/* -*- c++ -*- */

#define DSLWP_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "dslwp_swig_doc.i"

%{
#include "dslwp/tm_header_parser.h"
#include "dslwp/tm_parser.h"
#include "dslwp/steam_to_vector_moving_window_cc.h"
#include "dslwp/vector_padding_cc.h"
#include "dslwp/fft_estimator_cc.h"
#include "dslwp/set_gain_by_tag_cc.h"
#include "dslwp/oqpsk_coherent_demod_cc.h"
#include "dslwp/frame_spliter_c.h"
#include "dslwp/ccsds_turbo_encode.h"
#include "dslwp/ccsds_turbo_decode.h"
#include "dslwp/ccsds_pseudo_randomizer.h"
#include "dslwp/kiss_encode_pdu.h"
#include "dslwp/kiss_decode_pdu.h"
#include "dslwp/differential_phase_detection_1bit_cf.h"
#include "dslwp/frame_spliter_f.h"
#include "dslwp/program_tracking_cc.h"
#include "dslwp/lrtc_mod_bc.h"
#include "dslwp/attach_sync_marker.h"
#include "dslwp/tag_to_json_pdu_c.h"
#include "dslwp/fft_estimator2_cc.h"
#include "dslwp/lrtc_demod.h"
#include "dslwp/fec_decode_b.h"
#include "dslwp/fec_encode_b.h"
#include "dslwp/tm_converter2.h"
#include "dslwp/lrtc_demod2.h"
#include "dslwp/attach_preamble_and_tailer.h"
%}

%include "dslwp/tm_header_parser.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, tm_header_parser);


%include "dslwp/tm_parser.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, tm_parser);



%include "dslwp/steam_to_vector_moving_window_cc.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, steam_to_vector_moving_window_cc);
%include "dslwp/vector_padding_cc.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, vector_padding_cc);
%include "dslwp/fft_estimator_cc.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, fft_estimator_cc);
%include "dslwp/set_gain_by_tag_cc.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, set_gain_by_tag_cc);

%include "dslwp/oqpsk_coherent_demod_cc.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, oqpsk_coherent_demod_cc);
%include "dslwp/frame_spliter_c.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, frame_spliter_c);
%include "dslwp/ccsds_turbo_encode.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, ccsds_turbo_encode);

%include "dslwp/ccsds_turbo_decode.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, ccsds_turbo_decode);

%include "dslwp/ccsds_pseudo_randomizer.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, ccsds_pseudo_randomizer);
%include "dslwp/kiss_encode_pdu.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, kiss_encode_pdu);
%include "dslwp/kiss_decode_pdu.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, kiss_decode_pdu);

%include "dslwp/differential_phase_detection_1bit_cf.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, differential_phase_detection_1bit_cf);
%include "dslwp/frame_spliter_f.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, frame_spliter_f);

%include "dslwp/program_tracking_cc.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, program_tracking_cc);
%include "dslwp/lrtc_mod_bc.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, lrtc_mod_bc);

%include "dslwp/attach_sync_marker.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, attach_sync_marker);
%include "dslwp/tag_to_json_pdu_c.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, tag_to_json_pdu_c);
%include "dslwp/fft_estimator2_cc.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, fft_estimator2_cc);
%include "dslwp/lrtc_demod.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, lrtc_demod);
%include "dslwp/fec_decode_b.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, fec_decode_b);

%include "dslwp/fec_encode_b.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, fec_encode_b);
%include "dslwp/tm_converter2.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, tm_converter2);
%include "dslwp/lrtc_demod2.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, lrtc_demod2);
%include "dslwp/attach_preamble_and_tailer.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, attach_preamble_and_tailer);
