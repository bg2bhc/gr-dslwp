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

#ifndef INCLUDED_DSLWP_DIFFERENTIAL_PHASE_DETECTION_1BIT_CF_IMPL_H
#define INCLUDED_DSLWP_DIFFERENTIAL_PHASE_DETECTION_1BIT_CF_IMPL_H

#include <dslwp/differential_phase_detection_1bit_cf.h>

namespace gr {
  namespace dslwp {

    class differential_phase_detection_1bit_cf_impl : public differential_phase_detection_1bit_cf
    {
     private:
	int d_samples_per_symbol;
	std::vector<gr_complex> d_taps;
	int d_opt_point;
	int d_delay;

	gr_complex *d_mix_out;
	gr_complex *d_mf_out;
	int d_sample_in_symbol;
	float d_freq;
	float d_phase;

     public:
      differential_phase_detection_1bit_cf_impl(int samples_per_symbol, const std::vector<gr_complex> &taps, int opt_point, int delay);
      ~differential_phase_detection_1bit_cf_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_DIFFERENTIAL_PHASE_DETECTION_1BIT_CC_IMPL_H */

