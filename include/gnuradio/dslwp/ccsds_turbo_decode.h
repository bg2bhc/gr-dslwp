/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_CCSDS_TURBO_DECODE_H
#define INCLUDED_DSLWP_CCSDS_TURBO_DECODE_H

#include <gnuradio/dslwp/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace dslwp {

/*!
 * \brief <+description of block+>
 * \ingroup dslwp
 *
 */
class DSLWP_API ccsds_turbo_decode : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<ccsds_turbo_decode> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of dslwp::ccsds_turbo_decode.
     *
     * To avoid accidental use of raw pointers, dslwp::ccsds_turbo_decode's
     * constructor is in a private implementation
     * class. dslwp::ccsds_turbo_decode::make is the public interface for
     * creating new instances.
     */
    static sptr make(int base = 223,
                     int octets = 1,
                     int code_type = 1,
                     int iterations = 2,
                     float sigma = 0.707,
                     uint8_t update_sigma = 1);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_CCSDS_TURBO_DECODE_H */
