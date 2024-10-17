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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "station_info_pdu_impl.h"

#include <time.h>
#include <stdio.h>
#include <string.h>

namespace gr {
  namespace dslwp {

    station_info_pdu::sptr
    station_info_pdu::make(const std::string& nickname, float lat, float lon, float alt, const std::string& satellite, int physical_channel, int format)
    {
      return gnuradio::get_initial_sptr
        (new station_info_pdu_impl(nickname, lat, lon, alt, satellite, physical_channel, format));
    }


    /*
     * The private constructor
     */
    station_info_pdu_impl::station_info_pdu_impl(const std::string& nickname, float lat, float lon, float alt, const std::string& satellite, int physical_channel, int format)
      : gr::sync_block("station_info_pdu",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)), d_nickname(nickname), d_lat(lat), d_lon(lon), d_alt(alt), d_satellite(satellite), d_physical_channel(physical_channel), d_format(format)
    {
      	d_in_port = pmt::mp("in");
      	message_port_register_in(d_in_port);

      	d_out_port = pmt::mp("out");	      
      	message_port_register_out(d_out_port);

	set_msg_handler(d_in_port, boost::bind(&station_info_pdu_impl::pmt_in_callback, this ,_1) );
    }

    /*
     * Our virtual destructor.
     */
    station_info_pdu_impl::~station_info_pdu_impl()
    {
    }

    void station_info_pdu_impl::pmt_in_callback(pmt::pmt_t msg)
    {
	pmt::pmt_t meta(pmt::car(msg));
	pmt::pmt_t bytes(pmt::cdr(msg));

	size_t msg_len;
	int len_out;
	const uint8_t* bytes_in = pmt::u8vector_elements(bytes, msg_len);
	//uint8_t bytes_out[1024];
	
	if(d_format == 0)
	{
		char buf_json[2048];
		int len_json = sprintf(buf_json, "{\"sat_name\": \"%s\", \"physical_channel\": %d, \"proxy_nickname\": \"%s\", \"proxy_long\": %f, \"proxy_alt\": %f, \"proxy_lat\": %f, \"raw_data\": \"b'", d_satellite.data(), d_physical_channel, d_nickname.data(), d_lon, d_alt, d_lat);

		for(int i=0; i<msg_len; i++)
		{
			len_json += sprintf(buf_json+len_json, "%02x", bytes_in[i]);
		}
		
		len_json += sprintf(buf_json+len_json, "'\", \"proxy_receive_time\": %ld}", time(NULL));
		
		station_info_pdu_impl::message_port_pub(station_info_pdu_impl::d_out_port, pmt::cons(pmt::make_dict(), pmt::init_u8vector(len_json, (const uint8_t *)buf_json)));
	}
	else if(d_format == 1)
	{
		pmt::pmt_t p_dict = pmt::make_dict();
		p_dict = pmt::dict_add(p_dict, pmt::mp("timestamp"), pmt::from_uint64((uint64_t)time(NULL)));
		//p_dict = pmt::dict_add(p_dict, pmt::mp("nickname"), pmt::intern(d_nickname));
		p_dict = pmt::dict_add(p_dict, pmt::mp("lat"), pmt::from_float(d_lat));
		p_dict = pmt::dict_add(p_dict, pmt::mp("lon"), pmt::from_float(d_lon));
		p_dict = pmt::dict_add(p_dict, pmt::mp("alt"), pmt::from_float(d_alt));
		//p_dict = pmt::dict_add(p_dict, pmt::mp("satellite"), pmt::intern(d_satellite));

		station_info_pdu_impl::message_port_pub(station_info_pdu_impl::d_out_port, pmt::cons(p_dict, bytes));
	}
    }
    
    int
    station_info_pdu_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      //const <+ITYPE+> *in = (const <+ITYPE+> *) input_items[0];
      //<+OTYPE+> *out = (<+OTYPE+> *) output_items[0];

      // Do <+signal processing+>

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace dslwp */
} /* namespace gr */

