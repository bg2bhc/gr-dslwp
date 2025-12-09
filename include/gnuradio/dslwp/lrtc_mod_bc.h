/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_LRTC_MOD_BC_H
#define INCLUDED_DSLWP_LRTC_MOD_BC_H

#include <gnuradio/dslwp/api.h>
#include <gnuradio/sync_interpolator.h>

namespace gr {
namespace dslwp {

/*!
 * \brief <+description of block+>
 * \ingroup dslwp
 *
 */
class DSLWP_API lrtc_mod_bc : virtual public gr::sync_interpolator
{
public:
    typedef std::shared_ptr<lrtc_mod_bc> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of dslwp::lrtc_mod_bc.
     *
     * To avoid accidental use of raw pointers, dslwp::lrtc_mod_bc's
     * constructor is in a private implementation
     * class. dslwp::lrtc_mod_bc::make is the public interface for
     * creating new instances.
     */
    static sptr make();
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_LRTC_MOD_BC_H */
