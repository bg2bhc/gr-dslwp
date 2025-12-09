/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_STEAM_TO_VECTOR_MOVING_WINDOW_CC_H
#define INCLUDED_DSLWP_STEAM_TO_VECTOR_MOVING_WINDOW_CC_H

#include <gnuradio/dslwp/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace dslwp {

/*!
 * \brief <+description of block+>
 * \ingroup dslwp
 *
 */
class DSLWP_API steam_to_vector_moving_window_cc : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<steam_to_vector_moving_window_cc> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of
     * dslwp::steam_to_vector_moving_window_cc.
     *
     * To avoid accidental use of raw pointers, dslwp::steam_to_vector_moving_window_cc's
     * constructor is in a private implementation
     * class. dslwp::steam_to_vector_moving_window_cc::make is the public interface for
     * creating new instances.
     */
    static sptr make(size_t vlen);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_STEAM_TO_VECTOR_MOVING_WINDOW_CC_H */
