/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_CCSDS_TURBO_DECODE_IMPL_H
#define INCLUDED_DSLWP_CCSDS_TURBO_DECODE_IMPL_H

#include <gnuradio/dslwp/ccsds_turbo_decode.h>
extern "C"
{
	#include "ccsds/libconvcodes.h"
	#include "ccsds/libturbocodes.h"
}

#define MAX_COMPONENTS 4

namespace gr {
namespace dslwp {

class ccsds_turbo_decode_impl : public ccsds_turbo_decode
{
private:
      pmt::pmt_t d_in_port;
      pmt::pmt_t d_out_port;
      int d_base;
      int d_octets;
      int d_code_type;
      int d_iterations;
      float d_sigma;
      bool d_update_sigma;

      float d_rate;
      int d_info_length;
      int d_encoded_length;

      int *d_pi;
      const char *d_forward_upper[MAX_COMPONENTS];
      const char *d_forward_lower[MAX_COMPONENTS];
      const char *d_backward;
      t_convcode *d_code1;
      t_convcode *d_code2;
      t_turbocode *d_turbo;


      void pmt_in_callback(pmt::pmt_t msg);
      int puncturing(int k);
public:
    ccsds_turbo_decode_impl(int base,
                            int octets,
                            int code_type,
                            int iterations,
                            float sigma,
                            uint8_t update_sigma);
    ~ccsds_turbo_decode_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_CCSDS_TURBO_DECODE_IMPL_H */
