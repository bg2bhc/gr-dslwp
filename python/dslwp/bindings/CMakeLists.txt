# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT dslwp_sources)
    message(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT dslwp_sources)

########################################################################
# Check for pygccxml
########################################################################
gr_python_check_module_raw("pygccxml" "import pygccxml" PYGCCXML_FOUND)

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND dslwp_python_files
    attach_preamble_and_tailer_python.cc
    attach_sync_marker_python.cc
    ccsds_pseudo_randomizer_python.cc
    ccsds_turbo_decode_python.cc
    ccsds_turbo_encode_python.cc
    differential_phase_detection_1bit_cf_python.cc
    fec_decode_b_python.cc
    fec_encode_b_python.cc
    fft_estimator2_cc_python.cc
    fft_estimator_cc_python.cc
    frame_spliter_c_python.cc
    frame_spliter_f_python.cc
    kiss_decode_pdu_python.cc
    kiss_encode_pdu_python.cc
    lrtc_demod_python.cc
    lrtc_demod2_python.cc
    lrtc_mod_bc_python.cc
    oqpsk_coherent_demod_cc_python.cc
    program_tracking_cc_python.cc
    set_gain_by_tag_cc_python.cc
    station_info_pdu_python.cc
    steam_to_vector_moving_window_cc_python.cc
    tag_to_json_pdu_c_python.cc
    tm_converter2_python.cc
    tm_header_parser_python.cc
    tm_parser_python.cc
    vector_padding_cc_python.cc python_bindings.cc)

gr_pybind_make_oot(dslwp ../../.. gr::dslwp "${dslwp_python_files}")

# copy bindings extension for use in QA test module
add_custom_command(
    TARGET dslwp_python
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:dslwp_python>
            ${PROJECT_BINARY_DIR}/test_modules/gnuradio/dslwp/)

install(
    TARGETS dslwp_python
    DESTINATION ${GR_PYTHON_DIR}/gnuradio/dslwp
    COMPONENT pythonapi)
