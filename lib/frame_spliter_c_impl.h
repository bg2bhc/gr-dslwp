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

#ifndef INCLUDED_DSLWP_FRAME_SPLITER_C_IMPL_H
#define INCLUDED_DSLWP_FRAME_SPLITER_C_IMPL_H

#include <dslwp/frame_spliter_c.h>

namespace gr {
  namespace dslwp {

    class frame_spliter_c_impl : public frame_spliter_c
    {
     private:
      pmt::pmt_t d_out_port;
      pmt::pmt_t d_key;
      int d_frame_length;
      int d_bits_in;
      float *d_payload;
      float d_eb_n0_est;

     public:
      frame_spliter_c_impl(const std::string &key, int frame_length);
      ~frame_spliter_c_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_FRAME_SPLITER_C_IMPL_H */

