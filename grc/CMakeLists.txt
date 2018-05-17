# Copyright 2011 Free Software Foundation, Inc.
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
install(FILES
    dslwp_tm_header_parser.xml
    dslwp_tm_parser.xml
    dslwp_tm_parser.xml
    dslwp_steam_to_vector_moving_window_cc.xml
    dslwp_vector_padding_cc.xml
    dslwp_fft_estimator_cc.xml
    dslwp_set_gain_by_tag_cc.xml
    dslwp_oqpsk_coherent_demod_cc.xml
    dslwp_frame_spliter_c.xml
    dslwp_ccsds_turbo_encode.xml
    dslwp_ccsds_turbo_decode.xml
    dslwp_attach_sync_marker.xml
    dslwp_ccsds_pseudo_randomizer.xml
    dslwp_kiss_encode_pdu.xml
    dslwp_kiss_decode_pdu.xml
    dslwp_fec_encode_b.xml
    dslwp_differential_phase_detection_1bit_cf.xml
    dslwp_frame_spliter_f.xml
    dslwp_program_tracking_cc.xml DESTINATION share/gnuradio/grc/blocks
)
