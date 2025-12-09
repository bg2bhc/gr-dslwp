/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_FFT_ESTIMATOR_CC_IMPL_H
#define INCLUDED_DSLWP_FFT_ESTIMATOR_CC_IMPL_H

#include <gnuradio/dslwp/fft_estimator_cc.h>

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
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_FFT_ESTIMATOR_CC_IMPL_H */
