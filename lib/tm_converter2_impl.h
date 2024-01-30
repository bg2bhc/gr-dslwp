/* -*- c++ -*- */
/*
 * Copyright 2024 gr-dslwp author.
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

#ifndef INCLUDED_DSLWP_TM_CONVERTER2_IMPL_H
#define INCLUDED_DSLWP_TM_CONVERTER2_IMPL_H

#include <dslwp/tm_converter2.h>

namespace gr {
  namespace dslwp {

    class tm_converter2_impl : public tm_converter2
    {
     private:
      pmt::pmt_t d_in_port;
      pmt::pmt_t d_out_port;
      
      void pmt_in_callback(pmt::pmt_t msg);
      
      const std::string d_header;
      const std::vector<int> d_list;

     public:
      tm_converter2_impl(const std::string& header, const std::vector<int> &list);
      ~tm_converter2_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);

    };

  } // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_TM_CONVERTER2_IMPL_H */

