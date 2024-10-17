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

#ifndef INCLUDED_DSLWP_STATION_INFO_PDU_IMPL_H
#define INCLUDED_DSLWP_STATION_INFO_PDU_IMPL_H

#include <dslwp/station_info_pdu.h>

namespace gr {
  namespace dslwp {

    class station_info_pdu_impl : public station_info_pdu
    {
     private:
      // Nothing to declare in this block.
      pmt::pmt_t d_in_port;
      pmt::pmt_t d_out_port;
      const std::string d_nickname;
      float d_lat;
      float d_lon;
      float d_alt;
      const std::string d_satellite;
      int d_physical_channel;
      int d_format;
      
      void pmt_in_callback(pmt::pmt_t msg);

     public:
      station_info_pdu_impl(const std::string& nickname, float lat, float lon, float alt, const std::string& satellite, int physical_channel, int format);
      ~station_info_pdu_impl();

      // Where all the action really happens
      int work(
              int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items
      );
    };

  } // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_STATION_INFO_PDU_IMPL_H */

