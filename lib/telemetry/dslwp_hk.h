#ifndef __DSLWP_HK_H__
#define __DSLWP_HK_H__

#include <inttypes.h>

typedef struct hk_uv_t
{
	uint8_t config;
	uint8_t flag_rx;
	uint8_t tx_gain;
	uint8_t tx_modulation;
	uint8_t flag_tx;
	uint8_t flag_7021;
	uint8_t n_cmd_buf;
	uint8_t n_cmd_dropped;
	// 8
	uint8_t i_bus_rx;
	uint8_t u_bus_rx;
	uint8_t i_bus_tx;
	uint8_t u_bus_tx;
	int8_t t_pa;
	int8_t t_tx7021;
	uint8_t n_jt4_tx;
	uint8_t n_ham_rx;
	// 16
	uint8_t n_422_tx;
	uint8_t n_422_rx;
	uint8_t n_422_rx_pkg_err;
	uint8_t n_422_rx_exe_err;
	uint8_t cmd_422_last_rx;
	uint8_t n_rf_tx;
	uint8_t n_rf_tx_dropped;
	uint8_t n_rf_rx;
	// 24
	uint8_t n_rf_rx_pkg_err;
	uint8_t n_rf_rx_exe_err;
	uint8_t n_rf_rx_fec_err;
	uint8_t cmd_rf_last_rx;
	uint8_t rsvd0;
	uint8_t rsvd1;
	int8_t byte_corr;
	uint8_t n_cmd;
	// 32
	int16_t fc_asm;
	uint16_t snr_asm;
	uint16_t rssi_asm;
	uint16_t rssi_channel;
	// 40
	uint8_t rssi_7021;
	uint8_t flag_agc;
	int16_t rsvd15;
	uint32_t seconds_since_epoch;
	// 48
	uint8_t cam_mode;
	uint8_t cam_task_flag;
	uint8_t cam_err_flag;
	uint8_t cam_pic_len_2;
	uint8_t cam_pic_len_1;
	uint8_t cam_pic_len_0;
	uint8_t cam_memory_id;
	uint8_t	jt4_task_flag;
	// 56
	uint8_t n_reset;
	uint8_t flag_reset;
	uint8_t flag_sys;
	uint8_t n_dma_overflow;
	uint32_t runtime;
	// 64
	char message[8];
	// 72
} hk_uv_t;

typedef struct __attribute__((__packed__))
{
	uint32_t seconds_since_epoch     : 32;
	uint8_t n_cmd_exe                : 8;
	uint8_t n_cmd_delay              : 8;
	uint8_t this_wdt_timeout_count   : 8;
	uint8_t that_wdt_timeout_count   : 8;
	uint8_t sta_reset_count          : 8;
	uint8_t stb_reset_count          : 8;
	uint8_t ss_reset_count           : 8;
	uint8_t is_reset_count           : 8;
	uint8_t pl_task_err_flag         : 8;
	uint8_t hsd_task_err_flag        : 8;
	uint8_t tc_wdt_timeout_period    : 8;
	uint16_t v_bus                   : 16;
	uint16_t v_battery               : 16;
	uint16_t i_solar_panel           : 16;
	uint16_t i_load                  : 16;
	uint16_t i_bus                   : 16;
	uint8_t sw_flag_1                : 8;
	uint8_t sw_flag_2                : 8;
	uint8_t sw_flag_3                : 8;
	uint8_t sw_flag_4                : 8;
	uint32_t sta_q0                  : 32;
	uint32_t sta_q1                  : 32;
	uint32_t sta_q2                  : 32;
	uint32_t sta_q3                  : 32;
	uint8_t sta_flag                 : 8;
	uint32_t stb_q0                  : 32;
	uint32_t stb_q1                  : 32;
	uint32_t stb_q2                  : 32;
	uint32_t stb_q3                  : 32;
	uint8_t stb_flag                 : 8;
	uint32_t stc_q0                  : 32;
	uint32_t stc_q1                  : 32;
	uint32_t stc_q2                  : 32;
	uint32_t stc_q3                  : 32;
	uint8_t stc_flag                 : 8;
	uint32_t ss_x                    : 32;
	uint32_t ss_y                    : 32;
	uint8_t ss_flag                  : 8;
	uint16_t fwx_rate                : 16;
	uint16_t fwx_cmd                 : 16;
	uint16_t fwy_rate                : 16;
	uint16_t fwy_cmd                 : 16;
	uint16_t fwz_rate                : 16;
	uint16_t fwz_cmd                 : 16;
	uint16_t fws_rate                : 16;
	uint16_t fws_cmd                 : 16;
	uint32_t gyro_x                  : 32;
	uint32_t gyro_y                  : 32;
	uint32_t gyro_z                  : 32;
	uint16_t tank_pressure           : 16;
	uint8_t aocs_period              : 8;
	uint16_t error_q1                : 16;
	uint16_t error_q2                : 16;
	uint16_t error_q3                : 16;
	uint16_t error_w1                : 16;
	uint16_t error_w2                : 16;
	uint16_t error_w3                : 16;
	uint8_t usb_agc                  : 8;
	uint8_t usb_rf_power             : 8;
	uint8_t usb_temp2                : 8;
	uint8_t usb_flag1                : 8;
	uint8_t usb_flag2                : 8;
	uint8_t usb_n_cmd                : 8;
	uint8_t usb_n_direct_cmd         : 8;
	uint8_t usb_n_inject_cmd         : 8;
	uint8_t usb_n_inject_cmd_err     : 8;
	uint8_t usb_n_sync               : 8;
	uint16_t t_pl                    : 16;
	uint16_t t_hsd                   : 16;
	uint16_t t_obc                   : 16;
	uint16_t t_stb                   : 16;
	uint16_t t_ss                    : 16;
	uint16_t t_battery               : 16;
	uint16_t t_thrustor1a            : 16;
	uint16_t t_thrustor5a            : 16;
	uint16_t t_value1                : 16;
	uint16_t t_value5                : 16;
	uint16_t t_tube1                 : 16;
	uint16_t t_tank                  : 16;
	uint8_t heater_flag1             : 8;
	uint8_t heater_flag2             : 8;
	uint8_t heater_flag3             : 8;
	uint8_t heater_flag4             : 8;
	uint8_t heater_flag5             : 8;
	uint8_t uva_flag_rx              : 8;
	uint8_t uva_tx_gain              : 8;
	uint8_t uva_tx_modulation        : 8;
	uint8_t uva_flag_tx              : 8;
	uint16_t uva_fc_asm              : 16;
	uint16_t uva_snr_asm             : 16;
	uint16_t uva_rssi_asm            : 16;
	uint8_t uva_rssi_7021            : 8;
	uint8_t uvb_flag_rx              : 8;
	uint8_t uvb_tx_gain              : 8;
	uint8_t uvb_tx_modulation        : 8;
	uint8_t uvb_flag_tx              : 8;
	uint16_t uvb_fc_asm              : 16;
	uint16_t uvb_snr_asm             : 16;
	uint16_t uvb_rssi_asm            : 16;
	uint8_t uvb_rssi_7021            : 8;
} hk_wod_t;

typedef struct cfg_uv_t
{
	// 0
	uint8_t dem_clk_divide;
	uint8_t tx_frequency_deviation;
	uint8_t tx_gain;
	uint8_t turbo_rate;
	uint8_t precoder_en;
	uint8_t preamble_len;
	uint8_t trailer_len;
	uint8_t rx_freq;
	// 8
	float snr_threshold;
	uint8_t gmsk_beacon_en;
	uint8_t jt4_beacon_en;
	uint8_t interval_beacon;
	uint8_t interval_vc0_timeout;
	// 16
	char message_hk[8];
	// 24
	char callsign[5];
	uint8_t open_camera_en;
	uint8_t repeater_en;
	uint8_t take_picture_at_power_on;
	// 32
	uint32_t rx7021_r9;
	uint32_t crc;
	// 40
} cfg_uv_t;

typedef struct cfg_cam_t
{
	// 0
	uint8_t size;
	uint8_t brightness;
	uint8_t contrast;
	uint8_t sharpness;
	uint8_t exposure;
	uint8_t compressing;
	uint8_t colour;
	uint8_t config;
	uint8_t id;
} cfg_cam_t;

#endif
