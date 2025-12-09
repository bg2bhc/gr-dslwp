/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_SET_GAIN_BY_TAG_CC_IMPL_H
#define INCLUDED_DSLWP_SET_GAIN_BY_TAG_CC_IMPL_H

#include <gnuradio/dslwp/set_gain_by_tag_cc.h>

namespace gr {
namespace dslwp {

class set_gain_by_tag_cc_impl : public set_gain_by_tag_cc
{
private:
      float d_k;
      float d_gain;

public:
    set_gain_by_tag_cc_impl(float k, float gain);
    ~set_gain_by_tag_cc_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_SET_GAIN_BY_TAG_CC_IMPL_H */
