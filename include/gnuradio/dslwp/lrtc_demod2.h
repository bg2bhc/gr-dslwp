/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_LRTC_DEMOD2_H
#define INCLUDED_DSLWP_LRTC_DEMOD2_H

#include <gnuradio/dslwp/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace dslwp {

/*!
 * \brief <+description of block+>
 * \ingroup dslwp
 *
 */
class DSLWP_API lrtc_demod2 : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<lrtc_demod2> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of dslwp::lrtc_demod2.
     *
     * To avoid accidental use of raw pointers, dslwp::lrtc_demod2's
     * constructor is in a private implementation
     * class. dslwp::lrtc_demod2::make is the public interface for
     * creating new instances.
     */
    static sptr make(int mode,
                     size_t fft_size,
                     size_t n_avg,
                     int frame_len,
                     uint8_t using_randomizer,
                     bool using_m,
                     bool using_convolutional_code,
                     bool pass_all);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_LRTC_DEMOD2_H */
