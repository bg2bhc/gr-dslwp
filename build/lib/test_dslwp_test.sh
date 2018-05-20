#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/lilac/gr-dslwp/lib
export PATH=/home/lilac/gr-dslwp/build/lib:$PATH
export LD_LIBRARY_PATH=/home/lilac/gr-dslwp/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-dslwp 
