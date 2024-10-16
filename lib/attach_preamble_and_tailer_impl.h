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

#ifndef INCLUDED_DSLWP_ATTACH_PREAMBLE_AND_TAILER_IMPL_H
#define INCLUDED_DSLWP_ATTACH_PREAMBLE_AND_TAILER_IMPL_H

#include <dslwp/attach_preamble_and_tailer.h>

namespace gr {
  namespace dslwp {

    class attach_preamble_and_tailer_impl : public attach_preamble_and_tailer
    {
     private:
      int d_len_preamble;
      int d_len_tailer;
      unsigned char d_padding_type;
      pmt::pmt_t d_in_port;
      pmt::pmt_t d_out_port;

      void pmt_in_callback(pmt::pmt_t msg);

     public:
      attach_preamble_and_tailer_impl(int len_preamble, int len_tailer, unsigned char padding_type);
      ~attach_preamble_and_tailer_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);

    };

  } // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_ATTACH_PREAMBLE_AND_TAILER_IMPL_H */

