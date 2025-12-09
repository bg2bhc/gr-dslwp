/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_FEC_DECODE_B_H
#define INCLUDED_DSLWP_FEC_DECODE_B_H

#include <gnuradio/dslwp/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace dslwp {

/*!
 * \brief <+description of block+>
 * \ingroup dslwp
 *
 */
class DSLWP_API fec_decode_b : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<fec_decode_b> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of dslwp::fec_decode_b.
     *
     * To avoid accidental use of raw pointers, dslwp::fec_decode_b's
     * constructor is in a private implementation
     * class. dslwp::fec_decode_b::make is the public interface for
     * creating new instances.
     */
    static sptr make(int frame_len,
                     uint8_t using_randomizer,
                     bool using_m,
                     bool using_convolutional_code,
                     bool pass_all);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_FEC_DECODE_B_H */
