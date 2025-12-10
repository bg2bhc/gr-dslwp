/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_FEC_ENCODE_B_IMPL_H
#define INCLUDED_DSLWP_FEC_ENCODE_B_IMPL_H

#include <gnuradio/dslwp/fec_encode_b.h>

extern "C"
{
	#include "ccsds/ccsds.h"
}
namespace gr {
namespace dslwp {

class fec_encode_b_impl : public fec_encode_b
{
private:
      pmt::pmt_t d_in_port;
      pmt::pmt_t d_ptt_port;
      Ccsds cc;
      char d_ptt;
      void pmt_in_callback(pmt::pmt_t msg);

public:
    fec_encode_b_impl(int frame_len,
                      int preamble_len,
                      int trailer_len,
                      bool continous,
                      bool padding_zero,
                      uint8_t using_randomizer,
                      bool using_m,
                      uint8_t using_convolutional_code);
    ~fec_encode_b_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_FEC_ENCODE_B_IMPL_H */
