/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "ccsds_pseudo_randomizer_impl.h"
#include <gnuradio/io_signature.h>
#include <stdio.h>
namespace gr {
namespace dslwp {

ccsds_pseudo_randomizer::sptr ccsds_pseudo_randomizer::make(int data_format)
{
    return gnuradio::make_block_sptr<ccsds_pseudo_randomizer_impl>(data_format);
}


/*
 * The private constructor
 */
ccsds_pseudo_randomizer_impl::ccsds_pseudo_randomizer_impl(int data_format)
    : gr::sync_block("ccsds_pseudo_randomizer",
                     gr::io_signature::make(
                         0 /* min inputs */, 0 /* max inputs */, 0),
                     gr::io_signature::make(
                         0 /* min outputs */, 0 /*max outputs */, 0)),
	d_data_format(data_format)
{
		d_in_port = pmt::mp("in");
      	message_port_register_in(d_in_port);

		d_out_port = pmt::mp("out");	      
      	message_port_register_out(d_out_port);

		set_msg_handler(d_in_port, [this](pmt::pmt_t msg) { this->pmt_in_callback(msg); } );
}

/*
 * Our virtual destructor.
 */
ccsds_pseudo_randomizer_impl::~ccsds_pseudo_randomizer_impl() {}

    void ccsds_pseudo_randomizer_impl::pmt_in_callback(pmt::pmt_t msg)
    {
		pmt::pmt_t meta(pmt::car(msg));
		pmt::pmt_t bytes(pmt::cdr(msg));		

		switch(d_data_format)
		{
			case 1:
			{
				size_t msg_len;
				const uint8_t* bits_in = pmt::u8vector_elements(bytes, msg_len);

				uint8_t *buffer = (uint8_t *)malloc(sizeof(uint8_t)*msg_len);

				for(int i=0; i<msg_len; i++)
				{
					buffer[i] = (sequence[(i/8)%255]&(0x80>>(i%8))) ? !bits_in[i] : bits_in[i];
				}

				ccsds_pseudo_randomizer_impl::message_port_pub(ccsds_pseudo_randomizer_impl::d_out_port, pmt::cons(meta, pmt::init_u8vector(msg_len, buffer)));

				free(buffer);

				break;
			}
			case 2:
			{				
				size_t msg_len;
				const uint8_t* bytes_in = pmt::u8vector_elements(bytes, msg_len);

				uint8_t *buffer = (uint8_t *)malloc(sizeof(uint8_t)*msg_len);

				for(int i=0; i<msg_len; i++)
				{
					buffer[i] = bytes_in[i] ^ sequence[i%255];
				}

				ccsds_pseudo_randomizer_impl::message_port_pub(ccsds_pseudo_randomizer_impl::d_out_port, pmt::cons(meta, pmt::init_u8vector(msg_len, buffer)));

				free(buffer);

				break;
			}
			case 3:
			{
				size_t msg_len;
				const float* bits_in = pmt::f32vector_elements(bytes, msg_len);

				float *buffer = (float *)malloc(sizeof(float)*msg_len);

				for(int i=0; i<msg_len; i++)
				{
					buffer[i] = (sequence[(i/8)%255]&(0x80>>(i%8))) ? -bits_in[i] : bits_in[i];
				}

				ccsds_pseudo_randomizer_impl::message_port_pub(ccsds_pseudo_randomizer_impl::d_out_port, pmt::cons(meta, pmt::init_f32vector(msg_len, buffer)));

				free(buffer);

				break;
			}
			default:
			{
				fprintf(stdout, "\n**** ERROR: Unknown data format!\n");
			}
		}
    }
int ccsds_pseudo_randomizer_impl::work(int noutput_items,
                                       gr_vector_const_void_star& input_items,
                                       gr_vector_void_star& output_items)
{
    // Do <+signal processing+>

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace dslwp */
} /* namespace gr */
