/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_SET_GAIN_BY_TAG_CC_H
#define INCLUDED_DSLWP_SET_GAIN_BY_TAG_CC_H

#include <gnuradio/dslwp/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace dslwp {

/*!
 * \brief <+description of block+>
 * \ingroup dslwp
 *
 */
class DSLWP_API set_gain_by_tag_cc : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<set_gain_by_tag_cc> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of dslwp::set_gain_by_tag_cc.
     *
     * To avoid accidental use of raw pointers, dslwp::set_gain_by_tag_cc's
     * constructor is in a private implementation
     * class. dslwp::set_gain_by_tag_cc::make is the public interface for
     * creating new instances.
     */
    static sptr make(float k, float gain);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_SET_GAIN_BY_TAG_CC_H */
