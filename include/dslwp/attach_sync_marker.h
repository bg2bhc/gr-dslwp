/* -*- c++ -*- */
/* 
 * Copyright 2018 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */


#ifndef INCLUDED_DSLWP_ATTACH_SYNC_MARKER_H
#define INCLUDED_DSLWP_ATTACH_SYNC_MARKER_H

#include <dslwp/api.h>
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
      typedef boost::shared_ptr<attach_sync_marker> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of dslwp::attach_sync_marker.
       *
       * To avoid accidental use of raw pointers, dslwp::attach_sync_marker's
       * constructor is in a private implementation
       * class. dslwp::attach_sync_marker::make is the public interface for
       * creating new instances.
       */
      static sptr make(const std::vector<uint8_t> &marker, int data_format, int msg_len, bool check_length, bool pass_other_length);
    };

  } // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_ATTACH_SYNC_MARKER_H */

