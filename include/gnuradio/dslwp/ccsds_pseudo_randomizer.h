/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_CCSDS_PSEUDO_RANDOMIZER_H
#define INCLUDED_DSLWP_CCSDS_PSEUDO_RANDOMIZER_H

#include <gnuradio/dslwp/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace dslwp {

/*!
 * \brief <+description of block+>
 * \ingroup dslwp
 *
 */
class DSLWP_API ccsds_pseudo_randomizer : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<ccsds_pseudo_randomizer> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of dslwp::ccsds_pseudo_randomizer.
     *
     * To avoid accidental use of raw pointers, dslwp::ccsds_pseudo_randomizer's
     * constructor is in a private implementation
     * class. dslwp::ccsds_pseudo_randomizer::make is the public interface for
     * creating new instances.
     */
    static sptr make(int data_format);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_CCSDS_PSEUDO_RANDOMIZER_H */
