/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_TAG_TO_JSON_PDU_C_IMPL_H
#define INCLUDED_DSLWP_TAG_TO_JSON_PDU_C_IMPL_H

#include <gnuradio/dslwp/tag_to_json_pdu_c.h>

namespace gr {
namespace dslwp {

class tag_to_json_pdu_c_impl : public tag_to_json_pdu_c
{
private:
      pmt::pmt_t d_out_port;
      pmt::pmt_t p_key;
      std::string d_key;

public:
    tag_to_json_pdu_c_impl(const std::string& key);
    ~tag_to_json_pdu_c_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_TAG_TO_JSON_PDU_C_IMPL_H */
