/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_FFT_ESTIMATOR2_CC_H
#define INCLUDED_DSLWP_FFT_ESTIMATOR2_CC_H

#include <gnuradio/dslwp/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace dslwp {

/*!
 * \brief <+description of block+>
 * \ingroup dslwp
 *
 */
class DSLWP_API fft_estimator2_cc : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<fft_estimator2_cc> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of dslwp::fft_estimator2_cc.
     *
     * To avoid accidental use of raw pointers, dslwp::fft_estimator2_cc's
     * constructor is in a private implementation
     * class. dslwp::fft_estimator2_cc::make is the public interface for
     * creating new instances.
     */
    static sptr make(size_t fft_size, float threshold, size_t tap_len);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_FFT_ESTIMATOR2_CC_H */
