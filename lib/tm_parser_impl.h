/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_TM_PARSER_IMPL_H
#define INCLUDED_DSLWP_TM_PARSER_IMPL_H

#include <gnuradio/dslwp/tm_parser.h>

namespace gr {
namespace dslwp {

class tm_parser_impl : public tm_parser
{
private:
      pmt::pmt_t d_in_port;
      void pmt_in_callback(pmt::pmt_t msg);

public:
    tm_parser_impl();
    ~tm_parser_impl();

    // Where all the action really happens
    void forecast(int noutput_items, gr_vector_int& ninput_items_required);

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_TM_PARSER_IMPL_H */
