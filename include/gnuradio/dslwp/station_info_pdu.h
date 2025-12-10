/* -*- c++ -*- */
/*
 * Copyright 2025 BG2BHC.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSLWP_STATION_INFO_PDU_H
#define INCLUDED_DSLWP_STATION_INFO_PDU_H

#include <gnuradio/dslwp/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace dslwp {

/*!
 * \brief <+description of block+>
 * \ingroup dslwp
 *
 */
class DSLWP_API station_info_pdu : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<station_info_pdu> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of dslwp::station_info_pdu.
     *
     * To avoid accidental use of raw pointers, dslwp::station_info_pdu's
     * constructor is in a private implementation
     * class. dslwp::station_info_pdu::make is the public interface for
     * creating new instances.
     */
    static sptr make(const std::string& nickname,
                     float lat,
                     float lon,
                     float alt,
                     const std::string& satellite,
                     int physical_channel,
                     int format);
};

} // namespace dslwp
} // namespace gr

#endif /* INCLUDED_DSLWP_STATION_INFO_PDU_H */
