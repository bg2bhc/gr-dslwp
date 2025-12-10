/*
 * Copyright 2020 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <pybind11/pybind11.h>

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>

namespace py = pybind11;

// Headers for binding functions
/**************************************/
// The following comment block is used for
// gr_modtool to insert function prototypes
// Please do not delete
/**************************************/
// BINDING_FUNCTION_PROTOTYPES(
    void bind_attach_preamble_and_tailer(py::module& m);
    void bind_attach_sync_marker(py::module& m);
    void bind_ccsds_pseudo_randomizer(py::module& m);
    void bind_ccsds_turbo_decode(py::module& m);
    void bind_ccsds_turbo_encode(py::module& m);
    void bind_differential_phase_detection_1bit_cf(py::module& m);
    void bind_fec_decode_b(py::module& m);
    void bind_fec_encode_b(py::module& m);
    void bind_fft_estimator2_cc(py::module& m);
    void bind_fft_estimator_cc(py::module& m);
    void bind_frame_spliter_c(py::module& m);
    void bind_frame_spliter_f(py::module& m);
    void bind_kiss_decode_pdu(py::module& m);
    void bind_kiss_encode_pdu(py::module& m);
    void bind_lrtc_demod(py::module& m);
    void bind_lrtc_demod2(py::module& m);
    void bind_lrtc_mod_bc(py::module& m);
    void bind_oqpsk_coherent_demod_cc(py::module& m);
    void bind_program_tracking_cc(py::module& m);
    void bind_set_gain_by_tag_cc(py::module& m);
    void bind_station_info_pdu(py::module& m);
    void bind_steam_to_vector_moving_window_cc(py::module& m);
    void bind_tag_to_json_pdu_c(py::module& m);
    void bind_tm_converter2(py::module& m);
    void bind_tm_header_parser(py::module& m);
    void bind_tm_parser(py::module& m);
    void bind_vector_padding_cc(py::module& m);
// ) END BINDING_FUNCTION_PROTOTYPES


// We need this hack because import_array() returns NULL
// for newer Python versions.
// This function is also necessary because it ensures access to the C API
// and removes a warning.
void* init_numpy()
{
    import_array();
    return NULL;
}

PYBIND11_MODULE(dslwp_python, m)
{
    // Initialize the numpy C API
    // (otherwise we will see segmentation faults)
    init_numpy();

    // Allow access to base block methods
    py::module::import("gnuradio.gr");

    /**************************************/
    // The following comment block is used for
    // gr_modtool to insert binding function calls
    // Please do not delete
    /**************************************/
    // BINDING_FUNCTION_CALLS(
    bind_attach_preamble_and_tailer(m);
    bind_attach_sync_marker(m);
    bind_ccsds_pseudo_randomizer(m);
    bind_ccsds_turbo_decode(m);
    bind_ccsds_turbo_encode(m);
    bind_differential_phase_detection_1bit_cf(m);
    bind_fec_decode_b(m);
    bind_fec_encode_b(m);
    bind_fft_estimator2_cc(m);
    bind_fft_estimator_cc(m);
    bind_frame_spliter_c(m);
    bind_frame_spliter_f(m);
    bind_kiss_decode_pdu(m);
    bind_kiss_encode_pdu(m);
    bind_lrtc_demod(m);
    bind_lrtc_demod2(m);
    bind_lrtc_mod_bc(m);
    bind_oqpsk_coherent_demod_cc(m);
    bind_program_tracking_cc(m);
    bind_set_gain_by_tag_cc(m);
    bind_station_info_pdu(m);
    bind_steam_to_vector_moving_window_cc(m);
    bind_tag_to_json_pdu_c(m);
    bind_tm_converter2(m);
    bind_tm_header_parser(m);
    bind_tm_parser(m);
    bind_vector_padding_cc(m);
    // ) END BINDING_FUNCTION_CALLS
}