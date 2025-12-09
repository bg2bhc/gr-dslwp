/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "lrtc_demod_impl.h"
#include <gnuradio/io_signature.h>
#include <stdio.h>
#include <math.h>
#include <complex>

constexpr auto M_1Jf = std::complex<float>(0, 1);

namespace gr {
namespace dslwp {


lrtc_demod::sptr lrtc_demod::make(int mode, size_t fft_size, size_t n_avg)
{
    return gnuradio::make_block_sptr<lrtc_demod_impl>(mode, fft_size, n_avg);
}

static int ios[] = { sizeof(float), sizeof(float), sizeof(float) };
static std::vector<int> iosig(ios, ios + sizeof(ios) / sizeof(int));
/*
 * The private constructor
 */
lrtc_demod_impl::lrtc_demod_impl(int mode, size_t fft_size, size_t n_avg)
    : gr::sync_decimator("lrtc_demod",
                         gr::io_signature::makev(
                             3 /* min inputs */, 3 /* max inputs */, iosig),
                         gr::io_signature::make(1 /* min outputs */,
                                                1 /*max outputs */,
                                                sizeof(gr_complex)),
                         fft_size /*<+decimation+>*/),
	d_fft_size(fft_size), d_n_avg(n_avg), d_mode(mode)
{
      d_sample_in_symbol = 0;
      d_i_avg_buf = 0;
}

/*
 * Our virtual destructor.
 */
lrtc_demod_impl::~lrtc_demod_impl() {}

int lrtc_demod_impl::work(int noutput_items,
                          gr_vector_const_void_star& input_items,
                          gr_vector_void_star& output_items)
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
            	
            	if(d_buf_freq_est[d_i_avg_buf][d_index_pwr_max]>=d_freq_est)
            	{
            		out[nout] = sqrt(d_buf_pwr_est[d_i_avg_buf][d_index_pwr_max]/d_pwr_max*d_n_avg)+M_1Jf*d_freq_est;
            	}
            	else
            	{
            		out[nout] = -sqrt(d_buf_pwr_est[d_i_avg_buf][d_index_pwr_max]/d_pwr_max*d_n_avg)+M_1Jf*d_freq_est;
            	}
            	//out[nout] = d_buf_freq_est[d_i_avg_buf][d_index_pwr_max] + 1j * d_freq_est;
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
