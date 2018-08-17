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


#ifndef INCLUDED_DSLWP_OQPSK_COHERENT_DEMOD_CC_H
#define INCLUDED_DSLWP_OQPSK_COHERENT_DEMOD_CC_H

#include <dslwp/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace dslwp {

    /*!
     * \brief <+description of block+>
     * \ingroup dslwp
     *
     */
    class DSLWP_API oqpsk_coherent_demod_cc : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<oqpsk_coherent_demod_cc> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of dslwp::oqpsk_coherent_demod_cc.
       *
       * To avoid accidental use of raw pointers, dslwp::oqpsk_coherent_demod_cc's
       * constructor is in a private implementation
       * class. dslwp::oqpsk_coherent_demod_cc::make is the public interface for
       * creating new instances.
       */
      static sptr make(int samples_per_symbol, const std::vector<gr_complex> &taps, int opt_point, int pll, float pll_loop_bw, float pll_damping, float freq_max, float freq_min, int dttl, float dttl_loop_bw, float dttl_damping, float max_rate_deviation, int asm_ignore);
    };

  } // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_OQPSK_COHERENT_DEMOD_CC_H */

