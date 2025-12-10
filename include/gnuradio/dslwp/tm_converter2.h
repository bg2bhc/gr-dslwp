/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_TM_CONVERTER2_H
#define INCLUDED_DSLWP_TM_CONVERTER2_H

#include <gnuradio/block.h>
#include <gnuradio/dslwp/api.h>

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
    typedef std::shared_ptr<tm_converter2> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of dslwp::tm_converter2.
     *
     * To avoid accidental use of raw pointers, dslwp::tm_converter2's
     * constructor is in a private implementation
     * class. dslwp::tm_converter2::make is the public interface for
     * creating new instances.
     */
    static sptr make(const std::string& header, const std::vector<int>& list);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_TM_CONVERTER2_H */
