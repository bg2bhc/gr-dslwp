/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "attach_sync_marker_impl.h"
#include <gnuradio/io_signature.h>
#include <stdio.h>
namespace gr {
namespace dslwp {

attach_sync_marker::sptr attach_sync_marker::make(const std::vector<uint8_t>& marker,
                                                  int data_format,
                                                  int msg_len,
                                                  bool check_length,
                                                  bool pass_other_length)
{
    return gnuradio::make_block_sptr<attach_sync_marker_impl>(
        marker, data_format, msg_len, check_length, pass_other_length);
}


/*
 * The private constructor
 */
attach_sync_marker_impl::attach_sync_marker_impl(const std::vector<uint8_t>& marker,
                                                 int data_format,
                                                 int msg_len,
                                                 bool check_length,
                                                 bool pass_other_length)
    : gr::sync_block("attach_sync_marker",
                     gr::io_signature::make(
                         0 /* min inputs */, 0 /* max inputs */, 0),
                     gr::io_signature::make(
                         0 /* min outputs */, 0 /*max outputs */, 0)),
	d_marker(marker), d_data_format(data_format), d_msg_len(msg_len), d_check_length(check_length), d_pass_other_length(pass_other_length)
{
		d_in_port = pmt::mp("in");
      		message_port_register_in(d_in_port);

		d_out_port = pmt::mp("out");	      
      		message_port_register_out(d_out_port);

		set_msg_handler(d_in_port, [this](pmt::pmt_t msg) { this->pmt_in_callback(msg); });
}

/*
 * Our virtual destructor.
 */
attach_sync_marker_impl::~attach_sync_marker_impl() {}

    void attach_sync_marker_impl::pmt_in_callback(pmt::pmt_t msg)
    {
		pmt::pmt_t meta(pmt::car(msg));
		pmt::pmt_t bytes(pmt::cdr(msg));

		size_t msg_len;
		const uint8_t* bytes_in = pmt::u8vector_elements(bytes, msg_len);

		if(d_check_length)
		{
			if(msg_len != d_msg_len)
			{
				if(d_pass_other_length)
				{
					attach_sync_marker_impl::message_port_pub(attach_sync_marker_impl::d_out_port, pmt::cons(pmt::make_dict(), pmt::init_u8vector(msg_len, bytes_in)));
					fprintf(stdout, "\n**** ASM pass message with length %d!\n", msg_len);
					return;
				}
				else
				{
					fprintf(stdout, "\n**** ERROR: ASM input length do not match!\n");
					return;
				}
			}
		}

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
				fprintf(stdout, "\n**** ERROR: Unknown data format!\n");
			}
		}
    }
int attach_sync_marker_impl::work(int noutput_items,
                                  gr_vector_const_void_star& input_items,
                                  gr_vector_void_star& output_items)
{
    // Do <+signal processing+>

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace dslwp */
} /* namespace gr */
