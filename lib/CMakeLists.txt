# Copyright 2011,2012,2016 Free Software Foundation, Inc.
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
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
list(APPEND dslwp_sources
    ccsds/fifobuf.c
    ccsds/ccsds.c
    ccsds/metrics.c
    ccsds/rs.c
    ccsds/tab.c
    ccsds/viterbi27.c
    kiss/kiss.c
    ccsds/randomizer.c
    ccsds/libturbocodes.c
    ccsds/libconvcodes.c
    tm_header_parser_impl.cc
    tm_parser_impl.cc
    steam_to_vector_moving_window_cc_impl.cc
    vector_padding_cc_impl.cc
    fft_estimator_cc_impl.cc
    set_gain_by_tag_cc_impl.cc
    oqpsk_coherent_demod_cc_impl.cc
    frame_spliter_c_impl.cc
    ccsds_turbo_encode_impl.cc
    ccsds_turbo_decode_impl.cc
    attach_sync_marker_impl.cc
    ccsds_pseudo_randomizer_impl.cc
    kiss_encode_pdu_impl.cc
    kiss_decode_pdu_impl.cc
    fec_encode_b_impl.cc
    differential_phase_detection_1bit_cf_impl.cc
    frame_spliter_f_impl.cc )

set(dslwp_sources "${dslwp_sources}" PARENT_SCOPE)
if(NOT dslwp_sources)
	MESSAGE(STATUS "No C++ sources... skipping lib/")
	return()
endif(NOT dslwp_sources)

add_library(gnuradio-dslwp SHARED ${dslwp_sources})
target_link_libraries(gnuradio-dslwp ${Boost_LIBRARIES} ${GNURADIO_ALL_LIBRARIES})
set_target_properties(gnuradio-dslwp PROPERTIES DEFINE_SYMBOL "gnuradio_dslwp_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-dslwp PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
include(GrMiscUtils)
GR_LIBRARY_FOO(gnuradio-dslwp RUNTIME_COMPONENT "dslwp_runtime" DEVEL_COMPONENT "dslwp_devel")

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})

list(APPEND test_dslwp_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_dslwp.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_dslwp.cc
)

add_executable(test-dslwp ${test_dslwp_sources})

target_link_libraries(
  test-dslwp
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-dslwp
)

GR_ADD_TEST(test_dslwp test-dslwp)

########################################################################
# Print summary
########################################################################
message(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Building for version: ${VERSION} / ${LIBVER}")

