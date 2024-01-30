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
#include "lrtc_demod_impl.h"
#include "stdio.h"
#include "math.h"

namespace gr {
  namespace dslwp {

    lrtc_demod::sptr
    lrtc_demod::make(int mode, size_t fft_size, size_t n_avg)
    {
      return gnuradio::get_initial_sptr
        (new lrtc_demod_impl(mode, fft_size, n_avg));
    }

    static int ios[] = { sizeof(float), sizeof(float), sizeof(float) };
    static std::vector<int> iosig(ios, ios + sizeof(ios) / sizeof(int));
    /*
     * The private constructor
     */
    lrtc_demod_impl::lrtc_demod_impl(int mode, size_t fft_size, size_t n_avg)
      : gr::sync_decimator("lrtc_demod",
              gr::io_signature::makev(3, 3, iosig),
              gr::io_signature::make(1, 1, sizeof(gr_complex)), fft_size), d_fft_size(fft_size), d_n_avg(n_avg)
    {
      d_sample_in_symbol = 0;
      d_i_avg_buf = 0;
    }

    /*
     * Our virtual destructor.
     */
    lrtc_demod_impl::~lrtc_demod_impl()
    {
    }

    int
    lrtc_demod_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *pwr = (const float *) input_items[0];
      const float *freq = (const float *) input_items[1];
      const float *snr = (const float *) input_items[2];
      gr_complex *out = (gr_complex *) output_items[0];

      // Do <+signal processing+>
      int nout=0;
      for(int i=0; i<noutput_items*d_fft_size; i++)
      {
            d_buf_pwr_est[d_i_avg_buf][d_sample_in_symbol] = pwr[i];
            d_buf_freq_est[d_sample_in_symbol] = freq[i];
            //d_buf_phase_est[d_sample_in_symbol] = phase[i];
            d_buf_snr_est[d_sample_in_symbol] = snr[i];
            
            d_sample_in_symbol++;            
            if(d_sample_in_symbol==d_fft_size)
            {            	
            	int index_pwr_max=0;
            	float pwr_max=0;
            	for(int j=0; j<d_fft_size; j++)
            	{
            		float pwr_avg = 0;
            		for(int k=0; k<d_n_avg; k++)
            		{
            			pwr_avg += d_buf_pwr_est[k][j];
            		}
            		
            		if(pwr_avg>pwr_max)
            		{
            			pwr_max = pwr_avg;
            			index_pwr_max = j;
            		}
            	}
            	if(d_buf_freq_est[index_pwr_max]>=0)
            	{
            		out[nout] = sqrt(d_buf_pwr_est[d_i_avg_buf][index_pwr_max]/pwr_max*d_n_avg);
            	}
            	else
            	{
            		out[nout] = -sqrt(d_buf_pwr_est[d_i_avg_buf][index_pwr_max]/pwr_max*d_n_avg);
            	}
            	nout++;
            	
            	d_sample_in_symbol=0;
            	d_i_avg_buf++;
            	if(d_i_avg_buf==d_n_avg) d_i_avg_buf = 0;
            }
      }
      //fprintf(stdout, "nout=%d\n", nout);

      // Tell runtime system how many output items we produced.
      return nout;
    }

  } /* namespace dslwp */
} /* namespace gr */

