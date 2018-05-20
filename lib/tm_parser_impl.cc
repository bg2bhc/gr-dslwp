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
    #include "telemetry/dslwp_hk.h"
    #include "telemetry/sdar_hk.h"
    #include "telemetry/dslwp_packet_header.h"
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
					
					if(header.nid == 0x0E) fprintf(stdout, "\n**** DSLWP V/U Transceiver 0 Telemetry\n");
					if(header.nid == 0x0F) fprintf(stdout, "\n**** DSLWP V/U Transceiver 1 Telemetry\n");
					fprintf(stdout, "config = 0x%02x\n", hk_uv.config);
					fprintf(stdout, "flag_rx = 0x%02x\n", hk_uv.flag_rx);
					fprintf(stdout, "tx_gain = 0x%02x\n", hk_uv.tx_gain);
					fprintf(stdout, "tx_modulation = 0x%02x\n", hk_uv.tx_modulation);
					fprintf(stdout, "flag_tx = 0x%02x\n", hk_uv.flag_tx);
					fprintf(stdout, "flag_7021 = 0x%02x\n", hk_uv.flag_7021);
					fprintf(stdout, "n_cmd_buf = 0x%02x\n", hk_uv.n_cmd_buf);
					fprintf(stdout, "n_cmd_dropped = 0x%02x\n", hk_uv.n_cmd_dropped);
					fprintf(stdout, "i_bus_rx = %f\n", ((float)hk_uv.i_bus_rx) * 3.2f);
					fprintf(stdout, "u_bus_rx = %f\n", ((float)hk_uv.u_bus_rx) * 0.16f);
					fprintf(stdout, "i_bus_tx = %f\n", ((float)hk_uv.i_bus_tx) * 3.2f);
					fprintf(stdout, "u_bus_tx = %f\n", ((float)hk_uv.u_bus_tx) * 0.16f);
					fprintf(stdout, "t_pa = %d\n", hk_uv.t_pa);
					fprintf(stdout, "t_tx7021 = 0x%02x\n", hk_uv.t_tx7021);
					fprintf(stdout, "n_jt4_tx = %d\n", hk_uv.n_jt4_tx);
					fprintf(stdout, "n_ham_rx = %d\n", hk_uv.n_ham_rx);
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
					fprintf(stdout, "byte_corr = %d\n", hk_uv.byte_corr);
					fprintf(stdout, "n_cmd = %d\n", hk_uv.n_cmd);
					fprintf(stdout, "fc_asm = %f\n", ((int16_t)sw16(hk_uv.fc_asm))/32768.0f*3.1416f);
					fprintf(stdout, "snr_asm = %f\n", sw16(hk_uv.snr_asm)/256.0f);

					float gain_agc;
					switch(hk_uv.flag_agc)
					{
						case 0:
						{
							gain_agc =43.0f;
							break;
						}
						case 1:
						{
							gain_agc =33.0f;
							break;		
						}
						case 2:
						{
							gain_agc =26.0f;
							break;
						}
						case 4:
						{
							gain_agc =29.0f;
							break;
						}
						case 5:
						{
							gain_agc =19.0f;
							break;		
						}
						case 6:
						{
							gain_agc =12.0f;
							break;		
						}
						case 8:
						{
							gain_agc =17.0f;
							break;		
						}
						case 9:
						{
							gain_agc =7.0f;
							break;		
						}
						case 10:
						{
							gain_agc =0.0f;
							break;		
						}
					}

					fprintf(stdout, "rssi_asm = %f\n", -174.0f+sw16(hk_uv.rssi_asm)/10.0f+gain_agc);
					fprintf(stdout, "rssi_channel = %f\n", -174.0f+sw16(hk_uv.rssi_channel)/10.0f+gain_agc);
					fprintf(stdout, "rssi_7021 = %f (%d)\n", -140.0f+hk_uv.rssi_7021*0.5f+gain_agc, hk_uv.rssi_7021);
					fprintf(stdout, "flag_agc = 0x%02x (%d)\n", hk_uv.flag_agc, (int)gain_agc);
					fprintf(stdout, "seconds_since_epoch = %d\n", sw32(hk_uv.seconds_since_epoch));
					fprintf(stdout, "cam_mode = 0x%02x\n", hk_uv.cam_mode);
					fprintf(stdout, "cam_task_flag = 0x%02x\n", hk_uv.cam_task_flag);
					fprintf(stdout, "cam_err_flag = 0x%02x\n", hk_uv.cam_err_flag);
					fprintf(stdout, "cam_pic_len = %d\n", hk_uv.cam_pic_len_2*65536+hk_uv.cam_pic_len_1*256+hk_uv.cam_pic_len_0);
					fprintf(stdout, "cam_memory_id = %d\n", hk_uv.cam_memory_id);
					fprintf(stdout, "jt4_task_flag = 0x%02x\n", hk_uv.jt4_task_flag);
					fprintf(stdout, "n_reset = %d\n", hk_uv.n_reset);
					fprintf(stdout, "flag_reset = 0x%02x\n", hk_uv.flag_reset);
					fprintf(stdout, "flag_sys = 0x%02x\n", hk_uv.flag_sys);
					fprintf(stdout, "n_dma_overflow = %d\n", hk_uv.n_dma_overflow);
					fprintf(stdout, "runtime = %f\n", ((float)sw32(hk_uv.runtime))*0.004f);

					fprintf(stdout, "message = \"");
					for(int i=0; i<8; i++) fprintf(stdout, "%c", hk_uv.message[i]);
					fprintf(stdout, "\"\n");
				}

				if( ((header.nid == 0x0E)||(header.nid == 0x0F)) && (protocol==1) && (header.packet_data_len == sizeof(cfg_cam_t)) )
				{
					cfg_cam_t cfg_cam;		

					memcpy(&cfg_cam, bytes_in+LEN_PACKET_HEADER+1, sizeof(cfg_cam_t));
					
					if(header.nid == 0x0E) fprintf(stdout, "\n**** DSLWP V/U Transceiver 0 Camera Config\n");
					if(header.nid == 0x0F) fprintf(stdout, "\n**** DSLWP V/U Transceiver 1 Camera Config\n");
					fprintf(stdout, "size = 0x%02x\n", cfg_cam.size);
					fprintf(stdout, "brightness = 0x%02x\n", cfg_cam.brightness);
					fprintf(stdout, "contrast = 0x%02x\n", cfg_cam.contrast);
					fprintf(stdout, "sharpness = 0x%02x\n", cfg_cam.sharpness);
					fprintf(stdout, "exposure = 0x%02x\n", cfg_cam.exposure);
					fprintf(stdout, "compressing = 0x%02x\n", cfg_cam.compressing);
					fprintf(stdout, "colour = 0x%02x\n", cfg_cam.colour);
					fprintf(stdout, "config = 0x%02x\n", cfg_cam.config);
					fprintf(stdout, "id = 0x%02x\n", cfg_cam.id);
				}

				if( (header.nid == 0xAC) && (protocol==0) && (header.packet_data_len == sizeof(hk_wod_t)) )
				{
					hk_wod_t hk_wod;		

					memcpy(&hk_wod, bytes_in+LEN_PACKET_HEADER+1, sizeof(hk_wod_t));

					fprintf(stdout, "\n**** DSLWP WOD\n");
					fprintf(stdout, "seconds_since_epoch = %d\n", sw32(hk_wod.seconds_since_epoch));
					fprintf(stdout, "n_cmd_exe = %d\n", hk_wod.n_cmd_exe);
					fprintf(stdout, "n_cmd_delay = %d\n", hk_wod.n_cmd_delay);
					fprintf(stdout, "this_wdt_timeout_count = %d\n", hk_wod.this_wdt_timeout_count);
					fprintf(stdout, "that_wdt_timeout_count = %d\n", hk_wod.that_wdt_timeout_count);
					fprintf(stdout, "sta_reset_count = %d\n", hk_wod.sta_reset_count);
					fprintf(stdout, "stb_reset_count = %d\n", hk_wod.stb_reset_count);
					fprintf(stdout, "ss_reset_count = %d\n", hk_wod.ss_reset_count);
					fprintf(stdout, "is_reset_count = %d\n", hk_wod.is_reset_count);
					fprintf(stdout, "pl_task_err_flag = %d\n", hk_wod.pl_task_err_flag);
					fprintf(stdout, "hsd_task_err_flag = %d\n", hk_wod.hsd_task_err_flag);
					fprintf(stdout, "tc_wdt_timeout_period = %d\n", hk_wod.tc_wdt_timeout_period);
					fprintf(stdout, "v_bus = %d\n", sw16(hk_wod.v_bus));
					fprintf(stdout, "v_battery = %d\n", sw16(hk_wod.v_battery));
					fprintf(stdout, "i_solar_panel = %d\n", sw16(hk_wod.i_solar_panel));
					fprintf(stdout, "i_load = %d\n", sw16(hk_wod.i_load));
					fprintf(stdout, "i_bus = %d\n", sw16(hk_wod.i_bus));
					fprintf(stdout, "sw_flag_1 = %02x\n", hk_wod.sw_flag_1);
					fprintf(stdout, "sw_flag_2 = %02x\n", hk_wod.sw_flag_2);
					fprintf(stdout, "sw_flag_3 = %02x\n", hk_wod.sw_flag_3);
					fprintf(stdout, "sw_flag_4 = %02x\n", hk_wod.sw_flag_4);
					fprintf(stdout, "sta_q0 = %d\n", sw32(hk_wod.sta_q0));
					fprintf(stdout, "sta_q1 = %d\n", sw32(hk_wod.sta_q1));
					fprintf(stdout, "sta_q2 = %d\n", sw32(hk_wod.sta_q2));
					fprintf(stdout, "sta_q3 = %d\n", sw32(hk_wod.sta_q3));
					fprintf(stdout, "sta_flag = %d\n", hk_wod.sta_flag);
					fprintf(stdout, "stb_q0 = %d\n", sw32(hk_wod.stb_q0));
					fprintf(stdout, "stb_q1 = %d\n", sw32(hk_wod.stb_q1));
					fprintf(stdout, "stb_q2 = %d\n", sw32(hk_wod.stb_q2));
					fprintf(stdout, "stb_q3 = %d\n", sw32(hk_wod.stb_q3));
					fprintf(stdout, "stb_flag = %d\n", hk_wod.stb_flag);
					fprintf(stdout, "stc_q0 = %d\n", sw32(hk_wod.stc_q0));
					fprintf(stdout, "stc_q1 = %d\n", sw32(hk_wod.stc_q1));
					fprintf(stdout, "stc_q2 = %d\n", sw32(hk_wod.stc_q2));
					fprintf(stdout, "stc_q3 = %d\n", sw32(hk_wod.stc_q3));
					fprintf(stdout, "stc_flag = %d\n", hk_wod.stc_flag);
					fprintf(stdout, "ss_x = %d\n", sw32(hk_wod.ss_x));
					fprintf(stdout, "ss_y = %d\n", sw32(hk_wod.ss_y));
					fprintf(stdout, "ss_flag = %d\n", hk_wod.ss_flag);
					fprintf(stdout, "fwx_rate = %d\n", sw16(hk_wod.fwx_rate));
					fprintf(stdout, "fwx_cmd = %d\n", sw16(hk_wod.fwx_cmd));
					fprintf(stdout, "fwy_rate = %d\n", sw16(hk_wod.fwy_rate));
					fprintf(stdout, "fwy_cmd = %d\n", sw16(hk_wod.fwy_cmd));
					fprintf(stdout, "fwz_rate = %d\n", sw16(hk_wod.fwz_rate));
					fprintf(stdout, "fwz_cmd = %d\n", sw16(hk_wod.fwz_cmd));
					fprintf(stdout, "gyro_x = %d\n", sw32(hk_wod.gyro_x));
					fprintf(stdout, "gyro_y = %d\n", sw32(hk_wod.gyro_y));
					fprintf(stdout, "gyro_z = %d\n", sw32(hk_wod.gyro_z));
					fprintf(stdout, "tank_pressure = %d\n", sw16(hk_wod.tank_pressure));
					fprintf(stdout, "aocs_period = %d\n", hk_wod.aocs_period);
					fprintf(stdout, "error_q1 = %d\n", sw16(hk_wod.error_q1));
					fprintf(stdout, "error_q2 = %d\n", sw16(hk_wod.error_q2));
					fprintf(stdout, "error_q3 = %d\n", sw16(hk_wod.error_q3));
					fprintf(stdout, "error_w1 = %d\n", sw16(hk_wod.error_w1));
					fprintf(stdout, "error_w2 = %d\n", sw16(hk_wod.error_w2));
					fprintf(stdout, "error_w3 = %d\n", sw16(hk_wod.error_w3));
					fprintf(stdout, "usb_agc = %d\n", hk_wod.usb_agc);
					fprintf(stdout, "usb_rf_power = %d\n", hk_wod.usb_rf_power);
					fprintf(stdout, "usb_temp2 = %d\n", hk_wod.usb_temp2);
					fprintf(stdout, "usb_flag1 = %d\n", hk_wod.usb_flag1);
					fprintf(stdout, "usb_flag2 = %d\n", hk_wod.usb_flag2);
					fprintf(stdout, "usb_n_cmd = %d\n", hk_wod.usb_n_cmd);
					fprintf(stdout, "usb_n_direct_cmd = %d\n", hk_wod.usb_n_direct_cmd);
					fprintf(stdout, "usb_n_inject_cmd = %d\n", hk_wod.usb_n_inject_cmd);
					fprintf(stdout, "usb_n_inject_cmd_err = %d\n", hk_wod.usb_n_inject_cmd_err);
					fprintf(stdout, "usb_n_sync = %d\n", hk_wod.usb_n_sync);
					fprintf(stdout, "t_pl = %d\n", sw16(hk_wod.t_pl));
					fprintf(stdout, "t_hsd = %d\n", sw16(hk_wod.t_hsd));
					fprintf(stdout, "t_obc = %d\n", sw16(hk_wod.t_obc));
					fprintf(stdout, "t_stb = %d\n", sw16(hk_wod.t_stb));
					fprintf(stdout, "t_ss = %d\n", sw16(hk_wod.t_ss));
					fprintf(stdout, "t_battery = %d\n", sw16(hk_wod.t_battery));
					fprintf(stdout, "t_thrustor1a = %d\n", sw16(hk_wod.t_thrustor1a));
					fprintf(stdout, "t_thrustor5a = %d\n", sw16(hk_wod.t_thrustor5a));
					fprintf(stdout, "t_value1 = %d\n", sw16(hk_wod.t_value1));
					fprintf(stdout, "t_value5 = %d\n", sw16(hk_wod.t_value5));
					fprintf(stdout, "t_tube1 = %d\n", sw16(hk_wod.t_tube1));
					fprintf(stdout, "t_tank = %d\n", sw16(hk_wod.t_tank));
					fprintf(stdout, "heater_flag1 = %d\n", hk_wod.heater_flag1);
					fprintf(stdout, "heater_flag2 = %d\n", hk_wod.heater_flag2);
					fprintf(stdout, "heater_flag3 = %d\n", hk_wod.heater_flag3);
					fprintf(stdout, "heater_flag4 = %d\n", hk_wod.heater_flag4);
					fprintf(stdout, "heater_flag5 = %d\n", hk_wod.heater_flag5);
					fprintf(stdout, "uva_flag_rx = %d\n", hk_wod.uva_flag_rx);
					fprintf(stdout, "uva_tx_gain = %d\n", hk_wod.uva_tx_gain);
					fprintf(stdout, "uva_tx_modulation = %d\n", hk_wod.uva_tx_modulation);
					fprintf(stdout, "uva_fc_asm = %d\n", sw16(hk_wod.uva_fc_asm));
					fprintf(stdout, "uva_snr_asm = %d\n", sw16(hk_wod.uva_snr_asm));
					fprintf(stdout, "uva_rssi_asm = %d\n", sw16(hk_wod.uva_rssi_asm));
					fprintf(stdout, "uva_rssi_7021 = %d\n", hk_wod.uva_rssi_7021);
					fprintf(stdout, "uvb_flag_rx = %d\n", hk_wod.uvb_flag_rx);
					fprintf(stdout, "uvb_tx_gain = %d\n", hk_wod.uvb_tx_gain);
					fprintf(stdout, "uvb_tx_modulation = %d\n", hk_wod.uvb_tx_modulation);
					fprintf(stdout, "uvb_fc_asm = %d\n", sw16(hk_wod.uvb_fc_asm));
					fprintf(stdout, "uvb_snr_asm = %d\n", sw16(hk_wod.uvb_snr_asm));
					fprintf(stdout, "uvb_rssi_asm = %d\n", sw16(hk_wod.uvb_rssi_asm));
					fprintf(stdout, "uvb_rssi_7021 = %d\n", hk_wod.uvb_rssi_7021);
				}
				if( ((header.nid == 0x0E)||(header.nid == 0x0F)) && (protocol==4) && (header.packet_data_len == sizeof(cfg_uv_t)) )
				{
					cfg_uv_t cfg_uv;	

					memcpy(&cfg_uv, bytes_in+LEN_PACKET_HEADER+1, sizeof(cfg_uv_t));
					
					if(header.nid == 0x0E) fprintf(stdout, "\n**** DSLWP V/U Transceiver 0 Config\n");
					if(header.nid == 0x0F) fprintf(stdout, "\n**** DSLWP V/U Transceiver 1 Config\n");
					fprintf(stdout, "dem_clk_divide = %d\n", cfg_uv.dem_clk_divide);
					fprintf(stdout, "tx_frequency_deviation = %d\n", cfg_uv.tx_frequency_deviation);
					fprintf(stdout, "tx_gain = %d\n", cfg_uv.tx_gain);
					fprintf(stdout, "turbo_rate = 0x%02x\n", cfg_uv.turbo_rate);
					fprintf(stdout, "precoder_en = 0x%02x\n", cfg_uv.precoder_en);
					fprintf(stdout, "preamble_len = %d\n", cfg_uv.preamble_len);
					fprintf(stdout, "trailer_len = %d\n", cfg_uv.trailer_len);
					fprintf(stdout, "rx_freq = %d\n", cfg_uv.rx_freq);

					uint32_t snr_threshold_u32 = sw32(*((int *)(&cfg_uv.snr_threshold)));
					fprintf(stdout, "snr_threshold = %f\n", *((float *)&snr_threshold_u32));

					fprintf(stdout, "gmsk_beacon_en = 0x%02x\n", cfg_uv.gmsk_beacon_en);
					fprintf(stdout, "jt4_beacon_en = 0x%02x\n", cfg_uv.jt4_beacon_en);
					fprintf(stdout, "interval_beacon = %d\n", cfg_uv.interval_beacon);
					fprintf(stdout, "interval_vc0_timeout = %d\n", cfg_uv.interval_vc0_timeout);

					fprintf(stdout, "message_hk = \"");
					for(int i=0; i<8; i++) fprintf(stdout, "%c", cfg_uv.message_hk[i]);
					fprintf(stdout, "\"\n");

					fprintf(stdout, "callsign = \"");
					for(int i=0; i<5; i++) fprintf(stdout, "%c", cfg_uv.callsign[i]);
					fprintf(stdout, "\"\n");

					fprintf(stdout, "open_camera_en = 0x%02x\n", cfg_uv.open_camera_en);
					fprintf(stdout, "repeater_en = 0x%02x\n", cfg_uv.repeater_en);
					fprintf(stdout, "take_picture_at_power_on = 0x%02x\n", cfg_uv.take_picture_at_power_on);
					fprintf(stdout, "rx7021_r9 = 0x%08x\n", sw32(cfg_uv.rx7021_r9));
					fprintf(stdout, "crc = 0x%08x\n", sw32(cfg_uv.crc));
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
		  fprintf(stdout, "\n**** Packet Length Do Not Match!!!\n");
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

