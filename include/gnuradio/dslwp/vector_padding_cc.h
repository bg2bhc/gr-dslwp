/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_VECTOR_PADDING_CC_H
#define INCLUDED_DSLWP_VECTOR_PADDING_CC_H

#include <gnuradio/dslwp/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace dslwp {

/*!
 * \brief <+description of block+>
 * \ingroup dslwp
 *
 */
class DSLWP_API vector_padding_cc : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<vector_padding_cc> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of dslwp::vector_padding_cc.
     *
     * To avoid accidental use of raw pointers, dslwp::vector_padding_cc's
     * constructor is in a private implementation
     * class. dslwp::vector_padding_cc::make is the public interface for
     * creating new instances.
     */
    static sptr make(gr_complex padding, int position, size_t vlen_in, size_t vlen_out);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_VECTOR_PADDING_CC_H */
