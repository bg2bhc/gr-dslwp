/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_CCSDS_TURBO_ENCODE_H
#define INCLUDED_DSLWP_CCSDS_TURBO_ENCODE_H

#include <gnuradio/dslwp/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace dslwp {

/*!
 * \brief <+description of block+>
 * \ingroup dslwp
 *
 */
class DSLWP_API ccsds_turbo_encode : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<ccsds_turbo_encode> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of dslwp::ccsds_turbo_encode.
     *
     * To avoid accidental use of raw pointers, dslwp::ccsds_turbo_encode's
     * constructor is in a private implementation
     * class. dslwp::ccsds_turbo_encode::make is the public interface for
     * creating new instances.
     */
    static sptr
    make(int base = 223, int octets = 1, int code_type = 1, bool pass_other_length = 1);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_CCSDS_TURBO_ENCODE_H */
