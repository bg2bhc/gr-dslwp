/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_FRAME_SPLITER_C_IMPL_H
#define INCLUDED_DSLWP_FRAME_SPLITER_C_IMPL_H

#include <gnuradio/dslwp/frame_spliter_c.h>

namespace gr {
namespace dslwp {

class frame_spliter_c_impl : public frame_spliter_c
{
private:
      pmt::pmt_t d_out_port;
      pmt::pmt_t d_key;
      int d_frame_length;
      int d_bits_in;
      float *d_payload;
      float d_eb_n0_est;

public:
    frame_spliter_c_impl(const std::string& key, int frame_length);
    ~frame_spliter_c_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_FRAME_SPLITER_C_IMPL_H */
