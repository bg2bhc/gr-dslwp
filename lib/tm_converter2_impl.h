/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_TM_CONVERTER2_IMPL_H
#define INCLUDED_DSLWP_TM_CONVERTER2_IMPL_H

#include <gnuradio/dslwp/tm_converter2.h>

namespace gr {
namespace dslwp {

class tm_converter2_impl : public tm_converter2
{
private:
      pmt::pmt_t d_in_port;
      pmt::pmt_t d_out_port;
      
      void pmt_in_callback(pmt::pmt_t msg);
      
      const std::string d_header;
      const std::vector<int> d_list;

public:
    tm_converter2_impl(const std::string& header, const std::vector<int>& list);
    ~tm_converter2_impl();

    // Where all the action really happens
    void forecast(int noutput_items, gr_vector_int& ninput_items_required);

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_TM_CONVERTER2_IMPL_H */
