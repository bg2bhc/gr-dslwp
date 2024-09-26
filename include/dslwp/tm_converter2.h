/* -*- c++ -*- */
/* 
 * Copyright 2024 <+YOU OR YOUR COMPANY+>.
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


#ifndef INCLUDED_DSLWP_TM_CONVERTER2_H
#define INCLUDED_DSLWP_TM_CONVERTER2_H

#include <dslwp/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace dslwp {

    /*!
     * \brief <+description of block+>
     * \ingroup dslwp
     *
     */
    class DSLWP_API tm_converter2 : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<tm_converter2> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of dslwp::tm_converter2.
       *
       * To avoid accidental use of raw pointers, dslwp::tm_converter2's
       * constructor is in a private implementation
       * class. dslwp::tm_converter2::make is the public interface for
       * creating new instances.
       */
      static sptr make(const std::string &header, const std::vector<int> &list);
    };

  } // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_TM_CONVERTER2_H */

