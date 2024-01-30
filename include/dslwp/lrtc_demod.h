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

#ifndef INCLUDED_DSLWP_LRTC_DEMOD_H
#define INCLUDED_DSLWP_LRTC_DEMOD_H

#include <dslwp/api.h>
#include <gnuradio/sync_decimator.h>

namespace gr {
  namespace dslwp {

    /*!
     * \brief <+description of block+>
     * \ingroup dslwp
     *
     */
    class DSLWP_API lrtc_demod : virtual public gr::sync_decimator
    {
     public:
      typedef boost::shared_ptr<lrtc_demod> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of dslwp::lrtc_demod.
       *
       * To avoid accidental use of raw pointers, dslwp::lrtc_demod's
       * constructor is in a private implementation
       * class. dslwp::lrtc_demod::make is the public interface for
       * creating new instances.
       */
      static sptr make(int mode, size_t fft_size, size_t n_avg);
    };

  } // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_LRTC_DEMOD_H */

