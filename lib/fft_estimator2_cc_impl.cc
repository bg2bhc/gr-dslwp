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
#include <gnuradio/expj.h>
#include "fft_estimator2_cc_impl.h"

namespace gr {
  namespace dslwp {

    fft_estimator2_cc::sptr
    fft_estimator2_cc::make(size_t fft_size, float threshold, size_t tap_len)
    {
      return gnuradio::get_initial_sptr
        (new fft_estimator2_cc_impl(fft_size, threshold, tap_len));
    }

    static int ios[] = { sizeof(gr_complex), sizeof(float), sizeof(float), sizeof(float) };
    static std::vector<int> iosig(ios, ios + sizeof(ios) / sizeof(int));

    /*
     * The private constructor
     */
    fft_estimator2_cc_impl::fft_estimator2_cc_impl(size_t fft_size, float threshold, size_t tap_len)
      : gr::sync_block("fft_estimator2_cc",
              gr::io_signature::make(2, 2, sizeof(gr_complex)*fft_size),
              gr::io_signature::makev(1, 4, iosig)),
              d_fft_size(fft_size), d_threshold(threshold), d_over_threshold(0), d_tap_len(tap_len)
    {
      d_power = (float *)malloc(sizeof(float) * fft_size);
      set_history(2);
    }

    /*
     * Our virtual destructor.
     */
    fft_estimator2_cc_impl::~fft_estimator2_cc_impl()
    {
    }

    int
    fft_estimator2_cc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in_fft = (const gr_complex *) input_items[0];
      const gr_complex *in_s = (const gr_complex *) input_items[1];
      gr_complex *out = (gr_complex *) output_items[0];
      float *pwr_out = output_items.size() >= 2 ? (float*)output_items[1] : NULL;
      float *freq_out = output_items.size() >= 3 ? (float*)output_items[2] : NULL;
      float *snr_out = output_items.size() >= 4 ? (float*)output_items[3] : NULL;

      // Do <+signal processing+>
      for(int i=0; i<noutput_items; i++)
      {
	//float power_s_plus_n = 0;
	for(int j=0; j<d_fft_size; j++)
	{
		d_power[j] = in_fft[(i+1)*d_fft_size+j].real() * in_fft[(i+1)*d_fft_size+j].real() + in_fft[(i+1)*d_fft_size+j].imag() * in_fft[(i+1)*d_fft_size+j].imag();
		//power_s_plus_n += d_power[j];
	}
	
		float power_s = 0;
		int index_s = 0;
		for(int j=0; j<d_fft_size; j++)
		{
			float sum;
			if( j == (d_fft_size-1) )
			{
				sum = d_power[j] + d_power[0];
			}
			else
			{
				sum = d_power[j] + d_power[j+1];
			}

			if (sum > power_s)
			{
				power_s = sum;
				index_s = j;
			}
		}
		pwr_out[i] = power_s;		
		freq_out[i] = index_s;
		if(freq_out[i]>(d_fft_size/2-0.5)) freq_out[i] = freq_out[i] - d_fft_size;
		freq_out[i] = freq_out[i]*2.0f*M_PI/d_fft_size;
		/*
		if( index_s == (d_fft_size-1) )
		{
			phase_out[i] = in_fft[index_s] + in_fft[0];
		}
		else
		{
			phase_out[i] = in_fft[index_s] + in_fft[index_s+1];
		}*/

		float power_s_plus_n = 0.0f;
		for(int j=0; j<d_fft_size/16; j++)
		{
			if((index_s-j)<0)
			{
				power_s_plus_n = power_s_plus_n + d_power[index_s-j+d_fft_size];
			}
			else
			{
				power_s_plus_n = power_s_plus_n + d_power[index_s-j];
			}

			if((index_s+1+j)>=d_fft_size)
			{
				power_s_plus_n = power_s_plus_n + d_power[index_s+1+j-d_fft_size];
			}
			else
			{
				power_s_plus_n = power_s_plus_n + d_power[index_s+1+j];
			}
		}


		float snr = power_s/(power_s_plus_n-power_s)/8.0f; 
		//float snr = power_s/(power_s_plus_n-power_s);
		snr_out[i] = snr;

		if(d_over_threshold)
		{
			if(!d_corr_found)
			{
				if(power_s > d_power_s)
				{
					d_power_s = power_s;
					d_power_s_plus_n = power_s_plus_n;
					d_snr = snr;
					d_index_s = index_s;

					d_amp_i0 = sqrt(d_power[index_s]);
					if(index_s == d_fft_size-1)
					{
						d_amp_i1 = sqrt(d_power[0]);
					}
					else
					{
						d_amp_i1 = sqrt(d_power[index_s+1]);
					}
				}
				else
				{
					d_corr_found = 1;
					add_item_tag(0, nitems_written(0)+i, pmt::mp("corr_start"), pmt::from_double(0.0) );
					add_item_tag(0, nitems_written(0)+i+d_tap_len, pmt::mp("payload_start"), pmt::from_double(0.0) );

					float freq_est = ( d_index_s + d_amp_i1/(d_amp_i0+d_amp_i1) )/d_fft_size*2.0f*M_PI;
					if(freq_est>M_PI)
					{
						freq_est -= 2.0f*M_PI;
					}
					add_item_tag(0, nitems_written(0)+i, pmt::mp("freq_est"), pmt::from_double(freq_est) );

					gr_complex coeff, sum;
					sum = 0.0f;

					float phase_acc = 0.0f;
					for(int j=0; j<d_fft_size; j++)
					{
					        coeff = gr_expj(-phase_acc);

						sum += in_s[i*d_fft_size+j] * coeff;

						phase_acc += freq_est;

						if(phase_acc>M_PI)
						{
							phase_acc -= 2.0f*M_PI;
						}
						else if(phase_acc<-M_PI)
						{
							phase_acc += 2.0f*M_PI;
						}
					}

					float phase_est = 0.0f;
					if(sum.real()>0.0f)
					{
						phase_est = atan(sum.imag()/sum.real());
					}
					else if(sum.real()<0.0f)
					{
						if(sum.imag()>0.0f)
						{
							phase_est = atan(sum.imag()/sum.real()) + M_PI;
						}
						else
						{
							phase_est = atan(sum.imag()/sum.real()) - M_PI;
						}
					}
					else
					{
						if(sum.imag()>0.0f)
						{
							phase_est = M_PI/2.0f;
						}
						else if(sum.imag()<0.0f)
						{
							phase_est = -M_PI/2.0f;
						}
						else
						{
							phase_est = 0.0f;
						}
					}

					add_item_tag(0, nitems_written(0)+i, pmt::mp("phase_est"), pmt::from_double(phase_est) );

					float power_est = sum.real() * sum.real() + sum.imag() * sum.imag();
					add_item_tag(0, nitems_written(0)+i, pmt::mp("amp_est"), pmt::from_double(sqrt(power_est)));
					add_item_tag(0, nitems_written(0)+i, pmt::mp("snr_est"), pmt::from_double(power_est/(d_power_s_plus_n-power_est)/8.0f) );					
				}
			}

			if(snr < d_threshold)
			{
				d_over_threshold = 0;
			}
		}
		else
		{
			if(snr >= d_threshold)
			{				
				d_power_s = power_s;
				d_power_s_plus_n = power_s_plus_n;
				d_snr = snr;
				d_index_s = index_s;

				d_amp_i0 = sqrt(d_power[index_s]);
				if(index_s == d_fft_size-1)
				{
					d_amp_i1 = sqrt(d_power[0]);
				}
				else
				{
					d_amp_i1 = sqrt(d_power[index_s+1]);
				}

				d_over_threshold = 1;
				d_corr_found = 0;
			}
		}

		out[i] = in_s[i*d_fft_size];
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace dslwp */
} /* namespace gr */

