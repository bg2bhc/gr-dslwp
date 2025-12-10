/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "steam_to_vector_moving_window_cc_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace dslwp {

using input_type = gr_complex;
using output_type = gr_complex;
steam_to_vector_moving_window_cc::sptr steam_to_vector_moving_window_cc::make(size_t vlen)
{
    return gnuradio::make_block_sptr<steam_to_vector_moving_window_cc_impl>(vlen);
}


/*
 * The private constructor
 */
steam_to_vector_moving_window_cc_impl::steam_to_vector_moving_window_cc_impl(size_t vlen)
    : gr::sync_block("steam_to_vector_moving_window_cc",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
                     gr::io_signature::make(
                         1 /* min outputs */, 1 /*max outputs */, sizeof(output_type)*vlen)), d_vlen(vlen)
{
	set_history(vlen);
}

/*
 * Our virtual destructor.
 */
steam_to_vector_moving_window_cc_impl::~steam_to_vector_moving_window_cc_impl() {}

int steam_to_vector_moving_window_cc_impl::work(int noutput_items,
                                                gr_vector_const_void_star& input_items,
                                                gr_vector_void_star& output_items)
{
    auto in = static_cast<const input_type*>(input_items[0]);
    auto out = static_cast<output_type*>(output_items[0]);

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
