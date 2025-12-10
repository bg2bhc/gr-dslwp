/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "vector_padding_cc_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace dslwp {

using input_type = gr_complex;
using output_type = gr_complex;
vector_padding_cc::sptr
vector_padding_cc::make(gr_complex padding, int position, size_t vlen_in, size_t vlen_out)
{
    return gnuradio::make_block_sptr<vector_padding_cc_impl>(
        padding, position, vlen_in, vlen_out);
}


/*
 * The private constructor
 */
vector_padding_cc_impl::vector_padding_cc_impl(gr_complex padding,
                                               int position,
                                               size_t vlen_in,
                                               size_t vlen_out)
    : gr::sync_block("vector_padding_cc",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)*vlen_in),
                     gr::io_signature::make(
                         1 /* min outputs */, 1 /*max outputs */, sizeof(output_type)*vlen_out)),
	d_padding(padding), d_position(position), d_vlen_in(vlen_in), d_vlen_out(vlen_out)
						 
{
}

/*
 * Our virtual destructor.
 */
vector_padding_cc_impl::~vector_padding_cc_impl() {}

int vector_padding_cc_impl::work(int noutput_items,
                                 gr_vector_const_void_star& input_items,
                                 gr_vector_void_star& output_items)
{
    auto in = static_cast<const input_type*>(input_items[0]);
    auto out = static_cast<output_type*>(output_items[0]);

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
