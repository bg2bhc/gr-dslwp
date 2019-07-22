/* -*- c++ -*- */
/* 
 * Copyright 2018 <+YOU OR YOUR COMPANY+>.
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
#include "differential_phase_detection_1bit_cf_impl.h"
#include <math.h>
#include <stdio.h>
#include <time.h>

namespace gr {
  namespace dslwp {

    differential_phase_detection_1bit_cf::sptr
    differential_phase_detection_1bit_cf::make(int samples_per_symbol, const std::vector<gr_complex> &taps, int opt_point, int delay)
    {
      return gnuradio::get_initial_sptr
        (new differential_phase_detection_1bit_cf_impl(samples_per_symbol, taps, opt_point, delay));
    }

    /*
     * The private constructor
     */
    differential_phase_detection_1bit_cf_impl::differential_phase_detection_1bit_cf_impl(int samples_per_symbol, const std::vector<gr_complex> &taps, int opt_point, int delay)
      : gr::block("differential_phase_detection_1bit_cf",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(float))),
              d_samples_per_symbol(samples_per_symbol), d_taps(taps), d_opt_point(opt_point), d_delay(delay)
    {
	d_mix_out = (gr_complex *)malloc(sizeof(gr_complex)*taps.size());		
	for(int i=0; i<taps.size(); i++)
	{
		d_mix_out[i] = 1.0f;
	}

	d_mf_out = (gr_complex *)malloc(sizeof(gr_complex)*(samples_per_symbol+1));
	for(int i=0; i<samples_per_symbol+1; i++)
	{
		d_mf_out[i] = 1.0f;
	}

	set_tag_propagation_policy(TPP_DONT);

	d_sample_in_symbol = 0;
    }

    /*
     * Our virtual destructor.
     */
    differential_phase_detection_1bit_cf_impl::~differential_phase_detection_1bit_cf_impl()
    {
    }

    void
    differential_phase_detection_1bit_cf_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
	ninput_items_required[0] = d_samples_per_symbol * noutput_items;
    }

    int
    differential_phase_detection_1bit_cf_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      float *out = (float *) output_items[0];
      int i_output = 0;

      for(int i=0; i<ninput_items[0]; i++)
      {
		std::vector<tag_t> tags;
		get_tags_in_window(tags, 0, i, i+1);

		for(int j=0; j<tags.size(); j++)
		{
			if(tags[j].key == pmt::mp("corr_start"))
			{
				int sample_in_symbol_old = d_sample_in_symbol;
				d_sample_in_symbol = 0;

				add_item_tag(0, nitems_written(0)+i_output+d_delay, tags[j].key, tags[j].value );

				static time_t time_curr;
				static struct tm *tblock_curr;

				time_curr = time(NULL);
				tblock_curr = gmtime(&time_curr);

				fprintf(stdout, "\n**** ASM found at: %02d:%02d:%02d\nSet sample_in_symbol: %d -> 0\n", tblock_curr->tm_hour, tblock_curr->tm_min, tblock_curr->tm_sec, sample_in_symbol_old);
			}
			else if(tags[j].key == pmt::mp("payload_start"))
			{
				add_item_tag(0, nitems_written(0)+i_output+d_delay, tags[j].key, tags[j].value );
			}
			else if(tags[j].key == pmt::mp("freq_est"))
			{
				if(pmt::is_real(tags[j].value))
				{
					float value = pmt::to_double(tags[j].value);
					float freq_old = d_freq;
					d_freq = value;
					fprintf(stdout, "Set freq: %f -> %f\n", freq_old, d_freq);
				}
			}
			else if(tags[j].key == pmt::mp("phase_est"))
			{
				if(pmt::is_real(tags[j].value))
				{
					float value = pmt::to_double(tags[j].value);
					float phase_old = d_phase;
					d_phase = value;
					fprintf(stdout, "Set phase: %f -> %f\n", phase_old, d_phase);
				}
			}
			else if(tags[j].key == pmt::mp("snr_est"))
			{
				if(pmt::is_real(tags[j].value))
				{
					float value = pmt::to_double(tags[j].value);
					float eb_n0_est = value*d_samples_per_symbol/2.0f;

					add_item_tag(0, nitems_written(0)+i_output+d_delay, pmt::mp("eb_n0_est"), pmt::from_double(eb_n0_est) );
					fprintf(stdout, "Estimated Eb/N0 = %f\n", eb_n0_est);

				}
			}

		}

		gr_complex nco;
		nco = cos(-d_phase) + 1j*sin(-d_phase);

		for(int j=0; j<(d_taps.size()-1); j++)
		{
			d_mix_out[j] = d_mix_out[j+1];
		}
		d_mix_out[d_taps.size()-1] = nco*in[i];

		for(int j=0; j<d_samples_per_symbol; j++)
		{
			d_mf_out[j] = d_mf_out[j+1];
		}		

		d_mf_out[d_samples_per_symbol] = 0;
		for(int j=0; j<d_taps.size(); j++)
		{
			d_mf_out[d_samples_per_symbol] = d_mf_out[d_samples_per_symbol] + d_mix_out[j] * d_taps[j];
		}

		if( d_sample_in_symbol==d_opt_point )
		{
			out[i_output] = d_mf_out[d_samples_per_symbol].imag() * d_mf_out[0].real() - d_mf_out[d_samples_per_symbol].real() * d_mf_out[0].imag();
			i_output++;
		}

		d_sample_in_symbol++;
		if (d_sample_in_symbol == d_samples_per_symbol)
		{
			d_sample_in_symbol = 0;
		}

		d_phase = d_phase + d_freq;
		if(d_phase > M_PI)
		{
			d_phase -= 2.0f*M_PI;
		}
		else if(d_phase < -M_PI)
		{
			d_phase += 2.0f*M_PI;
		}
	}

      // Do <+signal processing+>
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (ninput_items[0]);

      // Tell runtime system how many output items we produced.
      return i_output;
    }

  } /* namespace dslwp */
} /* namespace gr */

