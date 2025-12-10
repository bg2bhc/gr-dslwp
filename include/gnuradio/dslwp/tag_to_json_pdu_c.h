/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_TAG_TO_JSON_PDU_C_H
#define INCLUDED_DSLWP_TAG_TO_JSON_PDU_C_H

#include <gnuradio/dslwp/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace dslwp {

/*!
 * \brief <+description of block+>
 * \ingroup dslwp
 *
 */
class DSLWP_API tag_to_json_pdu_c : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<tag_to_json_pdu_c> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of dslwp::tag_to_json_pdu_c.
     *
     * To avoid accidental use of raw pointers, dslwp::tag_to_json_pdu_c's
     * constructor is in a private implementation
     * class. dslwp::tag_to_json_pdu_c::make is the public interface for
     * creating new instances.
     */
    static sptr make(const std::string& key);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_TAG_TO_JSON_PDU_C_H */
