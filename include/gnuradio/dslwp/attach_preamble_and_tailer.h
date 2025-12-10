/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_ATTACH_PREAMBLE_AND_TAILER_H
#define INCLUDED_DSLWP_ATTACH_PREAMBLE_AND_TAILER_H

#include <gnuradio/block.h>
#include <gnuradio/dslwp/api.h>

namespace gr {
namespace dslwp {

/*!
 * \brief <+description of block+>
 * \ingroup dslwp
 *
 */
class DSLWP_API attach_preamble_and_tailer : virtual public gr::block
{
public:
    typedef std::shared_ptr<attach_preamble_and_tailer> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of dslwp::attach_preamble_and_tailer.
     *
     * To avoid accidental use of raw pointers, dslwp::attach_preamble_and_tailer's
     * constructor is in a private implementation
     * class. dslwp::attach_preamble_and_tailer::make is the public interface for
     * creating new instances.
     */
    static sptr make(int len_preamble, int len_tailer, unsigned char padding_type);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_ATTACH_PREAMBLE_AND_TAILER_H */
