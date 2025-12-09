/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_OQPSK_COHERENT_DEMOD_CC_H
#define INCLUDED_DSLWP_OQPSK_COHERENT_DEMOD_CC_H

#include <gnuradio/block.h>
#include <gnuradio/dslwp/api.h>

namespace gr {
namespace dslwp {

/*!
 * \brief <+description of block+>
 * \ingroup dslwp
 *
 */
class DSLWP_API oqpsk_coherent_demod_cc : virtual public gr::block
{
public:
    typedef std::shared_ptr<oqpsk_coherent_demod_cc> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of dslwp::oqpsk_coherent_demod_cc.
     *
     * To avoid accidental use of raw pointers, dslwp::oqpsk_coherent_demod_cc's
     * constructor is in a private implementation
     * class. dslwp::oqpsk_coherent_demod_cc::make is the public interface for
     * creating new instances.
     */
    static sptr make(int samples_per_symbol,
                     const std::vector<gr_complex>& taps,
                     int opt_point,
                     int pll,
                     float pll_loop_bw,
                     float pll_damping,
                     float freq_max,
                     float freq_min,
                     int dttl,
                     float dttl_loop_bw,
                     float dttl_damping,
                     float max_rate_deviation,
                     int asm_ignore);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_OQPSK_COHERENT_DEMOD_CC_H */
