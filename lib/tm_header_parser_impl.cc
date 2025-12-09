/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "tm_header_parser_impl.h"
#include <gnuradio/io_signature.h>
extern "C"
{
    #include "telemetry/dslwp_tm_header.h"
}
namespace gr {
namespace dslwp {


tm_header_parser::sptr tm_header_parser::make()
{
    return gnuradio::make_block_sptr<tm_header_parser_impl>();
}


/*
 * The private constructor
 */
tm_header_parser_impl::tm_header_parser_impl()
    : gr::block("tm_header_parser",
                gr::io_signature::make(
                    0 /* min inputs */, 0 /* max inputs */, sizeof(char)),
                gr::io_signature::make(
                    0 /* min outputs */, 0 /*max outputs */, sizeof(char)))
{
	d_in_port = pmt::mp("in");
      	message_port_register_in(d_in_port);

	d_out_port_0 = pmt::mp("out 0");	      
      	message_port_register_out(d_out_port_0);

	d_out_port_1 = pmt::mp("out 1");	      
      	message_port_register_out(d_out_port_1);

	d_out_port_2 = pmt::mp("out 2");	      
      	message_port_register_out(d_out_port_2);

	d_out_port_3 = pmt::mp("out 3");	      
      	message_port_register_out(d_out_port_3);

	set_msg_handler(d_in_port, [this](pmt::pmt_t msg) { this->pmt_in_callback(msg); } );
}

/*
 * Our virtual destructor.
 */
tm_header_parser_impl::~tm_header_parser_impl() {}

void tm_header_parser_impl::forecast(int noutput_items,
                                     gr_vector_int& ninput_items_required)
{
    /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
}

void tm_header_parser_impl::pmt_in_callback(pmt::pmt_t msg)
{
	pmt::pmt_t meta(pmt::car(msg));
	pmt::pmt_t bytes(pmt::cdr(msg));

	unsigned int i;
	size_t msg_len;
	tm_header_t header;
	const uint8_t* bytes_in = pmt::u8vector_elements(bytes, msg_len);

	if(msg_len>=LEN_TM_HEADER)
	{
		((uint8_t *)&header)[0] = bytes_in[4];
		((uint8_t *)&header)[1] = bytes_in[3];
		((uint8_t *)&header)[2] = bytes_in[2];
		((uint8_t *)&header)[3] = bytes_in[1];
		((uint8_t *)&header)[4] = bytes_in[0];

		fprintf(stdout, "\n**** TM Frame Header\n");

		fprintf(stdout, "version_number = 0x%x\n", header.version_number);
		fprintf(stdout, "spacecraft_id = 0x%x\n", header.spacecraft_id);
		fprintf(stdout, "virtual_channel_id = 0x%x\n", header.virtual_channel_id);
		fprintf(stdout, "spare = 0x%x\n", header.spare);
		fprintf(stdout, "master_frame_count = %d\n", header.master_frame_count);
		fprintf(stdout, "virtual_channel_frame_count = %d\n", header.virtual_channel_frame_count);
		fprintf(stdout, "first_header_pointer = %d\n", header.first_header_pointer);

		switch(header.virtual_channel_id)
		{
			case 0:
			{
				tm_header_parser_impl::message_port_pub(tm_header_parser_impl::d_out_port_0, pmt::cons(pmt::make_dict(), pmt::init_u8vector(msg_len-LEN_TM_HEADER, (const uint8_t *)bytes_in+LEN_TM_HEADER)));
				break;
			}
			case 1:
			{
				tm_header_parser_impl::message_port_pub(tm_header_parser_impl::d_out_port_1, pmt::cons(pmt::make_dict(), pmt::init_u8vector(msg_len-LEN_TM_HEADER, (const uint8_t *)bytes_in+LEN_TM_HEADER)));
				break;
			}
			case 2:
			{
				tm_header_parser_impl::message_port_pub(tm_header_parser_impl::d_out_port_2, pmt::cons(pmt::make_dict(), pmt::init_u8vector(msg_len-LEN_TM_HEADER, (const uint8_t *)bytes_in+LEN_TM_HEADER)));
				break;
			}
			case 3:
			{
				tm_header_parser_impl::message_port_pub(tm_header_parser_impl::d_out_port_3, pmt::cons(pmt::make_dict(), pmt::init_u8vector(msg_len-LEN_TM_HEADER, (const uint8_t *)bytes_in+LEN_TM_HEADER)));
				break;
			}
		}
	}
	else
	{
		fprintf(stdout, "\n**** TM Frame Error: Too short PDU\n");
	}
}
int tm_header_parser_impl::general_work(int noutput_items,
                                        gr_vector_int& ninput_items,
                                        gr_vector_const_void_star& input_items,
                                        gr_vector_void_star& output_items)
{
    // Do <+signal processing+>
    // Tell runtime system how many input items we consumed on
    // each input stream.
    consume_each(noutput_items);

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace dslwp */
} /* namespace gr */
