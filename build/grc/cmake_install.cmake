# Install script for directory: /home/lilac/gr-dslwp/grc

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/lilac/prefix-3.8")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gnuradio/grc/blocks" TYPE FILE FILES
    "/home/lilac/gr-dslwp/grc/dslwp_ccsds_pseudo_randomizer.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_ccsds_turbo_decode.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_ccsds_turbo_encode.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_differential_phase_detection_1bit_cf.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_fft_estimator_cc.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_frame_spliter_c.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_frame_spliter_f.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_kiss_decode_pdu.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_kiss_encode_pdu.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_lrtc_mod_bc.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_oqpsk_coherent_demod_cc.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_program_tracking_cc.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_set_gain_by_tag_cc.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_steam_to_vector_moving_window_cc.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_tm_header_parser.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_tm_parser.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_vector_padding_cc.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_attach_sync_marker.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_tag_to_json_pdu_c.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_fft_estimator2_cc.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_lrtc_demod.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_fec_decode_b.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_fec_encode_b.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_tm_converter2.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_lrtc_demod2.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_attach_preamble_and_tailer.block.yml"
    "/home/lilac/gr-dslwp/grc/dslwp_station_info_pdu.block.yml"
    )
endif()

