/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_KISS_ENCODE_PDU_H
#define INCLUDED_DSLWP_KISS_ENCODE_PDU_H

#include <gnuradio/block.h>
#include <gnuradio/dslwp/api.h>

namespace gr {
namespace dslwp {

/*!
 * \brief <+description of block+>
 * \ingroup dslwp
 *
 */
class DSLWP_API kiss_encode_pdu : virtual public gr::block
{
public:
    typedef std::shared_ptr<kiss_encode_pdu> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of dslwp::kiss_encode_pdu.
     *
     * To avoid accidental use of raw pointers, dslwp::kiss_encode_pdu's
     * constructor is in a private implementation
     * class. dslwp::kiss_encode_pdu::make is the public interface for
     * creating new instances.
     */
    static sptr make(int const_length);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_KISS_ENCODE_PDU_H */
