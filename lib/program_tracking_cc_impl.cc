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

namespace gr {
  namespace dslwp {

    program_tracking_cc::sptr
    program_tracking_cc::make(uint8_t enable, uint32_t timestamp, const std::string& path, float lon, float lat, float alt, float fc, uint32_t samp_rate, bool txrx, bool verbose)
    {
      return gnuradio::get_initial_sptr
        (new program_tracking_cc_impl(enable, timestamp, path, lon, lat, alt, fc, samp_rate, txrx, verbose));
    }

    /*
     * The private constructor
     */
    program_tracking_cc_impl::program_tracking_cc_impl(uint8_t enable, uint32_t timestamp, const std::string& path, float lon, float lat, float alt, float fc, uint32_t samp_rate, bool txrx, bool verbose)
      : gr::sync_block("program_tracking_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex))),
							d_enable(enable), d_fc(fc), d_samp_rate(samp_rate), d_txrx(txrx), d_verbose(verbose)
    {
			if(d_enable)
			{
				d_fp = fopen((const char *)(path.data()), "r");

				fprintf(stdout, "\n**** Program tracking\n");
/*
				double azm, elv, range;
				program_tracking_cc_impl::ecef2aer(-207.8135, 286.0307, 353.5534, 45.0/180*M_PI, 126.0/180*M_PI, &azm, &elv, &range);
				fprintf(stdout, "%f, %f, %f\n", azm, elv, range);
*/
				double rgs; 				
				program_tracking_cc_impl::lla2ecef(lat/180.0*M_PI, lon/180.0*M_PI, alt/1000.0, &d_rgs_x, &d_rgs_y, &d_rgs_z);
				program_tracking_cc_impl::ecef2llr(d_rgs_x, d_rgs_y, d_rgs_z, &d_lat, &d_lon, &rgs);

				fprintf(stdout, "Set home location in ECEF: %f, %f, %f\n", d_rgs_x, d_rgs_y, d_rgs_z);

				if(fscanf(d_fp, "%010ld %015lf %015lf %015lf %010lf %010lf %010lf\r\n", &d_timestamp0, &d_rsat0_x, &d_rsat0_y, &d_rsat0_z, &d_vsat0_x, &d_vsat0_y, &d_vsat0_z) != 7)
				{
					fclose(d_fp);
					fprintf(stdout, "\n**** Error read tracking file!!!\n");
					exit(0);
				}
				
                if(d_enable==1)
				    d_time_curr = time(NULL);
                else if(d_enable==2)
				    d_time_curr = timestamp;

				if(d_time_curr < d_timestamp0)
				{
					struct tm *tblock;

					tblock =  gmtime(&d_time_curr);
					fprintf(stdout, "Current time: %ld, %02d/%02d/%02d %02d:%02d:%02d\n", d_time_curr, tblock->tm_year+1900, tblock->tm_mon+1, tblock->tm_mday, tblock->tm_hour, tblock->tm_min, tblock->tm_sec);

					tblock =  gmtime((time_t *)&d_timestamp0);
					fprintf(stdout, "Tracking start at: %ld, %02d/%02d/%02d %02d:%02d:%02d\n", d_timestamp0, tblock->tm_year+1900, tblock->tm_mon+1, tblock->tm_mday, tblock->tm_hour, tblock->tm_min, tblock->tm_sec);

					d_tracking = 0;
				}
				else
				{
					while(d_time_curr > d_timestamp0)
					{
								if(fscanf(d_fp, "%010ld %015lf %015lf %015lf %010lf %010lf %010lf\r\n", &d_timestamp0, &d_rsat0_x, &d_rsat0_y, &d_rsat0_z, &d_vsat0_x, &d_vsat0_y, &d_vsat0_z) != 7)
								{
									fclose(d_fp);
									fprintf(stdout, "\n**** Error read tracking file or EOF!!!\n");
									exit(0);
								}	
					}
					fprintf(stdout, "\n**** Tracking start!\n");
					d_tracking = 1;

					double vec_x, vec_y, vec_z, vec_unit_x, vec_unit_y, vec_unit_z;

					vec_x = d_rsat0_x - d_rgs_x;
					vec_y = d_rsat0_y - d_rgs_y;
					vec_z = d_rsat0_z - d_rgs_z;	

					program_tracking_cc_impl::ecef2azel(vec_x, vec_y, vec_z, d_lat, d_lon, &d_az0, &d_el0);		

					d_range0 = pow(vec_x*vec_x+vec_y*vec_y+vec_z*vec_z, 0.5);

					vec_unit_x = vec_x / d_range0;
					vec_unit_y = vec_y / d_range0;
					vec_unit_z = vec_z / d_range0;

					d_rr0 = d_vsat0_x * vec_unit_x + d_vsat0_y * vec_unit_y + d_vsat0_z * vec_unit_z;

					if(fscanf(d_fp, "%010ld %015lf %015lf %015lf %010lf %010lf %010lf\r\n", &d_timestamp1, &d_rsat1_x, &d_rsat1_y, &d_rsat1_z, &d_vsat1_x, &d_vsat1_y, &d_vsat1_z) != 7)
					{
						fclose(d_fp);
						fprintf(stdout, "\n**** Error read tracking file or EOF!!!\n");
						exit(0);
					}

					vec_x = d_rsat1_x - d_rgs_x;
					vec_y = d_rsat1_y - d_rgs_y;
					vec_z = d_rsat1_z - d_rgs_z;

					program_tracking_cc_impl::ecef2azel(vec_x, vec_y, vec_z, d_lat, d_lon, &d_az1, &d_el1);	

					d_range1 = pow(vec_x*vec_x+vec_y*vec_y+vec_z*vec_z, 0.5);

					vec_unit_x = vec_x / d_range1;
					vec_unit_y = vec_y / d_range1;
					vec_unit_z = vec_z / d_range1;

					d_rr1 = d_vsat1_x * vec_unit_x + d_vsat1_y * vec_unit_y + d_vsat1_z * vec_unit_z;				
					d_rrr = d_rr1 - d_rr0;

					struct tm *tblock;
					tblock =  gmtime((time_t *)&d_timestamp0);

					d_doppler = d_rr0/2.99792458e5*d_fc;
					d_doppler_rate = d_rrr/2.99792458e5*d_fc;
					if(d_txrx)
					{
						d_doppler = -d_doppler;
						d_doppler_rate = -d_doppler_rate;
					}
					if(d_verbose)
					{
						fprintf(stdout, "%02d/%02d/%02d %02d:%02d:%02d, az = %.2f, el = %.2f, range = %f, rr = %f, rrr = %f, doppler = %.2f, doppler_rate = %.2f\n", tblock->tm_year+1900, tblock->tm_mon+1, tblock->tm_mday, tblock->tm_hour, tblock->tm_min, tblock->tm_sec, d_az0/M_PI*180.0, d_el0/M_PI*180.0, d_range0, d_rr0, d_rrr, -d_doppler, -d_doppler_rate);
					}
				}
			}
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

		void program_tracking_cc_impl::ecef2llr(double rx, double ry, double rz, double *lat, double *lon, double *r)
		{
			*lon = acos(rx / sqrt(rx*rx+ry*ry));
			if(ry<0)
			{
				*lon = -*lon;
			}
			
			*lat = atan(rz / sqrt(rx*rx+ry*ry));
			*r = sqrt(rx*rx + ry*ry + rz*rz);
		}

		void program_tracking_cc_impl::ecef2azel(double rx, double ry, double rz, double lat, double lon, double *az, double *el)
		{
			float r1x = cos(lon)*rx + sin(lon)*ry;
			float r1y = -sin(lon)*rx + cos(lon)*ry;
			float r1z = rz;

			float r2x = cos(-lat)*r1x - sin(-lat)*r1z;
			float r2y = r1y;
			float r2z = sin(-lat)*r1x + cos(-lat)*r1z;

			*el = atan(r2x / sqrt(r2y*r2y + r2z*r2z));

			*az = acos(r2z / sqrt(r2y*r2y + r2z*r2z));
			if(r2y < 0)
			{
				*az = 2*M_PI - *az;
			}
		}

    int
    program_tracking_cc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];

			int i;
			static float k_real = 1, k_imag = 0;
			static double  current_phase = 0;
			static uint32_t sample_in_second = 0;

			for(i=0; i<noutput_items; i++)
			{
				if(d_enable)
				{
					k_real = cos(current_phase);
					k_imag = sin(current_phase);

					if(sample_in_second >= d_samp_rate)
					{
						sample_in_second = 0;
						d_time_curr++;

						if(d_tracking)
						{
							d_timestamp0 = d_timestamp1;
							d_rsat0_x = d_rsat1_x;
							d_rsat0_y = d_rsat1_y;
							d_rsat0_z = d_rsat1_z;
							d_vsat0_x = d_vsat1_x;
							d_vsat0_y = d_vsat1_y;
							d_vsat0_z = d_vsat1_z;
							d_range0 = d_range1;
							d_rr0 = d_rr1;
							d_el0 = d_el1;
							d_az0 = d_az1;

							if(fscanf(d_fp, "%010ld %015lf %015lf %015lf %010lf %010lf %010lf\r\n", &d_timestamp1, &d_rsat1_x, &d_rsat1_y, &d_rsat1_z, &d_vsat1_x, &d_vsat1_y, &d_vsat1_z) != 7)
							{
								fclose(d_fp);
								fprintf(stdout, "\n**** Error read tracking file or EOF!!!\n");
								exit(0);
							}

							double vec_x, vec_y, vec_z, vec_unit_x, vec_unit_y, vec_unit_z;

							vec_x = d_rsat1_x - d_rgs_x;
							vec_y = d_rsat1_y - d_rgs_y;
							vec_z = d_rsat1_z - d_rgs_z;		

							program_tracking_cc_impl::ecef2azel(vec_x, vec_y, vec_z, d_lat, d_lon, &d_az1, &d_el1);		

							d_range1 = pow(vec_x*vec_x+vec_y*vec_y+vec_z*vec_z, 0.5);

							vec_unit_x = vec_x / d_range1;
							vec_unit_y = vec_y / d_range1;
							vec_unit_z = vec_z / d_range1;

							d_rr1 = d_vsat1_x * vec_unit_x + d_vsat1_y * vec_unit_y + d_vsat1_z * vec_unit_z;						
							d_rrr = d_rr1 - d_rr0;

							d_doppler = d_rr0/2.99792458e5*d_fc;
							d_doppler_rate = d_rrr/2.99792458e5*d_fc;
							if(d_txrx)
							{
								d_doppler = -d_doppler;
								d_doppler_rate = -d_doppler_rate;
							}

							struct tm *tblock;
							tblock =  gmtime((time_t *)&d_timestamp0);

							if(d_verbose)
							{							
								fprintf(stdout, "%02d/%02d/%02d %02d:%02d:%02d, az = %.2f, el = %.2f, range = %f, rr = %f, rrr = %f, doppler = %.2f, doppler_rate = %.2f\n", tblock->tm_year+1900, tblock->tm_mon+1, tblock->tm_mday, tblock->tm_hour, tblock->tm_min, tblock->tm_sec, d_az0/M_PI*180.0, d_el0/M_PI*180.0, d_range0, d_rr0, d_rrr, -d_doppler, -d_doppler_rate);
							}
						}
						else
						{
							{
								if(d_time_curr == d_timestamp0)
								{

									fprintf(stdout, "\n**** Tracking start!\n");
									d_tracking = 1;

									if(fscanf(d_fp, "%010ld %015lf %015lf %015lf %010lf %010lf %010lf\r\n", &d_timestamp0, &d_rsat0_x, &d_rsat0_y, &d_rsat0_z, &d_vsat0_x, &d_vsat0_y, &d_vsat0_z) != 7)
									{
										fclose(d_fp);
										fprintf(stdout, "\n**** Error read tracking file or EOF!!!\n");
										exit(0);
									}

									double vec_x, vec_y, vec_z, vec_unit_x, vec_unit_y, vec_unit_z;

									vec_x = d_rsat0_x - d_rgs_x;
									vec_y = d_rsat0_y - d_rgs_y;
									vec_z = d_rsat0_z - d_rgs_z;	

									program_tracking_cc_impl::ecef2azel(vec_x, vec_y, vec_z, d_lat, d_lon, &d_az0, &d_el0);			

									d_range0 = pow(vec_x*vec_x+vec_y*vec_y+vec_z*vec_z, 0.5);

									vec_unit_x = vec_x / d_range0;
									vec_unit_y = vec_y / d_range0;
									vec_unit_z = vec_z / d_range0;

									d_rr0 = d_vsat0_x * vec_unit_x + d_vsat0_y * vec_unit_y + d_vsat0_z * vec_unit_z;

									if(fscanf(d_fp, "%010ld %015lf %015lf %015lf %010lf %010lf %010lf\r\n", &d_timestamp1, &d_rsat1_x, &d_rsat1_y, &d_rsat1_z, &d_vsat1_x, &d_vsat1_y, &d_vsat1_z) != 7)
									{
										fclose(d_fp);
										fprintf(stdout, "\n**** Error read tracking file or EOF!!!\n");
										exit(0);
									}

									vec_x = d_rsat1_x - d_rgs_x;
									vec_y = d_rsat1_y - d_rgs_y;
									vec_z = d_rsat1_z - d_rgs_z;	

									program_tracking_cc_impl::ecef2azel(vec_x, vec_y, vec_z, d_lat, d_lon, &d_az1, &d_el1);			

									d_range1 = pow(vec_x*vec_x+vec_y*vec_y+vec_z*vec_z, 0.5);

									vec_unit_x = vec_x / d_range1;
									vec_unit_y = vec_y / d_range1;
									vec_unit_z = vec_z / d_range1;

									d_rr1 = d_vsat1_x * vec_unit_x + d_vsat1_y * vec_unit_y + d_vsat1_z * vec_unit_z;					
									d_rrr = d_rr1 - d_rr0;

									struct tm *tblock;
									tblock =  gmtime((time_t *)&d_timestamp0);

									d_doppler = d_rr0/2.99792458e5*d_fc;
									d_doppler_rate = d_rrr/2.99792458e5*d_fc;
									if(d_txrx)
									{
										d_doppler = -d_doppler;
										d_doppler_rate = -d_doppler_rate;
									}

									if(d_verbose)
									{
										fprintf(stdout, "%02d/%02d/%02d %02d:%02d:%02d, az = %.2f, el = %.2f, range = %f, rr = %f, rrr = %f, doppler = %.2f, doppler_rate = %.2f\n", tblock->tm_year+1900, tblock->tm_mon+1, tblock->tm_mday, tblock->tm_hour, tblock->tm_min, tblock->tm_sec, d_az0/M_PI*180.0, d_el0/M_PI*180.0, d_range0, d_rr0, d_rrr, -d_doppler, -d_doppler_rate);
									}
								}
							}
						}
					}

					current_phase += d_doppler/d_samp_rate*2*M_PI;

					d_doppler += d_doppler_rate/d_samp_rate;
					sample_in_second++;
				}

				out[i] = gr_complex(k_real, k_imag) * in[i];
			}
			

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace dslwp */
} /* namespace gr */

