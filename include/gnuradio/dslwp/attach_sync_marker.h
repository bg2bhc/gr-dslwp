/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_ATTACH_SYNC_MARKER_H
#define INCLUDED_DSLWP_ATTACH_SYNC_MARKER_H

#include <gnuradio/dslwp/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace dslwp {

/*!
 * \brief <+description of block+>
 * \ingroup dslwp
 *
 */
class DSLWP_API attach_sync_marker : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<attach_sync_marker> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of dslwp::attach_sync_marker.
     *
     * To avoid accidental use of raw pointers, dslwp::attach_sync_marker's
     * constructor is in a private implementation
     * class. dslwp::attach_sync_marker::make is the public interface for
     * creating new instances.
     */
    static sptr make(const std::vector<uint8_t>& marker,
                     int data_format,
                     int msg_len,
                     bool check_length,
                     bool pass_other_length);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_ATTACH_SYNC_MARKER_H */
