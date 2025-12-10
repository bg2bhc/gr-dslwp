/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_ATTACH_PREAMBLE_AND_TAILER_IMPL_H
#define INCLUDED_DSLWP_ATTACH_PREAMBLE_AND_TAILER_IMPL_H

#include <gnuradio/dslwp/attach_preamble_and_tailer.h>

namespace gr {
namespace dslwp {

class attach_preamble_and_tailer_impl : public attach_preamble_and_tailer
{
private:
      int d_len_preamble;
      int d_len_tailer;
      unsigned char d_padding_type;
      pmt::pmt_t d_in_port;
      pmt::pmt_t d_out_port;

      void pmt_in_callback(pmt::pmt_t msg);
public:
    attach_preamble_and_tailer_impl(int len_preamble,
                                    int len_tailer,
                                    unsigned char padding_type);
    ~attach_preamble_and_tailer_impl();

    // Where all the action really happens
    void forecast(int noutput_items, gr_vector_int& ninput_items_required);

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_ATTACH_PREAMBLE_AND_TAILER_IMPL_H */
