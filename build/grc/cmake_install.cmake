# Install script for directory: /home/lilac/gr-dslwp/grc

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gnuradio/grc/blocks" TYPE FILE FILES
    "/home/lilac/gr-dslwp/grc/dslwp_tm_header_parser.xml"
    "/home/lilac/gr-dslwp/grc/dslwp_tm_parser.xml"
    "/home/lilac/gr-dslwp/grc/dslwp_tm_parser.xml"
    "/home/lilac/gr-dslwp/grc/dslwp_steam_to_vector_moving_window_cc.xml"
    "/home/lilac/gr-dslwp/grc/dslwp_vector_padding_cc.xml"
    "/home/lilac/gr-dslwp/grc/dslwp_fft_estimator_cc.xml"
    "/home/lilac/gr-dslwp/grc/dslwp_set_gain_by_tag_cc.xml"
    "/home/lilac/gr-dslwp/grc/dslwp_oqpsk_coherent_demod_cc.xml"
    "/home/lilac/gr-dslwp/grc/dslwp_frame_spliter_c.xml"
    "/home/lilac/gr-dslwp/grc/dslwp_ccsds_turbo_encode.xml"
    "/home/lilac/gr-dslwp/grc/dslwp_ccsds_turbo_decode.xml"
    "/home/lilac/gr-dslwp/grc/dslwp_attach_sync_marker.xml"
    "/home/lilac/gr-dslwp/grc/dslwp_ccsds_pseudo_randomizer.xml"
    "/home/lilac/gr-dslwp/grc/dslwp_kiss_encode_pdu.xml"
    "/home/lilac/gr-dslwp/grc/dslwp_kiss_decode_pdu.xml"
    "/home/lilac/gr-dslwp/grc/dslwp_fec_encode_b.xml"
    "/home/lilac/gr-dslwp/grc/dslwp_differential_phase_detection_1bit_cf.xml"
    )
endif()

