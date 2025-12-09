/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_VECTOR_PADDING_CC_IMPL_H
#define INCLUDED_DSLWP_VECTOR_PADDING_CC_IMPL_H

#include <gnuradio/dslwp/vector_padding_cc.h>

namespace gr {
namespace dslwp {

class vector_padding_cc_impl : public vector_padding_cc
{
private:
		gr_complex d_padding;
		int d_position;
		size_t d_vlen_in;
		size_t d_vlen_out;

public:
    vector_padding_cc_impl(gr_complex padding,
                           int position,
                           size_t vlen_in,
                           size_t vlen_out);
    ~vector_padding_cc_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_VECTOR_PADDING_CC_IMPL_H */
