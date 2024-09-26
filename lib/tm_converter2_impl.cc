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
#include "tm_converter2_impl.h"

namespace gr {
  namespace dslwp {

    tm_converter2::sptr
    tm_converter2::make(const std::string& header, const std::vector<int> &list)
    {
      return gnuradio::get_initial_sptr
        (new tm_converter2_impl(header, list));
    }


    /*
     * The private constructor
     */
    tm_converter2_impl::tm_converter2_impl(const std::string &header, const std::vector<int> &list)
      : gr::block("tm_converter2",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)), d_header(header), d_list(list)
    {
		d_in_port = pmt::mp("in");
      		message_port_register_in(d_in_port);

		d_out_port = pmt::mp("out");	      
      		message_port_register_out(d_out_port);

		set_msg_handler(d_in_port, boost::bind(&tm_converter2_impl::pmt_in_callback, this ,_1) );
    }

    /*
     * Our virtual destructor.
     */
    tm_converter2_impl::~tm_converter2_impl()
    {
    }

    void tm_converter2_impl::pmt_in_callback(pmt::pmt_t msg)
    {
    	pmt::pmt_t meta(pmt::car(msg));
	pmt::pmt_t bytes(pmt::cdr(msg));

	size_t msg_len;
	const uint8_t* bytes_in = pmt::u8vector_elements(bytes, msg_len);
	uint8_t buffer[256];
	
	for(int i=0; i<d_header.size(); i++)
	{
		buffer[i] = d_header[i];
	}
	for(int i=0; i<d_list.size(); i++)
	{
		if(d_list[i]<msg_len)
		{
			buffer[i+d_header.size()] = bytes_in[d_list[i]];
		}
		else
		{
			return;
		}
	}
	
	tm_converter2_impl::message_port_pub(tm_converter2_impl::d_out_port, pmt::cons(pmt::make_dict(), pmt::init_u8vector(d_header.size()+d_list.size(), buffer)));
	return;
    }

    void
    tm_converter2_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }

    int
    tm_converter2_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace dslwp */
} /* namespace gr */

