/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_DIFFERENTIAL_PHASE_DETECTION_1BIT_CF_H
#define INCLUDED_DSLWP_DIFFERENTIAL_PHASE_DETECTION_1BIT_CF_H

#include <gnuradio/block.h>
#include <gnuradio/dslwp/api.h>

namespace gr {
namespace dslwp {

/*!
 * \brief <+description of block+>
 * \ingroup dslwp
 *
 */
class DSLWP_API differential_phase_detection_1bit_cf : virtual public gr::block
{
public:
    typedef std::shared_ptr<differential_phase_detection_1bit_cf> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of
     * dslwp::differential_phase_detection_1bit_cf.
     *
     * To avoid accidental use of raw pointers,
     * dslwp::differential_phase_detection_1bit_cf's constructor is in a private
     * implementation class. dslwp::differential_phase_detection_1bit_cf::make is the
     * public interface for creating new instances.
     */
    static sptr make(int samples_per_symbol,
                     const std::vector<gr_complex>& taps,
                     int opt_point,
                     int delay);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_DIFFERENTIAL_PHASE_DETECTION_1BIT_CF_H */
