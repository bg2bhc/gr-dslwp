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

#ifndef INCLUDED_DSLWP_ATTACH_SYNC_MARKER_IMPL_H
#define INCLUDED_DSLWP_ATTACH_SYNC_MARKER_IMPL_H

#include <dslwp/attach_sync_marker.h>

namespace gr {
  namespace dslwp {

    class attach_sync_marker_impl : public attach_sync_marker
    {
     private:
      pmt::pmt_t d_in_port;
      pmt::pmt_t d_out_port;
      const std::vector<uint8_t> d_marker;
      int d_data_format;
      int d_msg_len;
      bool d_check_length;
      bool d_pass_other_length;

      void pmt_in_callback(pmt::pmt_t msg);

     public:
      attach_sync_marker_impl(const std::vector<uint8_t> &marker, int data_format, int msg_len, bool check_length, bool pass_other_length);
      ~attach_sync_marker_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_ATTACH_SYNC_MARKER_IMPL_H */

