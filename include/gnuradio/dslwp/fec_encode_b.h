/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_FEC_ENCODE_B_H
#define INCLUDED_DSLWP_FEC_ENCODE_B_H

#include <gnuradio/dslwp/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace dslwp {

/*!
 * \brief <+description of block+>
 * \ingroup dslwp
 *
 */
class DSLWP_API fec_encode_b : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<fec_encode_b> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of dslwp::fec_encode_b.
     *
     * To avoid accidental use of raw pointers, dslwp::fec_encode_b's
     * constructor is in a private implementation
     * class. dslwp::fec_encode_b::make is the public interface for
     * creating new instances.
     */
    static sptr make(int frame_len,
                     int preamble_len,
                     int trailer_len,
                     bool continous,
                     bool padding_zero,
                     uint8_t using_randomizer,
                     bool using_m,
                     uint8_t using_convolutional_code);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_FEC_ENCODE_B_H */
