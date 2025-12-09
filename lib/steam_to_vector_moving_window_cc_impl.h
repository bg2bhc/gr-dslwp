/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_STEAM_TO_VECTOR_MOVING_WINDOW_CC_IMPL_H
#define INCLUDED_DSLWP_STEAM_TO_VECTOR_MOVING_WINDOW_CC_IMPL_H

#include <gnuradio/dslwp/steam_to_vector_moving_window_cc.h>

namespace gr {
namespace dslwp {

class steam_to_vector_moving_window_cc_impl : public steam_to_vector_moving_window_cc
{
private:
    size_t d_vlen;

public:
    steam_to_vector_moving_window_cc_impl(size_t vlen);
    ~steam_to_vector_moving_window_cc_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_STEAM_TO_VECTOR_MOVING_WINDOW_CC_IMPL_H */
