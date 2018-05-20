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

#ifndef INCLUDED_DSLWP_FFT_ESTIMATOR_CC_IMPL_H
#define INCLUDED_DSLWP_FFT_ESTIMATOR_CC_IMPL_H

#include <dslwp/fft_estimator_cc.h>

namespace gr {
  namespace dslwp {

    class fft_estimator_cc_impl : public fft_estimator_cc
    {
     private:
		size_t d_fft_size;
		float d_threshold;
		size_t d_tap_len;
		float* d_power;
		float d_snr;
		float d_power_s_plus_n;
		float d_power_s;
		float d_amp_i0;
		float d_amp_i1;
		int d_index_s;
		int d_over_threshold;
		int d_corr_found;

     public:
      fft_estimator_cc_impl(size_t fft_size, float threshold, size_t tap_len);
      ~fft_estimator_cc_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_FFT_ESTIMATOR_CC_IMPL_H */

