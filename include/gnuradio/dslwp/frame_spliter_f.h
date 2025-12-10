/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_FRAME_SPLITER_F_H
#define INCLUDED_DSLWP_FRAME_SPLITER_F_H

#include <gnuradio/block.h>
#include <gnuradio/dslwp/api.h>

namespace gr {
namespace dslwp {

/*!
 * \brief <+description of block+>
 * \ingroup dslwp
 *
 */
class DSLWP_API frame_spliter_f : virtual public gr::block
{
public:
    typedef std::shared_ptr<frame_spliter_f> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of dslwp::frame_spliter_f.
     *
     * To avoid accidental use of raw pointers, dslwp::frame_spliter_f's
     * constructor is in a private implementation
     * class. dslwp::frame_spliter_f::make is the public interface for
     * creating new instances.
     */
    static sptr make(const std::string& key, int frame_length);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_FRAME_SPLITER_F_H */
