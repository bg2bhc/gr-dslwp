/* -*- c++ -*- */
/*
 * Copyright 2024 gr-dslwp author.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "lrtc_demod2_impl.h"

namespace gr {
  namespace dslwp {

    lrtc_demod2::sptr
    lrtc_demod2::make(int mode, size_t fft_size, size_t n_avg, int frame_len, uint8_t using_randomizer, bool using_m, bool using_convolutional_code, bool pass_all)
    {
      return gnuradio::get_initial_sptr
        (new lrtc_demod2_impl(mode, fft_size, n_avg, frame_len, using_randomizer, using_m, using_convolutional_code, pass_all));
    }

    static int ios[] = { sizeof(float), sizeof(float), sizeof(float) };
    static std::vector<int> iosig(ios, ios + sizeof(ios) / sizeof(int));

    /*
     * The private constructor
     */
    lrtc_demod2_impl::lrtc_demod2_impl(int mode, size_t fft_size, size_t n_avg, int frame_len, uint8_t using_randomizer, bool using_m, bool using_convolutional_code, bool pass_all)
      : gr::sync_block("lrtc_demod2",
              gr::io_signature::makev(3, 3, iosig),
              gr::io_signature::make(0, 0, 0)), d_fft_size(fft_size), d_n_avg(n_avg), d_pass_all(pass_all), d_mode(mode)
    {
	d_sample_in_symbol = 0;
	d_i_avg_buf = 0;
      
      	d_data_port = pmt::mp("data");
      	message_port_register_out(d_data_port);
      	
      	d_hk_port = pmt::mp("hk");
      	message_port_register_out(d_hk_port);

	//set_output_multiple(16);
	n_bits_out = 0;

	ccsds_init(&cc, 0x1ACFFC1D, frame_len, this, callback, callback2);

	cc.cfg_using_m = using_m;
	cc.cfg_using_convolutional_code = using_convolutional_code;
	cc.cfg_using_randomizer = using_randomizer;
    }

    /*
     * Our virtual destructor.
     */
    lrtc_demod2_impl::~lrtc_demod2_impl()
    {
    }

    void lrtc_demod2_impl::callback(unsigned char *buf, unsigned short len, int16_t byte_corr, void *obj_ptr)
    {
	static time_t time_curr;
	static struct tm *tblock_curr;
	lrtc_demod2_impl *obj_ptr_loc = (lrtc_demod2_impl *)obj_ptr;
	
	time_curr = time(NULL);
	tblock_curr =  gmtime(&time_curr);
	
	fprintf(stdout, "\n**** %02d:%02d:%02d, byte_corr = %d\n", tblock_curr->tm_hour, tblock_curr->tm_min, tblock_curr->tm_sec, byte_corr);

	if (byte_corr != -1 || obj_ptr_loc->d_pass_all)
	{
		obj_ptr_loc->message_port_pub(obj_ptr_loc->d_data_port, pmt::cons(pmt::make_dict(), pmt::init_u8vector(len, buf)));
	}
    }
    
    void lrtc_demod2_impl::callback2(unsigned char *buf, unsigned short len, int16_t byte_corr, void *obj_ptr)
    {       
	lrtc_demod2_impl *obj_ptr_loc = (lrtc_demod2_impl *)obj_ptr;
	
	char buf_json[100];
        int  len_json = sprintf(buf_json, "{\"freq_est\": %f}", obj_ptr_loc->d_freq_est);
	obj_ptr_loc->message_port_pub(obj_ptr_loc->d_hk_port, pmt::cons(pmt::make_dict(), pmt::init_u8vector(len_json, (const uint8_t *)buf_json)));
	
        len_json = sprintf(buf_json, "{\"amp_est\": %f}", sqrt(obj_ptr_loc->d_pwr_max/obj_ptr_loc->d_n_avg));
	obj_ptr_loc->message_port_pub(obj_ptr_loc->d_hk_port, pmt::cons(pmt::make_dict(), pmt::init_u8vector(len_json, (const uint8_t *)buf_json)));
	
	len_json = sprintf(buf_json, "{\"snr_est\": %f}", obj_ptr_loc->d_buf_snr_est[obj_ptr_loc->d_index_pwr_max]);
	obj_ptr_loc->message_port_pub(obj_ptr_loc->d_hk_port, pmt::cons(pmt::make_dict(), pmt::init_u8vector(len_json, (const uint8_t *)buf_json)));
    }

    int
    lrtc_demod2_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *pwr = (const float *) input_items[0];
      const float *freq = (const float *) input_items[1];
      const float *snr = (const float *) input_items[2];

      // Do <+signal processing+>
      for(int i=0; i<noutput_items; i++)
      {
            d_buf_pwr_est[d_i_avg_buf][d_sample_in_symbol] = pwr[i];
            d_buf_freq_est[d_i_avg_buf][d_sample_in_symbol] = freq[i];
            //d_buf_phase_est[d_sample_in_symbol] = phase[i];
            d_buf_snr_est[d_sample_in_symbol] = snr[i];
            
            d_sample_in_symbol++;            
            if(d_sample_in_symbol==d_fft_size)
            {
            	d_pwr_max = 0;   	           	
            	for(int j=0; j<d_fft_size; j++)
            	{
            		float pwr_avg = 0;
            		for(int k=0; k<d_n_avg; k++)
            		{
            			pwr_avg += d_buf_pwr_est[k][j];
            		}
            		
            		if(pwr_avg > d_pwr_max)
            		{
            			d_pwr_max = pwr_avg;
            			d_index_pwr_max = j;
            		}
            	}
            	d_freq_est = 0;
            	if(d_mode==1)
            	{
		    	for(int j=0; j<d_n_avg; j++)
		    	{
		    		d_freq_est += d_buf_freq_est[j][d_index_pwr_max];
		    	}
		    	d_freq_est /= d_n_avg;
            	}
            	
            	d_bits_out[n_bits_out] = (d_buf_freq_est[d_i_avg_buf][d_index_pwr_max]>=d_freq_est) ? 1 : 0;
            	n_bits_out++;
            	if(n_bits_out==16)
            	{
		    	ccsds_rx_proc(&cc, d_bits_out, 16);
			ccsds_pull(&cc);
			n_bits_out = 0;
            	}
            	
            	d_sample_in_symbol=0;
            	d_i_avg_buf++;
            	if(d_i_avg_buf==d_n_avg) d_i_avg_buf = 0;
            }
      }
      //fprintf(stdout, "nout=%d\n", nout);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace dslwp */
} /* namespace gr */

