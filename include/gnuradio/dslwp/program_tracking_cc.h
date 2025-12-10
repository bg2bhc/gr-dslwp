/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_PROGRAM_TRACKING_CC_H
#define INCLUDED_DSLWP_PROGRAM_TRACKING_CC_H

#include <gnuradio/dslwp/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace dslwp {

/*!
 * \brief <+description of block+>
 * \ingroup dslwp
 *
 */
class DSLWP_API program_tracking_cc : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<program_tracking_cc> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of dslwp::program_tracking_cc.
     *
     * To avoid accidental use of raw pointers, dslwp::program_tracking_cc's
     * constructor is in a private implementation
     * class. dslwp::program_tracking_cc::make is the public interface for
     * creating new instances.
     */
    static sptr make(uint8_t enable,
                     uint32_t timestamp,
                     const std::string& path,
                     float lon,
                     float lat,
                     float alt,
                     float fc,
                     uint32_t samp_rate,
                     bool txrx,
                     bool verbose);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_PROGRAM_TRACKING_CC_H */
