/* -*- c++ -*- */

#define DSLWP_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "dslwp_swig_doc.i"

%{
#include "dslwp/tm_header_parser.h"
#include "dslwp/tm_parser.h"
%}


%include "dslwp/tm_header_parser.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, tm_header_parser);


%include "dslwp/tm_parser.h"
GR_SWIG_BLOCK_MAGIC2(dslwp, tm_parser);
