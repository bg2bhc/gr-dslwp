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
#include "differential_phase_detection_1bit_cc_impl.h"
#include <math.h>
#include <stdio.h>

namespace gr {
  namespace dslwp {

    differential_phase_detection_1bit_cc::sptr
    differential_phase_detection_1bit_cc::make(int samples_per_symbol, const std::vector<gr_complex> &taps, int opt_point, int delay)
    {
      return gnuradio::get_initial_sptr
        (new differential_phase_detection_1bit_cc_impl(samples_per_symbol, taps, opt_point, delay));
    }

    /*
     * The private constructor
     */
    differential_phase_detection_1bit_cc_impl::differential_phase_detection_1bit_cc_impl(int samples_per_symbol, const std::vector<gr_complex> &taps, int opt_point, int delay)
      : gr::block("differential_phase_detection_1bit_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex))),
              d_samples_per_symbol(samples_per_symbol), d_taps(taps), d_opt_point(opt_point), d_delay(delay)
    {}

    /*
     * Our virtual destructor.
     */
    differential_phase_detection_1bit_cc_impl::~differential_phase_detection_1bit_cc_impl()
    {
    }

    void
    differential_phase_detection_1bit_cc_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }

    int
    differential_phase_detection_1bit_cc_impl::general_work (int noutput_items,
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

				add_item_tag(0, nitems_written(0)+i_output+d_delay, tags[j].key, tags[j].value );

				fprintf(stdout, "\n**** ASM found!\nSet sample_in_symbol: %d -> 0\n", sample_in_symbol_old);
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
	}

      // Do <+signal processing+>
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace dslwp */
} /* namespace gr */

