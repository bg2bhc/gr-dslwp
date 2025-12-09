/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "tag_to_json_pdu_c_impl.h"
#include <gnuradio/io_signature.h>
#include <stdio.h>

namespace gr {
namespace dslwp {

using input_type = gr_complex;
tag_to_json_pdu_c::sptr tag_to_json_pdu_c::make(const std::string& key)
{
    return gnuradio::make_block_sptr<tag_to_json_pdu_c_impl>(key);
}


/*
 * The private constructor
 */
tag_to_json_pdu_c_impl::tag_to_json_pdu_c_impl(const std::string& key)
    : gr::sync_block("tag_to_json_pdu_c",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
                     gr::io_signature::make(
                         0 /* min outputs */, 0 /*max outputs */, 0))
{
		d_key = key;
		p_key = pmt::mp(key);
		d_out_port = pmt::mp("out");
		message_port_register_out(d_out_port);
}

/*
 * Our virtual destructor.
 */
tag_to_json_pdu_c_impl::~tag_to_json_pdu_c_impl() {}

int tag_to_json_pdu_c_impl::work(int noutput_items,
                                 gr_vector_const_void_star& input_items,
                                 gr_vector_void_star& output_items)
{
    auto in = static_cast<const input_type*>(input_items[0]);
    // Do <+signal processing+>
      std::vector<tag_t> tags;
      get_tags_in_window(tags, 0, 0, noutput_items);

      for(int j=0; j<tags.size(); j++)
      {
            if(tags[j].key == p_key)
            {
                  if(pmt::is_real(tags[j].value))
                  {
                        double value = pmt::to_double(tags[j].value);
                        pmt::pmt_t p_dict = pmt::make_dict();
                        p_dict = pmt::dict_add(p_dict, p_key, tags[j].value);
                        char buf_json[100];
                        int  len_json = sprintf(buf_json, "{\"%s\": %f}", d_key.c_str(), value);
                        
                        if(len_json != -1)
                        {
                        	tag_to_json_pdu_c_impl::message_port_pub(tag_to_json_pdu_c_impl::d_out_port, pmt::cons(p_dict, pmt::init_u8vector(len_json, (const uint8_t *)buf_json)));
                        }
                  }
            }
      }
    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace dslwp */
} /* namespace gr */
