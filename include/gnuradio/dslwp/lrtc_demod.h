/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_LRTC_DEMOD_H
#define INCLUDED_DSLWP_LRTC_DEMOD_H

#include <gnuradio/dslwp/api.h>
#include <gnuradio/sync_decimator.h>

namespace gr {
namespace dslwp {

/*!
 * \brief <+description of block+>
 * \ingroup dslwp
 *
 */
class DSLWP_API lrtc_demod : virtual public gr::sync_decimator
{
public:
    typedef std::shared_ptr<lrtc_demod> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of dslwp::lrtc_demod.
     *
     * To avoid accidental use of raw pointers, dslwp::lrtc_demod's
     * constructor is in a private implementation
     * class. dslwp::lrtc_demod::make is the public interface for
     * creating new instances.
     */
    static sptr make(int mode, size_t fft_size, size_t n_avg);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_LRTC_DEMOD_H */
