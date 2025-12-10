/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_STATION_INFO_PDU_IMPL_H
#define INCLUDED_DSLWP_STATION_INFO_PDU_IMPL_H

#include <gnuradio/dslwp/station_info_pdu.h>

namespace gr {
namespace dslwp {

class station_info_pdu_impl : public station_info_pdu
{
private:
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
    station_info_pdu_impl(const std::string& nickname,
                          float lat,
                          float lon,
                          float alt,
                          const std::string& satellite,
                          int physical_channel,
                          int format);
    ~station_info_pdu_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_STATION_INFO_PDU_IMPL_H */
