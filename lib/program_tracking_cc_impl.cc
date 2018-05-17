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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "program_tracking_cc_impl.h"

#include <math.h>
#include <time.h>

namespace gr {
  namespace dslwp {

    program_tracking_cc::sptr
    program_tracking_cc::make(bool enable, const std::string& path, float lon, float lat, float alt, float fc, uint32_t samp_rate, bool txrx, bool verbose)
    {
      return gnuradio::get_initial_sptr
        (new program_tracking_cc_impl(enable, path, lon, lat, alt, fc, samp_rate, txrx, verbose));
    }

    /*
     * The private constructor
     */
    program_tracking_cc_impl::program_tracking_cc_impl(bool enable, const std::string& path, float lon, float lat, float alt, float fc, uint32_t samp_rate, bool txrx, bool verbose)
      : gr::sync_block("program_tracking_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex))),
							d_lat(lat), d_lon(lon), d_alt(alt), d_fc(fc), d_samp_rate(samp_rate), d_txrx(txrx), d_verbose(verbose)
    {
			d_fp = fopen((const char *)(path.data()), "r");

			program_tracking_cc_impl::lla2ecef(lat/180.0*M_PI, lon/180.0*M_PI, alt/1000.0, &d_rgs_x, &d_rgs_y, &d_rgs_z);
/*
			char c;
			while((c=fgetc(d_fp))!=EOF)
			{
				fprintf(stdout, "%c", c);
			}

			uint32_t timestamp;
			double rx, ry, rz, vx, vy, vz;
			int ret;

			while((ret=fscanf(d_fp, "%010d %015lf %015lf %015lf %010lf %010lf %010lf\r\n", &timestamp, &rx, &ry, &rz, &vx, &vy, &vz)) == 7)
			{
				fprintf(stdout, "%d, %010d %015lf %015lf %015lf %010lf %010lf %010lf\r\n", ret, timestamp, rx, ry, rz, vx, vy, vz);
			}
*/

			if(fscanf(d_fp, "%010d %015lf %015lf %015lf %010lf %010lf %010lf\r\n", &d_timestamp0, &d_rsat0_x, &d_rsat0_y, &d_rsat0_z, &d_vsat0_x, &d_vsat0_y, &d_vsat0_z) != 7)
			{
				fclose(d_fp);
				fprintf(stdout, "\n**** Error reading tracking file!!!\n");
				exit(0);
			}

			fprintf(stdout, "\n**** Program tracking\n");

			
			//fprintf(stdout, "%010d %015lf %015lf %015lf %010lf %010lf %010lf\r\n", d_timestamp0, d_rsat0_x, d_rsat0_y, d_rsat0_z, d_vsat0_x, d_vsat0_y, d_vsat0_z);

			time_t time_curr;
			struct tm *tblock_curr;

			time_curr = d_timestamp0;
			tblock_curr =  gmtime(&time_curr);
			fprintf(stdout, "Start time: %ld, %02d/%02d/%02d %02d:%02d:%02d\n", time_curr, tblock_curr->tm_year+1900, tblock_curr->tm_mon+1, tblock_curr->tm_mday, tblock_curr->tm_hour, tblock_curr->tm_min, tblock_curr->tm_sec);

			time_curr = time(NULL);
			tblock_curr =  gmtime(&time_curr);
			fprintf(stdout, "Current time: %ld, %02d/%02d/%02d %02d:%02d:%02d\n", time_curr, tblock_curr->tm_year+1900, tblock_curr->tm_mon+1, tblock_curr->tm_mday, tblock_curr->tm_hour, tblock_curr->tm_min, tblock_curr->tm_sec);

			double azm, elv, range;
			program_tracking_cc_impl::ecef2aer(-207.8135, 286.0307, 353.5534, 45.0/180*M_PI, 126.0/180*M_PI, &azm, &elv, &range);
			fprintf(stdout, "%f, %f, %f\n", azm, elv, range);

			d_init = 0;
		}

    /*
     * Our virtual destructor.
     */
    program_tracking_cc_impl::~program_tracking_cc_impl()
    {
			fclose(d_fp);
    }

		void program_tracking_cc_impl::lla2ecef(double lat, double lon, double alt, double *rx, double *ry, double *rz)
		{
			double a = 6378.137;
			double e2 = 0.00669437999013;

			double v = a * pow(1-e2*sin(lat)*sin(lat), -0.5);

			*rx = (v+alt)*cos(lat)*cos(lon);
			*ry = (v+alt)*cos(lat)*sin(lon);
			*rz = ((1-e2)*v+alt)*sin(lat);
		}

		void program_tracking_cc_impl::ecef2aer(double x, double y, double z, double lat, double lon, double *azm, double *elv, double *range)
		{
			double x1 = -sin(lon)*cos(lat)*x - sin(lon)*sin(lat)*y + cos(lon)*z;
			double y1 = -sin(lat) * x + cos(lat) * y;
			double z1 = -cos(lon)*cos(lat)*x - cos(lon)*sin(lat)*y - sin(lon)*z;

			fprintf(stdout, "%f %f %f\n", x1, y1, z1);

			if((x>0.0)&&(y>=0.0))
			{
				*azm = atan(y1/x1);
			}
			else if((x<0.0)&&(y>=0.0))
			{
				*azm = M_PI + atan(y1/x1);
			}
			else if((x<0.0)&&(y<=0.0))
			{
				*azm = M_PI + atan(y1/x1);
			}
			else if((x>0.0)&&(y<=0.0))
			{
				*azm = M_PI*2.0 - atan(y1/x1);
			}
			else
			{
				*azm = 0.0;
			}

			*elv = -atan(z1/pow(x1*x1+y1*y1, 0.5));

			*range = pow(x1*x1+y1*y1+z1*z1, 0.5);
		}

    int
    program_tracking_cc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];

      // Do <+signal processing+>
			if(!d_init)
			{
				static time_t time_curr;
				static struct tm *tblock_curr;

				time_curr = time(NULL);
				tblock_curr =  gmtime(&time_curr);
				fprintf(stdout, "Current time: %ld, %02d/%02d/%02d %02d:%02d:%02d\n", time_curr, tblock_curr->tm_year+1900, tblock_curr->tm_mon+1, tblock_curr->tm_mday, tblock_curr->tm_hour, tblock_curr->tm_min, tblock_curr->tm_sec);				
			}
			

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace dslwp */
} /* namespace gr */

