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
#include "steam_to_vector_moving_window_cc_impl.h"

namespace gr {
  namespace dslwp {

    steam_to_vector_moving_window_cc::sptr
    steam_to_vector_moving_window_cc::make(size_t vlen)
    {
      return gnuradio::get_initial_sptr
        (new steam_to_vector_moving_window_cc_impl(vlen));
    }

    /*
     * The private constructor
     */
    steam_to_vector_moving_window_cc_impl::steam_to_vector_moving_window_cc_impl(size_t vlen)
      : gr::sync_block("steam_to_vector_moving_window_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)*vlen)), d_vlen(vlen)
    {
		set_history(vlen);
    }

    /*
     * Our virtual destructor.
     */
    steam_to_vector_moving_window_cc_impl::~steam_to_vector_moving_window_cc_impl()
    {
    }

    int
    steam_to_vector_moving_window_cc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];

      // Do <+signal processing+>
      for (int i=0; i<noutput_items; i++)
      {
		for(int j=0; j<d_vlen; j++)
		{
			out[i*d_vlen+j] = in[i+j];
		}
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace dslwp */
} /* namespace gr */

