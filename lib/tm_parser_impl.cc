/* -*- c++ -*- */
/* 
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
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
#include "tm_parser_impl.h"

#include <stdio.h>
#include <string.h>

extern "C"
{
    #include "dslwp_hk.h"
    #include "sdar_hk.h"
    #include "dslwp_packet_header.h"
}

#define sw16(x) (uint16_t)( ( ( ((uint16_t)x) & ((uint16_t)0x00FFU) ) << 8 ) | ( ( ((uint16_t)x) & ((uint16_t)0xFF00U) ) >> 8 ) )
#define sw32(x) (uint32_t)( ( ( ((uint32_t)x) & ((uint32_t)0x000000FFU) ) << 24 ) | ( ( ((uint32_t)x) & ((uint32_t)0x0000FF00U) ) << 8 ) | ( ( ((uint32_t)x) & ((uint32_t)0x00FF0000U) ) >> 8 ) | ( ( ((uint32_t)x) & ((uint32_t)0xFF000000U) ) >> 24 ) )

namespace gr {
  namespace dslwp {

    tm_parser::sptr
    tm_parser::make()
    {
      return gnuradio::get_initial_sptr
        (new tm_parser_impl());
    }

    /*
     * The private constructor
     */
    tm_parser_impl::tm_parser_impl()
      : gr::block("tm_parser",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0))
    {
	d_in_port = pmt::mp("in");
      	message_port_register_in(d_in_port);
	set_msg_handler(d_in_port, boost::bind(&tm_parser_impl::pmt_in_callback, this ,_1) );
    }

    /*
     * Our virtual destructor.
     */
    tm_parser_impl::~tm_parser_impl()
    {
    }

    void tm_parser_impl::pmt_in_callback(pmt::pmt_t msg)
    {
	pmt::pmt_t meta(pmt::car(msg));
	pmt::pmt_t bytes(pmt::cdr(msg));

	unsigned int i;
	size_t msg_len;
	const uint8_t* bytes_in = pmt::u8vector_elements(bytes, msg_len);
	packet_header_t header;
	
	if(msg_len < 6)
	{
		fprintf(stdout, "\n**** TM Packet Too Short!\n");
	}
	else
	{
		((uint8_t *)&header)[0] = bytes_in[5];
		((uint8_t *)&header)[1] = bytes_in[4];
		((uint8_t *)&header)[2] = bytes_in[3];
		((uint8_t *)&header)[3] = bytes_in[2];
		((uint8_t *)&header)[4] = bytes_in[1];
		((uint8_t *)&header)[5] = bytes_in[0];

		fprintf(stdout, "\n**** TM Packet Header\n");
		fprintf(stdout, "version_number = 0x%02x\n", header.version_number);
		fprintf(stdout, "flag_type = 0x%02x\n", header.flag_type);
		fprintf(stdout, "slave_header_flag = 0x%02x\n", header.slave_header_flag);
		fprintf(stdout, "application_type = 0x%02x\n", header.application_type);
		fprintf(stdout, "nid = 0x%02x\n", header.nid);
		fprintf(stdout, "group_flag = 0x%02x\n", header.group_flag);
		fprintf(stdout, "source_sequence_count = %d\n", header.source_sequence_count);
		fprintf(stdout, "packet_data_len = %d\n", header.packet_data_len);
	
		if( msg_len == header.packet_data_len + LEN_PACKET_HEADER + 1 )
		{
			if(header.application_type == 0)
			{
				uint8_t protocol;
				protocol = bytes_in[LEN_PACKET_HEADER];

				if( ((header.nid == 0x0E)||(header.nid == 0x0F)) && (protocol==0) && (header.packet_data_len == sizeof(hk_uv_t)) )
				{
					hk_uv_t hk_uv;		

					memcpy(&hk_uv, bytes_in+LEN_PACKET_HEADER+1, sizeof(hk_uv_t));
					
					if(header.nid == 0x0E) fprintf(stdout, "\n**** DSLWP V/U Transceiver 0 Telemetry 0\n");
					if(header.nid == 0x0F) fprintf(stdout, "\n**** DSLWP V/U Transceiver 1 Telemetry 0\n");
					fprintf(stdout, "config = 0x%02x\n", hk_uv.config);
					fprintf(stdout, "tx_mode = 0x%02x\n", hk_uv.tx_mode);
					fprintf(stdout, "tx_gain = 0x%02x\n", hk_uv.tx_gain);
					fprintf(stdout, "flag_7021 = 0x%02x\n", hk_uv.flag_7021);
					fprintf(stdout, "n_cmd_buf = 0x%02x\n", hk_uv.n_cmd_buf);
					fprintf(stdout, "n_cmd_dropped = 0x%02x\n", hk_uv.n_cmd_dropped);
					fprintf(stdout, "i_bus_rx = %f\n", ((float)hk_uv.i_bus_rx) * 3.2f);
					fprintf(stdout, "u_bus_rx = %f\n", ((float)hk_uv.u_bus_rx) * 0.16f);
					fprintf(stdout, "i_bus_tx = %f\n", ((float)hk_uv.i_bus_tx) * 3.2f);
					fprintf(stdout, "u_bus_tx = %f\n", ((float)hk_uv.u_bus_tx) * 0.16f);
					fprintf(stdout, "t_pa = %d\n", hk_uv.t_pa);
					fprintf(stdout, "t_tx7021 = 0x%02x\n", hk_uv.t_tx7021);
					fprintf(stdout, "n_422_tx = %d\n", hk_uv.n_422_tx);
					fprintf(stdout, "n_422_rx = %d\n", hk_uv.n_422_rx);
					fprintf(stdout, "n_422_rx_pkg_err = %d\n", hk_uv.n_422_rx_pkg_err);
					fprintf(stdout, "n_422_rx_exe_err = %d\n", hk_uv.n_422_rx_exe_err);
					fprintf(stdout, "cmd_422_last_rx = 0x%02x\n", hk_uv.cmd_422_last_rx);
					fprintf(stdout, "n_rf_tx = %d\n", hk_uv.n_rf_tx);
					fprintf(stdout, "n_rf_tx_dropped = %d\n", hk_uv.n_rf_tx_dropped);
					fprintf(stdout, "n_rf_rx = %d\n", hk_uv.n_rf_rx);
					fprintf(stdout, "n_rf_rx_pkg_err = %d\n", hk_uv.n_rf_rx_pkg_err);
					fprintf(stdout, "n_rf_rx_exe_err = %d\n", hk_uv.n_rf_rx_exe_err);
					fprintf(stdout, "n_rf_rx_fec_err = %d\n", hk_uv.n_rf_rx_fec_err);
					fprintf(stdout, "cmd_rf_last_rx = 0x%02x\n", hk_uv.cmd_rf_last_rx);
					fprintf(stdout, "n_ul = %d\n", sw32(hk_uv.n_ul));
					fprintf(stdout, "fc_tc = 0x%04x\n", hk_uv.fc_tc);
					fprintf(stdout, "fc_ham = 0x%04x\n", hk_uv.fc_ham);
					fprintf(stdout, "rssi_tc = 0x%04x\n", hk_uv.rssi_tc);
					fprintf(stdout, "rssi_ham = 0x%04x\n", hk_uv.rssi_ham);
					fprintf(stdout, "cam_mode = 0x%02x\n", hk_uv.cam_mode);
					fprintf(stdout, "cam_task_flag = 0x%02x\n", hk_uv.cam_task_flag);
					fprintf(stdout, "cam_err_flag = 0x%02x\n", hk_uv.cam_err_flag);
					fprintf(stdout, "cam_pic_len = %d\n", hk_uv.cam_pic_len_2*2048+hk_uv.cam_pic_len_1*256+hk_uv.cam_pic_len_0);
					fprintf(stdout, "n_reset = %d\n", hk_uv.n_reset);
					fprintf(stdout, "flag_reset = 0x%02x\n", hk_uv.flag_reset);
					fprintf(stdout, "flag_sys = 0x%02x\n", hk_uv.flag_sys);
					fprintf(stdout, "n_dma_overflow = %d\n", hk_uv.n_dma_overflow);
					fprintf(stdout, "runtime = %f\n", ((float)sw32(hk_uv.runtime))*0.004f);
				}

				if( (header.nid == 0xA0) && (protocol==0) && (header.packet_data_len == sizeof(hk_tanrus_uv_t)) )
				{
					hk_tanrus_uv_t hk_tanrus_uv;		

					memcpy(&hk_tanrus_uv, bytes_in+LEN_PACKET_HEADER+1, sizeof(hk_tanrus_uv_t));

					fprintf(stdout, "\n**** Tanrus-1 V/U Transceiver Telemetry 0\n");
					fprintf(stdout, "config = 0x%02x\n", 		hk_tanrus_uv.config);
					fprintf(stdout, "flag_direct_ins = 0x%02x\n", 	hk_tanrus_uv.flag_direct_ins);
					fprintf(stdout, "payload_mode = 0x%02x\n", 	hk_tanrus_uv.payload_mode);
					fprintf(stdout, "tx_mode = 0x%02x\n", 		hk_tanrus_uv.tx_mode);
					fprintf(stdout, "gain_tx = %d\n", 		hk_tanrus_uv.gain_tx);
					fprintf(stdout, "i_3v3 = %f\n", 		(float)(hk_tanrus_uv.i_3v3&0x1fff)/10.0f);
					fprintf(stdout, "u_3v3 = %f\n", 		(float)(hk_tanrus_uv.u_3v3&0xfff8)/2000.0f);
					fprintf(stdout, "i_vbat_tx = %f\n", 		(float)(hk_tanrus_uv.i_vbat_tx&0x1fff)/2.5f);
					fprintf(stdout, "u_vbat_tx = %f\n", 		(float)(hk_tanrus_uv.u_vbat_tx&0xfff8)/2000.0f);
					fprintf(stdout, "i_vbat_rx = %f\n", 		(float)(hk_tanrus_uv.i_vbat_rx&0x1fff)/2.5f);
					fprintf(stdout, "u_vbat_rx = %f\n", 		(float)(hk_tanrus_uv.u_vbat_rx&0xfff8)/2000.0f);
					fprintf(stdout, "t_stm32 = 0x%02x\n", 		hk_tanrus_uv.t_stm32);
					fprintf(stdout, "t_pa = %f\n", 			(float)(hk_tanrus_uv.t_pa>>3)/16.0f);
					fprintf(stdout, "n_tx_rf = %d\n", 		hk_tanrus_uv.n_tx_rf);
					fprintf(stdout, "n_rx_rf = %d\n", 		hk_tanrus_uv.n_rx_rf);
					fprintf(stdout, "cmd_rf_last_rx = 0x%02x\n", 	hk_tanrus_uv.cmd_rf_last_rx);
					fprintf(stdout, "n_tx_can = %d\n", 		hk_tanrus_uv.n_tx_can);
					fprintf(stdout, "n_rx_can = %d\n", 		hk_tanrus_uv.n_rx_can);
					fprintf(stdout, "n_tx_err_can = %d\n", 		hk_tanrus_uv.n_tx_err_can);
					fprintf(stdout, "n_rx_err_can = %d\n", 		hk_tanrus_uv.n_rx_err_can);
					fprintf(stdout, "n_tc = %d\n", 			hk_tanrus_uv.n_tc);
					fprintf(stdout, "dc_fm_tc = %d\n", 		hk_tanrus_uv.dc_fm_tc);
					fprintf(stdout, "dc_fm_ham = %d\n", 		hk_tanrus_uv.dc_fm_ham);
					fprintf(stdout, "rssi_fm_tc = %d\n", 		hk_tanrus_uv.rssi_fm_tc);
					fprintf(stdout, "rssi_fm_ham = %d\n", 		hk_tanrus_uv.rssi_fm_ham);
					fprintf(stdout, "reset_flag = 0x%02x\n", 	hk_tanrus_uv.reset_flag);
					fprintf(stdout, "sys_flag = 0x%02x\n", 		hk_tanrus_uv.sys_flag);
					fprintf(stdout, "dma_overflow = %d\n", 		hk_tanrus_uv.dma_overflow);
					fprintf(stdout, "runtime = %f\n", 		hk_tanrus_uv.runtime*0.001);
					fprintf(stdout, "reset_count = %d\n", 		hk_tanrus_uv.reset_count);
					fprintf(stdout, "ctcss_count = %d\n", 		hk_tanrus_uv.ctcss_count);
					fprintf(stdout, "ctcss_det = %f\n", 		hk_tanrus_uv.ctcss_det);
					fprintf(stdout, "avr_adf7021_ld = 0x%02x\n", 	hk_tanrus_uv.avr_adf7021_ld);
					fprintf(stdout, "avr_err_flag = 0x%02x\n", 	hk_tanrus_uv.avr_err_flag);
					fprintf(stdout, "avr_n_tx_232 = %d\n", 		hk_tanrus_uv.avr_n_tx_232);
					fprintf(stdout, "avr_n_rx_232 = %d\n", 		hk_tanrus_uv.avr_n_rx_232);
					fprintf(stdout, "avr_runtime = %f\n", 		hk_tanrus_uv.avr_runtime*0.001);
					fprintf(stdout, "avr_rssi_analog = %d\n", 	hk_tanrus_uv.avr_rssi_analog);
					fprintf(stdout, "avr_n_rssi_const = %d\n", 	hk_tanrus_uv.avr_n_rssi_const);
					fprintf(stdout, "avr_unlock_count = %d\n", 	hk_tanrus_uv.avr_unlock_count);
					fprintf(stdout, "avr_reset_flag = 0x%02x\n", 	hk_tanrus_uv.avr_reset_flag);
					fprintf(stdout, "avr_reset_count = %d\n", 	hk_tanrus_uv.avr_reset_count);
				}

				if( ((header.nid == 0xA6)||(header.nid == 0xA7)) && (protocol==0) && (header.packet_data_len == sizeof(hk_obt_uv_t)) )
				{
					hk_obt_uv_t hk_obt_uv;		

					memcpy(&hk_obt_uv, bytes_in+LEN_PACKET_HEADER+1, sizeof(hk_obt_uv_t));

					fprintf(stdout, "\n**** OBT V/U Transceiver Telemetry 0\n");
					fprintf(stdout, "config = 0x%02x\n", 		hk_obt_uv.config);
					fprintf(stdout, "flag_direct_ins = 0x%02x\n", 	hk_obt_uv.flag_direct_ins);
					fprintf(stdout, "payload_mode = 0x%02x\n", 	hk_obt_uv.payload_mode);
					fprintf(stdout, "tx_mode = 0x%02x\n", 		hk_obt_uv.tx_mode);
					fprintf(stdout, "gain_tx = %d\n", 		hk_obt_uv.gain_tx);
					fprintf(stdout, "i_3v3 = %f\n", 		(float)(hk_obt_uv.i_3v3&0x1fff)/10.0f);
					fprintf(stdout, "u_3v3 = %f\n", 		(float)(hk_obt_uv.u_3v3&0xfff8)/2000.0f);
					fprintf(stdout, "i_vbat_tx = %f\n", 		(float)(hk_obt_uv.i_vbat_tx&0x1fff)/2.5f);
					fprintf(stdout, "u_vbat_tx = %f\n", 		(float)(hk_obt_uv.u_vbat_tx&0xfff8)/2000.0f);
					fprintf(stdout, "i_vbat_rx = %f\n", 		(float)(hk_obt_uv.i_vbat_rx&0x1fff)/2.5f);
					fprintf(stdout, "u_vbat_rx = %f\n", 		(float)(hk_obt_uv.u_vbat_rx&0xfff8)/2000.0f);
					fprintf(stdout, "t_stm32 = 0x%02x\n", 		hk_obt_uv.t_stm32);
					fprintf(stdout, "t_pa = %f\n", 			(float)(hk_obt_uv.t_pa>>3)/16.0f);
					fprintf(stdout, "n_tx_rf = %d\n", 		hk_obt_uv.n_tx_rf);
					fprintf(stdout, "n_rx_rf = %d\n", 		hk_obt_uv.n_rx_rf);
					fprintf(stdout, "cmd_rf_last_rx = 0x%02x\n", 	hk_obt_uv.cmd_rf_last_rx);
					fprintf(stdout, "n_tx_can = %d\n", 		hk_obt_uv.n_tx_can);
					fprintf(stdout, "n_rx_can = %d\n", 		hk_obt_uv.n_rx_can);
					fprintf(stdout, "n_tx_err_can = %d\n", 		hk_obt_uv.n_tx_err_can);
					fprintf(stdout, "n_rx_err_can = %d\n", 		hk_obt_uv.n_rx_err_can);
					fprintf(stdout, "n_tc = %d\n", 			hk_obt_uv.n_tc);
					fprintf(stdout, "dc_fm_tc = %d\n", 		hk_obt_uv.dc_fm_tc);
					fprintf(stdout, "dc_fm_ham = %d\n", 		hk_obt_uv.dc_fm_ham);
					fprintf(stdout, "rssi_fm_tc = %d\n", 		hk_obt_uv.rssi_fm_tc);
					fprintf(stdout, "rssi_fm_ham = %d\n", 		hk_obt_uv.rssi_fm_ham);
					fprintf(stdout, "reset_flag = 0x%02x\n", 	hk_obt_uv.reset_flag);
					fprintf(stdout, "sys_flag = 0x%02x\n", 		hk_obt_uv.sys_flag);
					fprintf(stdout, "dma_overflow = %d\n", 		hk_obt_uv.dma_overflow);
					fprintf(stdout, "runtime = %f\n", 		hk_obt_uv.runtime*0.001);
					fprintf(stdout, "reset_count = %d\n", 		hk_obt_uv.reset_count);
					fprintf(stdout, "ctcss_count = %d\n", 		hk_obt_uv.ctcss_count);
					fprintf(stdout, "antdet1 = 0x%02x\n", 		hk_obt_uv.antdet1);
					fprintf(stdout, "antdet2 = 0x%02x\n", 		hk_obt_uv.antdet2);
					fprintf(stdout, "avr_adf7021_ld = 0x%02x\n", 	hk_obt_uv.avr_adf7021_ld);
					fprintf(stdout, "avr_err_flag = 0x%02x\n", 	hk_obt_uv.avr_err_flag);
					fprintf(stdout, "avr_n_tx_232 = %d\n", 		hk_obt_uv.avr_n_tx_232);
					fprintf(stdout, "avr_n_rx_232 = %d\n", 		hk_obt_uv.avr_n_rx_232);
					fprintf(stdout, "avr_runtime = %f\n", 		hk_obt_uv.avr_runtime*0.001);
					fprintf(stdout, "avr_rssi_analog = %d\n", 	hk_obt_uv.avr_rssi_analog);
					fprintf(stdout, "avr_n_rssi_const = %d\n", 	hk_obt_uv.avr_n_rssi_const);
					fprintf(stdout, "avr_unlock_count = %d\n", 	hk_obt_uv.avr_unlock_count);
					fprintf(stdout, "avr_reset_flag = 0x%02x\n", 	hk_obt_uv.avr_reset_flag);
					fprintf(stdout, "avr_reset_count = %d\n", 	hk_obt_uv.avr_reset_count); 

					if( (hk_obt_uv.antdet1 & 0x80)||(hk_obt_uv.antdet1 & 0x80) )
					{
						fprintf(stdout, "\n**** Warning! Antenna auto deployment ON!!!\n\n");
					}
				}

				if( ((header.nid == 0xA0)||(header.nid == 0xA6)||(header.nid == 0xA7)) && (protocol==1) && (header.packet_data_len == sizeof(Cfg_obt)) )
				{
					Cfg_obt cfg;		

					memcpy(&cfg, bytes_in+LEN_PACKET_HEADER+1, sizeof(Cfg_obt));

					fprintf(stdout, "\n**** SDAR Config Packet\n");
					fprintf(stdout, "gain_tx_HI = %d\n", 		cfg.gain_tx_HI);
					fprintf(stdout, "gain_tx_LO = %d\n", 		cfg.gain_tx_LO);
					fprintf(stdout, "bias_I = %d\n", 		cfg.bias_I);
					fprintf(stdout, "bias_Q = %d\n", 		cfg.bias_Q);
					fprintf(stdout, "threshold_u_vbat_rx_powerdown = %d\n", 		cfg.threshold_u_vbat_rx_powerdown);
					fprintf(stdout, "threshold_u_vbat_rx_repeateroff = %d\n", 		cfg.threshold_u_vbat_rx_repeateroff);
					fprintf(stdout, "threshold_t_pa = %d\n", 	cfg.threshold_t_pa);
					fprintf(stdout, "contious_en = 0x%02x\n", 	cfg.contious_en);
					fprintf(stdout, "cam_ham_en = 0x%02x\n", 	cfg.cam_ham_en);
					fprintf(stdout, "ctcss_en = 0x%02x\n", 		cfg.ctcss_en);
					fprintf(stdout, "ctcss_n_integration = %d\n", 	cfg.ctcss_n_integration);
					fprintf(stdout, "ctcss_n_tail = %d\n", 		cfg.ctcss_n_tail);
					fprintf(stdout, "ctcss_coeff = %f\n", 		cfg.ctcss_coeff);
					fprintf(stdout, "ctcss_threshold = %f\n", 	cfg.ctcss_threshold);
					fprintf(stdout, "gain_fmdm_ham = %f\n", 	cfg.gain_fmdm_ham);
					fprintf(stdout, "gain_fmdm_tc = %f\n", 		cfg.gain_fmdm_tc);
					fprintf(stdout, "interval_hk_OBC = %d\n", 	cfg.interval_hk_OBC);
					fprintf(stdout, "interval_hk_TLM = %d\n", 	cfg.interval_hk_TLM);
					fprintf(stdout, "interval_hk_BEACON = %d\n", 	cfg.interval_hk_BEACON);
					fprintf(stdout, "message = %s\n", 		cfg.message);
					fprintf(stdout, "cam_delay = %d\n", 		cfg.cam_delay);
					fprintf(stdout, "crc = 0x%08x\n", 		cfg.crc);
				}
				if( ((header.nid == 0xA0)||(header.nid == 0xA6)||(header.nid == 0xA7)) && (protocol==2))
				{
					int i;		

					fprintf(stdout, "\n**** SDAR FRAM Packet\ncontents =\n");

					for(i=0; i<header.packet_data_len; i++)
					{
						fprintf(stdout, "0x%02x, ", bytes_in[LEN_PACKET_HEADER+1+i]);
					}
					fprintf(stdout, "\n****************\n");
				}
			}
		}
		else
		{
		
		}
	}
    }

    void
    tm_parser_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }

    int
    tm_parser_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      //const <+ITYPE+> *in = (const <+ITYPE+> *) input_items[0];
      //<+OTYPE+> *out = (<+OTYPE+> *) output_items[0];

      // Do <+signal processing+>
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace dslwp */
} /* namespace gr */

