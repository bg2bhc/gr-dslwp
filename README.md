# gr-dslwp
---------------------------------------
GNU Radio OOT Module for DSWLP, a lunar formation flying mission consists of 2 microsatellites.


## Install
---------------------------------------
 $ mkdir build 
 $ cd build 
 $ cmake ../ 
 $ make 
 $ sudo make install 
 $ sudo ldconfig 

GRC hier blocks are included in the hier folder. To install, please open the .grc files, press the "Generate flow graph" botton and restart GRC.

## Important Before Running
---------------------------------------
Please edit the path in Program Tracking CC in all the demod GRCs to the correct program tracking file. Currently gr-dslwp/examples/ 
program_tracking_dslwp-a_20180520_window1.txt for the first launch window.

As the bandwidth of the downlink signal is quite small, please calibrate your receiver frequency within 500 Hz. Warming up your receiver for at least 15 minutes, then transmit with a precise frequency, and edit the value of f_offset in frontend GRCs in Hz.

## Demod GRCs
---------------------------------------
6 different demod GRCs are provided for differnet frequencies and modes.
After sepration, the following GRCs should be used:
- demod_dslwp_gmsk_a0_500bps_0.25_dpd.grc (Satellite A Radio 0, 500 bps GMSK with 1/4 Turbo code)
- demod_dslwp_gmsk_a1_250bps_0.5_coherent.grc (Satellite A Radio 1, 250 bps GMSK with 1/2 Turbo code and precoder)
- demod_dslwp_gmsk_b0_500bps_0.25_dpd.grc (Satellite B Radio 0, 500 bps GMSK with 1/4 Turbo code) 
- demod_dslwp_gmsk_b1_250bps_0.5_coherent.grc (Satellite B Radio 1, 250 bps GMSK with 1/2 Turbo code and precoder)

## About TLE
---------------------------------------
A TLE was provided on http://lilacsat.hit.edu.cn/tle/dslwp.txt. It is not a precise way to describe a lunar transfer orbit, but can be used for antenna pointing during lunar transferring. After lunar injection, TLE is no longer useful.

## Coherent GMSK Demodulator
---------------------------------------
A GMSK demodulator under development, with OQPSK type PLL, sync word detection and Turbo codes.
In the examples folder:
- test_turbo_gmsk_selfloop.grc for software simulation. Try differnet ebn0, ebn0_threshold, pll_loop_bw, etc. for evaluation. 
- test_turbo_gmsk_tx.grc and test_turbo_gmsk_rx.grc can be used for a test with real channel with 2 USRPs.

Thanks to Gianluna for the turbo encoder / decoder: https://github.com/geeanlooca/deepspace-turbo
