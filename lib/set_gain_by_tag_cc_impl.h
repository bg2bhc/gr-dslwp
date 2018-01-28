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

#ifndef INCLUDED_DSLWP_SET_GAIN_BY_TAG_CC_IMPL_H
#define INCLUDED_DSLWP_SET_GAIN_BY_TAG_CC_IMPL_H

#include <dslwp/set_gain_by_tag_cc.h>

namespace gr {
  namespace dslwp {

    class set_gain_by_tag_cc_impl : public set_gain_by_tag_cc
    {
     private:
      float d_k;
      float d_gain;

     public:
      set_gain_by_tag_cc_impl(float k, float gain);
      ~set_gain_by_tag_cc_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_SET_GAIN_BY_TAG_CC_IMPL_H */

