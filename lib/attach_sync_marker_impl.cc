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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "attach_sync_marker_impl.h"
#include <stdio.h>

namespace gr {
  namespace dslwp {

    attach_sync_marker::sptr
    attach_sync_marker::make(const std::vector<uint8_t> &marker, int data_format)
    {
      return gnuradio::get_initial_sptr
        (new attach_sync_marker_impl(marker, data_format));
    }

    /*
     * The private constructor
     */
    attach_sync_marker_impl::attach_sync_marker_impl(const std::vector<uint8_t> &marker, int data_format)
      : gr::sync_block("attach_sync_marker",
              gr::io_signature::make(0, 0, sizeof(float)),
              gr::io_signature::make(0, 0, sizeof(float))),
d_marker(marker), d_data_format(data_format)
    {
		d_in_port = pmt::mp("in");
      	message_port_register_in(d_in_port);

		d_out_port = pmt::mp("out");	      
      	message_port_register_out(d_out_port);

		set_msg_handler(d_in_port, boost::bind(&attach_sync_marker_impl::pmt_in_callback, this ,_1) );
    }

    /*
     * Our virtual destructor.
     */
    attach_sync_marker_impl::~attach_sync_marker_impl()
    {
    }

    void attach_sync_marker_impl::pmt_in_callback(pmt::pmt_t msg)
    {
		pmt::pmt_t meta(pmt::car(msg));
		pmt::pmt_t bytes(pmt::cdr(msg));

		size_t msg_len;
		const uint8_t* bytes_in = pmt::u8vector_elements(bytes, msg_len);

		switch(d_data_format)
		{
			case 1:
			{
				uint8_t *buffer = (uint8_t *)malloc(sizeof(uint8_t)*(d_marker.size()*8+msg_len));

				for(int i=0; i<d_marker.size(); i++)
				{
					for(int j=0; j<8; j++)
					{
						buffer[i*8+j] = (d_marker[i]&(0x80>>j))?1:0;
					}
				}

				for(int i=0; i<msg_len; i++)
				{
					buffer[d_marker.size()*8+i] = bytes_in[i]?1:0;
				}

				attach_sync_marker_impl::message_port_pub(attach_sync_marker_impl::d_out_port, pmt::cons(pmt::make_dict(), pmt::init_u8vector(d_marker.size()*8+msg_len, buffer)));

				free(buffer);

				break;
			}
			case 2:
			{
				uint8_t *buffer = (uint8_t *)malloc(sizeof(uint8_t)*(d_marker.size()+msg_len));

				for(int i=0; i<d_marker.size(); i++)
				{
					buffer[i] = d_marker[i];
				}

				for(int i=0; i<msg_len; i++)
				{
					buffer[i+d_marker.size()] = bytes_in[i];
				}

				attach_sync_marker_impl::message_port_pub(attach_sync_marker_impl::d_out_port, pmt::cons(pmt::make_dict(), pmt::init_u8vector(d_marker.size()+msg_len, buffer)));

				free(buffer);

				break;
			}
			default:
			{
				fprintf(stdout, "\n**** ERROR: Data format do not match!\n");
			}
		}
    }

    int
    attach_sync_marker_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      return noutput_items;
    }

  } /* namespace dslwp */
} /* namespace gr */

