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
#include "tag_to_json_pdu_c_impl.h"
#include <stdio.h>

namespace gr {
  namespace dslwp {

    tag_to_json_pdu_c::sptr
    tag_to_json_pdu_c::make(const std::string &key)
    {
      return gnuradio::get_initial_sptr
        (new tag_to_json_pdu_c_impl(key));
    }


    /*
     * The private constructor
     */
    tag_to_json_pdu_c_impl::tag_to_json_pdu_c_impl(const std::string &key)
      : gr::sync_block("tag_to_json_pdu_c",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(0, 0, 0))
    {
		d_key = key;
		p_key = pmt::mp(key);
		d_out_port = pmt::mp("out");
		message_port_register_out(d_out_port);
    }

    /*
     * Our virtual destructor.
     */
    tag_to_json_pdu_c_impl::~tag_to_json_pdu_c_impl()
    {
    }

    int
    tag_to_json_pdu_c_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];

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

