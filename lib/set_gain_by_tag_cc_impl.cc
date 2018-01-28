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
#include "set_gain_by_tag_cc_impl.h"
#include <stdio.h>

namespace gr {
  namespace dslwp {

    set_gain_by_tag_cc::sptr
    set_gain_by_tag_cc::make(float k, float gain)
    {
      return gnuradio::get_initial_sptr
        (new set_gain_by_tag_cc_impl(k, gain));
    }

    /*
     * The private constructor
     */
    set_gain_by_tag_cc_impl::set_gain_by_tag_cc_impl(float k, float gain)
      : gr::sync_block("set_gain_by_tag_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex))), d_k(k), d_gain(gain)
    {}

    /*
     * Our virtual destructor.
     */
    set_gain_by_tag_cc_impl::~set_gain_by_tag_cc_impl()
    {
    }

    int
    set_gain_by_tag_cc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];

      // Do <+signal processing+>
      for(int i=0; i<noutput_items; i++)
      {
		std::vector<tag_t> tags;
		get_tags_in_window(tags, 0, i, i+1);

		for(int j=0; j<tags.size(); j++)
		{
			if(tags[j].key == pmt::mp("amp_est"))
			{
				if(pmt::is_real(tags[j].value))
				{
					float value = pmt::to_double(tags[j].value);
					float gain_old = d_gain;
					d_gain = d_k/value;
					fprintf(stdout, "\n**** Set gain: %f -> %f\n", gain_old, d_gain);
				}
			}
		}

		out[i] = in[i]*d_gain;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace dslwp */
} /* namespace gr */

