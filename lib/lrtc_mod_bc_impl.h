/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_LRTC_MOD_BC_IMPL_H
#define INCLUDED_DSLWP_LRTC_MOD_BC_IMPL_H

#include <gnuradio/dslwp/lrtc_mod_bc.h>

namespace gr {
namespace dslwp {

class lrtc_mod_bc_impl : public lrtc_mod_bc
{
private:
      float d_pacc;
      float d_dp;

public:
    lrtc_mod_bc_impl();
    ~lrtc_mod_bc_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_LRTC_MOD_BC_IMPL_H */
