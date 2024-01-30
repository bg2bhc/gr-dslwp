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

#ifndef INCLUDED_DSLWP_LRTC_DEMOD_IMPL_H
#define INCLUDED_DSLWP_LRTC_DEMOD_IMPL_H

#include <dslwp/lrtc_demod.h>

#define MAX_AVG_CORR 32
#define MAX_FFT_SIZE 1024

namespace gr {
  namespace dslwp {

    class lrtc_demod_impl : public lrtc_demod
    {
     private:
      size_t d_fft_size;
      size_t d_n_avg;
      int d_sample_in_symbol;
      int d_i_avg_buf;
      float d_buf_pwr_est[MAX_AVG_CORR][MAX_FFT_SIZE];
      float d_buf_freq_est[MAX_AVG_CORR][MAX_FFT_SIZE];
      float d_buf_snr_est[MAX_FFT_SIZE];
      
      int d_index_pwr_max;
      float d_pwr_max;
      float d_freq_est;

     public:
      lrtc_demod_impl(int mode, size_t fft_size, size_t n_avg);
      ~lrtc_demod_impl();

      // Where all the action really happens
      int work(
              int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items
      );
    };

  } // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_LRTC_DEMOD_IMPL_H */

