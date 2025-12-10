/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "frame_spliter_c_impl.h"
#include <gnuradio/io_signature.h>
#include <stdio.h>
#include <cmath>
namespace gr {
namespace dslwp {

using input_type = gr_complex;
frame_spliter_c::sptr frame_spliter_c::make(const std::string& key, int frame_length)
{
    return gnuradio::make_block_sptr<frame_spliter_c_impl>(key, frame_length);
}


/*
 * The private constructor
 */
frame_spliter_c_impl::frame_spliter_c_impl(const std::string& key, int frame_length)
    : gr::sync_block("frame_spliter_c",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
                     gr::io_signature::make(
                         0 /* min outputs */, 0 /*max outputs */, 0)),
	d_frame_length(frame_length)
{
		d_out_port = pmt::mp("out");
		d_key = pmt::mp(key);
		message_port_register_out(d_out_port);
		d_bits_in = -1;
		d_payload = (float *)malloc(sizeof(float)*frame_length);
		d_eb_n0_est = NAN;
}

/*
 * Our virtual destructor.
 */
frame_spliter_c_impl::~frame_spliter_c_impl() {}

int frame_spliter_c_impl::work(int noutput_items,
                               gr_vector_const_void_star& input_items,
                               gr_vector_void_star& output_items)
{
    auto in = static_cast<const input_type*>(input_items[0]);
    // Do <+signal processing+>
      for(int i=0; i<noutput_items; i++)
      {
		std::vector<tag_t> tags;
		get_tags_in_window(tags, 0, i, i+1);

		for(int j=0; j<tags.size(); j++)
		{
			if(tags[j].key == d_key)
			{
				if(d_bits_in<0)
				{
					d_bits_in = 0;
				}
				else
				{
					fprintf(stdout, "\n**** Warning: New frame attemption before end of frame!\n");
				}
			}
			else if(tags[j].key == pmt::mp("eb_n0_est"))
			{
				if(pmt::is_real(tags[j].value))
				{
					d_eb_n0_est = pmt::to_double(tags[j].value);
				}
			}
		}

		if(d_bits_in>=0)
		{
			d_payload[d_bits_in++] = in[i].real();

			if(d_bits_in >= d_frame_length)
			{
				pmt::pmt_t p_dict = pmt::make_dict();
				if(!std::isnan(d_eb_n0_est))
				{
					p_dict = pmt::dict_add(p_dict, pmt::mp("eb_n0_est"), pmt::from_double(d_eb_n0_est));
				}
				frame_spliter_c_impl::message_port_pub(frame_spliter_c_impl::d_out_port, pmt::cons(p_dict, pmt::init_f32vector(d_frame_length, d_payload)));
				d_bits_in = -1;
				continue;
			}

			d_payload[d_bits_in++] = in[i].imag();

			if(d_bits_in >= d_frame_length)
			{
				pmt::pmt_t p_dict = pmt::make_dict();
				if(!std::isnan(d_eb_n0_est))
				{
					p_dict = pmt::dict_add(p_dict, pmt::mp("eb_n0_est"), pmt::from_double(d_eb_n0_est));
				}
				frame_spliter_c_impl::message_port_pub(frame_spliter_c_impl::d_out_port, pmt::cons(p_dict, pmt::init_f32vector(d_frame_length, d_payload)));
				d_bits_in = -1;
			}
		}

      }
    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace dslwp */
} /* namespace gr */
