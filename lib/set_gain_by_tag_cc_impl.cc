/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "set_gain_by_tag_cc_impl.h"
#include <gnuradio/io_signature.h>
#include <stdio.h>

namespace gr {
namespace dslwp {

using input_type = gr_complex;
using output_type = gr_complex;
set_gain_by_tag_cc::sptr set_gain_by_tag_cc::make(float k, float gain)
{
    return gnuradio::make_block_sptr<set_gain_by_tag_cc_impl>(k, gain);
}


/*
 * The private constructor
 */
set_gain_by_tag_cc_impl::set_gain_by_tag_cc_impl(float k, float gain)
    : gr::sync_block("set_gain_by_tag_cc",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
                     gr::io_signature::make(
                         1 /* min outputs */, 1 /*max outputs */, sizeof(output_type))), d_k(k), d_gain(gain)
{
}

/*
 * Our virtual destructor.
 */
set_gain_by_tag_cc_impl::~set_gain_by_tag_cc_impl() {}

int set_gain_by_tag_cc_impl::work(int noutput_items,
                                  gr_vector_const_void_star& input_items,
                                  gr_vector_void_star& output_items)
{
    auto in = static_cast<const input_type*>(input_items[0]);
    auto out = static_cast<output_type*>(output_items[0]);

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
