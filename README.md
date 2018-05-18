 # gr-dslwp
---------------------------------------
GNU Radio OOT Module for DSWLP, a lunar formation flying mission consists of 2 microsatellites.


## Install
---------------------------------------
$mkdir build 
$cd build 
$cmake ../ 
$make 
$sudo make install 
$sudo ldconfig 

GRC hier blocks are included in the hier folder. To install, please open the .grc files, press the "Generate flow graph" botton and restart GRC.

## Important Before Running
---------------------------------------
Please edit the path in Program Tracking CC in all the demod grc to the correct program tracking file. Currently /examples/ 
program_tracking_dslwp-a_20180520_window1.txt for the first launch window.


## Coherent GMSK Demodulator
---------------------------------------
A GMSK demodulator under development, with OQPSK type PLL, sync word detection and Turbo codes.
In the examples folder:
- test_turbo_gmsk_selfloop.grc for software simulation. Try differnet ebn0, ebn0_threshold, pll_loop_bw, etc. for evaluation. 
- test_turbo_gmsk_tx.grc and test_turbo_gmsk_rx.grc can be used for a test with real channel with 2 USRPs.



Thanks to Gianluna for the turbo encoder / decoder: https://github.com/geeanlooca/deepspace-turbo
