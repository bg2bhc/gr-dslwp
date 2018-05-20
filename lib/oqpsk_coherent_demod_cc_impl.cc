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
#include "oqpsk_coherent_demod_cc_impl.h"
#include <math.h>
#include <stdio.h>
#include <time.h>

namespace gr {
  namespace dslwp {

    oqpsk_coherent_demod_cc::sptr
    oqpsk_coherent_demod_cc::make(int samples_per_symbol, const std::vector<gr_complex> &taps, int opt_point, int pll, float pll_loop_bw, float pll_damping, float freq_max, float freq_min, int dttl, float dttl_loop_bw, float dttl_damping, float max_rate_deviation)
    {
      return gnuradio::get_initial_sptr
        (new oqpsk_coherent_demod_cc_impl(samples_per_symbol, taps, opt_point, pll, pll_loop_bw, pll_damping, freq_max, freq_min, dttl, dttl_loop_bw, dttl_damping, max_rate_deviation));
    }

    /*
     * The private constructor
     */
    oqpsk_coherent_demod_cc_impl::oqpsk_coherent_demod_cc_impl(int samples_per_symbol, const std::vector<gr_complex> &taps, int opt_point, int pll, float pll_loop_bw, float pll_damping, float freq_max, float freq_min, int dttl, float dttl_loop_bw, float dttl_damping, float max_rate_deviation)
      : gr::block("oqpsk_coherent_demod_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex))),
              d_samples_per_symbol(samples_per_symbol), d_taps(taps), d_opt_point(opt_point), d_pll(pll), d_pll_loop_bw(pll_loop_bw), d_pll_damping(pll_damping), d_freq_max(freq_max), d_freq_min(freq_min), d_dttl(dttl), d_dttl_loop_bw(dttl_loop_bw), d_dttl_damping(dttl_damping), d_max_rate_deviation(max_rate_deviation)
    {
		d_mix_out = (gr_complex *)malloc(sizeof(gr_complex)*taps.size());		
		for(int i=0; i<taps.size(); i++)
		{
			d_mix_out[i] = 1.0f;
		}

		d_mf_out = (gr_complex *)malloc(sizeof(gr_complex)*(samples_per_symbol/2+1));
		for(int i=0; i<samples_per_symbol/2+1; i++)
		{
			d_mf_out[i] = 1.0f;
		}

		float denom = 1.0f + 2.0f*pll_damping*pll_loop_bw + pll_loop_bw*pll_loop_bw;
		d_alpha = (4*pll_damping*pll_loop_bw)/denom;
		d_beta = (4*pll_loop_bw*pll_loop_bw)/denom;

		set_tag_propagation_policy(TPP_DONT);

		d_sample_in_symbol = 0;
		d_freq = 0;
		d_phase = 0;
	}

    /*
     * Our virtual destructor.
     */
    oqpsk_coherent_demod_cc_impl::~oqpsk_coherent_demod_cc_impl()
    {
    }

    void
    oqpsk_coherent_demod_cc_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
		ninput_items_required[0] = d_samples_per_symbol * noutput_items;
    }

    int
    oqpsk_coherent_demod_cc_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];
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

				/* For opt_point=12, [B-1, B0], [B1, B2]... */
				//add_item_tag(0, nitems_written(0)+i_output+1, tags[j].key, tags[j].value );

				/* For opt_point=4, [B0, B1], [B2, B3]... */
				add_item_tag(0, nitems_written(0)+i_output+2, tags[j].key, tags[j].value );

				static time_t time_curr;
				static struct tm *tblock_curr;

				time_curr = time(NULL);
				tblock_curr = gmtime(&time_curr);

				fprintf(stdout, "\n**** ASM found at: %02d:%02d:%02d\nSet sample_in_symbol: %d -> 0\n", tblock_curr->tm_hour, tblock_curr->tm_min, tblock_curr->tm_sec, sample_in_symbol_old);
			}
			if(tags[j].key == pmt::mp("payload_start"))
			{
				/* For opt_point=12, [B-1, B0], [B1, B2]... */
				//add_item_tag(0, nitems_written(0)+i_output+1, tags[j].key, tags[j].value );

				/* For opt_point=4, [B0, B1], [B2, B3]... */
				add_item_tag(0, nitems_written(0)+i_output+2, tags[j].key, tags[j].value );
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

				/* For opt_point=12, [B-1, B0], [B1, B2]... */
				//add_item_tag(0, nitems_written(0)+i_output+1, pmt::mp("eb_n0"), pmt::from_double(value*d_samples_per_symbol/2.0f) );

				/* For opt_point=4, [B0, B1], [B2, B3]... */
				add_item_tag(0, nitems_written(0)+i_output+2, pmt::mp("eb_n0_est"), pmt::from_double(eb_n0_est) );
				fprintf(stdout, "Estimated Eb/N0 = %f\n", eb_n0_est);

				}

			}
		}
		
		gr_complex nco;
		nco.real() = cos(-d_phase);
		nco.imag() = sin(-d_phase);

		for(int j=0; j<(d_taps.size()-1); j++)
		{
			d_mix_out[j] = d_mix_out[j+1];
		}
		d_mix_out[d_taps.size()-1] = nco*in[i];

		for(int j=0; j<d_samples_per_symbol/2; j++)
		{
			d_mf_out[j] = d_mf_out[j+1];
		}		

		d_mf_out[d_samples_per_symbol/2].real() = 0.0f;
		d_mf_out[d_samples_per_symbol/2].imag() = 0.0f;
		for(int j=0; j<d_taps.size(); j++)
		{
			d_mf_out[d_samples_per_symbol/2] = d_mf_out[d_samples_per_symbol/2] + d_mix_out[j] * d_taps[j];
		}

		float pd_out;
		if( d_sample_in_symbol==d_opt_point )
		{
			/* For opt_point=12, [B-1, B0], [B1, B2]... */
			//out[i_output].real() = d_mf_out[0].real();
			//out[i_output].imag() = d_mf_out[d_samples_per_symbol/2].imag();

			/* For opt_point=4, [B0, B1], [B2, B3]... */
			out[i_output].real() = d_mf_out[0].imag();
			out[i_output].imag() = d_mf_out[d_samples_per_symbol/2].real();
			i_output++;

			/* For opt_point=12, [B-1, B0], [B1, B2]... */
			//pd_out = d_mf_out[0].real()*d_mf_out[0].imag() - d_mf_out[d_samples_per_symbol/2].real()*d_mf_out[d_samples_per_symbol/2].imag();

			/* For opt_point=4, [B0, B1], [B2, B3]... */
			pd_out = d_mf_out[d_samples_per_symbol/2].real()*d_mf_out[d_samples_per_symbol/2].imag() - d_mf_out[0].real()*d_mf_out[0].imag();
		}

		d_sample_in_symbol++;
		if (d_sample_in_symbol == d_samples_per_symbol)
		{
			d_sample_in_symbol = 0;
		}
		
		if(d_pll)
		{
			d_freq = d_freq + d_beta * pd_out / d_samples_per_symbol / d_samples_per_symbol;

			if(d_freq > d_freq_max)
			{
				d_freq = d_freq_max;
			}
			else if(d_freq < d_freq_min)
			{
				d_freq = d_freq_min;
			}

			d_phase = d_phase + d_freq + d_alpha * pd_out / d_samples_per_symbol;
		}
		else
		{
			d_phase = d_phase + d_freq;
		}

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

