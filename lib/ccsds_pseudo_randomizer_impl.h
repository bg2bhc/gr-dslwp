/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_CCSDS_PSEUDO_RANDOMIZER_IMPL_H
#define INCLUDED_DSLWP_CCSDS_PSEUDO_RANDOMIZER_IMPL_H

#include <gnuradio/dslwp/ccsds_pseudo_randomizer.h>
extern "C"
{
	#include "ccsds/randomizer.h"
}

namespace gr {
namespace dslwp {

class ccsds_pseudo_randomizer_impl : public ccsds_pseudo_randomizer
{
private:
      pmt::pmt_t d_in_port;
      pmt::pmt_t d_out_port;
      int d_data_format;

      void pmt_in_callback(pmt::pmt_t msg);
public:
    ccsds_pseudo_randomizer_impl(int data_format);
    ~ccsds_pseudo_randomizer_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_CCSDS_PSEUDO_RANDOMIZER_IMPL_H */
