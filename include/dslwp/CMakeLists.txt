# Copyright 2011,2012 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Install public header files
########################################################################
install(FILES
    fft.h
    api.h
    tm_header_parser.h
    tm_parser.h
    tm_parser.h
    steam_to_vector_moving_window_cc.h
    vector_padding_cc.h
    fft_estimator_cc.h
    set_gain_by_tag_cc.h
    oqpsk_coherent_demod_cc.h
    frame_spliter_c.h
    ccsds_turbo_encode.h
    ccsds_turbo_decode.h
    attach_sync_marker.h
    ccsds_pseudo_randomizer.h
    kiss_encode_pdu.h
    kiss_decode_pdu.h
    fec_encode_b.h
    differential_phase_detection_1bit_cc.h DESTINATION include/dslwp
)
