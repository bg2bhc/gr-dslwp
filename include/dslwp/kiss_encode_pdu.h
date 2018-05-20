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


#ifndef INCLUDED_DSLWP_KISS_ENCODE_PDU_H
#define INCLUDED_DSLWP_KISS_ENCODE_PDU_H

#include <dslwp/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace dslwp {

    /*!
     * \brief <+description of block+>
     * \ingroup dslwp
     *
     */
    class DSLWP_API kiss_encode_pdu : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<kiss_encode_pdu> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of dslwp::kiss_encode_pdu.
       *
       * To avoid accidental use of raw pointers, dslwp::kiss_encode_pdu's
       * constructor is in a private implementation
       * class. dslwp::kiss_encode_pdu::make is the public interface for
       * creating new instances.
       */
      static sptr make(int const_length);
    };

  } // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_KISS_ENCODE_PDU_H */

