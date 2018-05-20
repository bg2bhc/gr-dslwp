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
#include "vector_padding_cc_impl.h"

namespace gr {
  namespace dslwp {

    vector_padding_cc::sptr
    vector_padding_cc::make(gr_complex padding, int position, size_t vlen_in, size_t vlen_out)
    {
      return gnuradio::get_initial_sptr
        (new vector_padding_cc_impl(padding, position, vlen_in, vlen_out));
    }

    /*
     * The private constructor
     */
    vector_padding_cc_impl::vector_padding_cc_impl(gr_complex padding, int position, size_t vlen_in, size_t vlen_out)
      : gr::sync_block("vector_padding_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)*vlen_in),
              gr::io_signature::make(1, 1, sizeof(gr_complex)*vlen_out)),
              d_padding(padding), d_position(position), d_vlen_in(vlen_in), d_vlen_out(vlen_out)
    {}

    /*
     * Our virtual destructor.
     */
    vector_padding_cc_impl::~vector_padding_cc_impl()
    {
    }

    int
    vector_padding_cc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];

      // Do <+signal processing+>
      for(int i=0; i<noutput_items; i++)
      {
		if(d_position==0) // End
		{
			for(int j=0; j<d_vlen_in; j++)
			{
				out[i*d_vlen_out+j] = in[i*d_vlen_in+j];
			}
			for(int j=d_vlen_in; j<d_vlen_out; j++)
			{
				out[i*d_vlen_out+j] = d_padding;
			}
		}
		if(d_position==1) // Begin
		{
			for(int j=0; j<d_vlen_out-d_vlen_in; j++)
			{
				out[i*d_vlen_out+j] = d_padding;
			}
			for(int j=d_vlen_out-d_vlen_in; j<d_vlen_out; j++)
			{
				out[i*d_vlen_out+j] = in[i*d_vlen_in+j-d_vlen_out+d_vlen_in];
			}
		}
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace dslwp */
} /* namespace gr */

