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

#ifndef INCLUDED_DSLWP_PROGRAM_TRACKING_CC_IMPL_H
#define INCLUDED_DSLWP_PROGRAM_TRACKING_CC_IMPL_H

#include <dslwp/program_tracking_cc.h>
#include <stdio.h>
#include <inttypes.h>
#include <time.h>

namespace gr {
  namespace dslwp {

    class program_tracking_cc_impl : public program_tracking_cc
    {
     private:
			uint8_t d_enable;

			double d_rgs_x;
			double d_rgs_y;
			double d_rgs_z;

			time_t d_timestamp0;
			double d_rsat0_x;
			double d_rsat0_y;
			double d_rsat0_z;
			double d_vsat0_x;
			double d_vsat0_y;
			double d_vsat0_z;

			time_t d_timestamp1;
			double d_rsat1_x;
			double d_rsat1_y;
			double d_rsat1_z;
			double d_vsat1_x;
			double d_vsat1_y;
			double d_vsat1_z;

			double d_lat;
			double d_lon;
			double d_fc;
			uint32_t d_samp_rate;
			bool d_txrx;
			bool d_verbose;

			double d_range0;
			double d_range1;
			double d_rr0;
			double d_rr1;
			double d_rrr;

			time_t d_time_curr;

			FILE *d_fp;
			uint8_t d_tracking;

			double d_doppler;
			double d_doppler_rate;

			double d_az0, d_az1, d_el0, d_el1;

			void lla2ecef(double lat, double lon, double alt, double *rx, double *ry, double *rz);
			void ecef2llr(double rx, double ry, double rz, double *lat, double *lon, double *r);
			void ecef2azel(double rx, double ry, double rz, double lat, double lon, double *az, double *el);
			//void ecef2aer(double x, double y, double z, double lat, double lon, double *azm, double *elv, double *range);

     public:
      program_tracking_cc_impl(uint8_t enable, uint32_t timestamp, const std::string& path, float lon, float lat, float alt, float fc, uint32_t samp_rate, bool txrx, bool verbose);
      ~program_tracking_cc_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_PROGRAM_TRACKING_CC_IMPL_H */

