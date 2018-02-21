# Install script for directory: /home/lilac/gr-dslwp/include/dslwp

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/dslwp" TYPE FILE FILES
    "/home/lilac/gr-dslwp/include/dslwp/fft.h"
    "/home/lilac/gr-dslwp/include/dslwp/api.h"
    "/home/lilac/gr-dslwp/include/dslwp/tm_header_parser.h"
    "/home/lilac/gr-dslwp/include/dslwp/tm_parser.h"
    "/home/lilac/gr-dslwp/include/dslwp/tm_parser.h"
    "/home/lilac/gr-dslwp/include/dslwp/steam_to_vector_moving_window_cc.h"
    "/home/lilac/gr-dslwp/include/dslwp/vector_padding_cc.h"
    "/home/lilac/gr-dslwp/include/dslwp/fft_estimator_cc.h"
    "/home/lilac/gr-dslwp/include/dslwp/set_gain_by_tag_cc.h"
    "/home/lilac/gr-dslwp/include/dslwp/oqpsk_coherent_demod_cc.h"
    "/home/lilac/gr-dslwp/include/dslwp/frame_spliter_c.h"
    "/home/lilac/gr-dslwp/include/dslwp/ccsds_turbo_encode.h"
    "/home/lilac/gr-dslwp/include/dslwp/ccsds_turbo_decode.h"
    "/home/lilac/gr-dslwp/include/dslwp/attach_sync_marker.h"
    "/home/lilac/gr-dslwp/include/dslwp/ccsds_pseudo_randomizer.h"
    "/home/lilac/gr-dslwp/include/dslwp/kiss_encode_pdu.h"
    "/home/lilac/gr-dslwp/include/dslwp/kiss_decode_pdu.h"
    "/home/lilac/gr-dslwp/include/dslwp/fec_encode_b.h"
    "/home/lilac/gr-dslwp/include/dslwp/differential_phase_detection_1bit_cf.h"
    )
endif()

