/* -*- c++ -*- */

#define DSLWP_API

%include "gnuradio.i"			// the common stuff

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
#include "dslwp/attach_sync_marker.h"
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
%include "dslwp/attach_sync_marker.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, attach_sync_marker);
