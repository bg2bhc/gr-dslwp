/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_ATTACH_SYNC_MARKER_IMPL_H
#define INCLUDED_DSLWP_ATTACH_SYNC_MARKER_IMPL_H

#include <gnuradio/dslwp/attach_sync_marker.h>

namespace gr {
namespace dslwp {

class attach_sync_marker_impl : public attach_sync_marker
{
private:
      pmt::pmt_t d_in_port;
      pmt::pmt_t d_out_port;
      const std::vector<uint8_t> d_marker;
      int d_data_format;
      int d_msg_len;
      bool d_check_length;
      bool d_pass_other_length;

      void pmt_in_callback(pmt::pmt_t msg);
public:
    attach_sync_marker_impl(const std::vector<uint8_t>& marker,
                            int data_format,
                            int msg_len,
                            bool check_length,
                            bool pass_other_length);
    ~attach_sync_marker_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_ATTACH_SYNC_MARKER_IMPL_H */
