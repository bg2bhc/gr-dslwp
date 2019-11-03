#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: demod_dslwp_gmsk_b1_250bps_0r5_coherent
# Generated: Mon Nov  4 00:12:28 2019
##################################################

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"

import os
import sys
sys.path.append(os.environ.get('GRC_HIER_PATH', os.path.expanduser('~/.grc_gnuradio')))

from PyQt4 import Qt
from fft_correlator_hier import fft_correlator_hier  # grc-generated hier_block
from gnuradio import analog
from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import filter
from gnuradio import gr
from gnuradio import qtgui
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from grc_param import *
from optparse import OptionParser
import dslwp
import math
import sip
from gnuradio import qtgui


class demod_dslwp_gmsk_b1_250bps_0r5_coherent(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "demod_dslwp_gmsk_b1_250bps_0r5_coherent")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("demod_dslwp_gmsk_b1_250bps_0r5_coherent")
        qtgui.util.check_set_qss()
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
            pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "demod_dslwp_gmsk_b1_250bps_0r5_coherent")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())

        ##################################################
        # Variables
        ##################################################
        self.sps = sps = 8
        self.ebn0_threshold = ebn0_threshold = -2
        self.snr_threshold = snr_threshold = 10.0**(ebn0_threshold/10.0)/sps
        self.samp_rate = samp_rate = 2000
        self.pll_loop_bw = pll_loop_bw = 8
        self.if_rate = if_rate = 40000
        self.f_offset = f_offset = 0

        ##################################################
        # Blocks
        ##################################################
        self._f_offset_tool_bar = Qt.QToolBar(self)
        self._f_offset_tool_bar.addWidget(Qt.QLabel("f_offset"+": "))
        self._f_offset_line_edit = Qt.QLineEdit(str(self.f_offset))
        self._f_offset_tool_bar.addWidget(self._f_offset_line_edit)
        self._f_offset_line_edit.returnPressed.connect(
        	lambda: self.set_f_offset(eng_notation.str_to_num(str(self._f_offset_line_edit.text().toAscii()))))
        self.top_grid_layout.addWidget(self._f_offset_tool_bar, 1,0)
        self.qtgui_waterfall_sink_x_0 = qtgui.waterfall_sink_c(
        	1024, #size
        	firdes.WIN_BLACKMAN_hARRIS, #wintype
        	0, #fc
        	samp_rate, #bw
        	"", #name
                1 #number of inputs
        )
        self.qtgui_waterfall_sink_x_0.set_update_time(0.8)
        self.qtgui_waterfall_sink_x_0.enable_grid(False)
        self.qtgui_waterfall_sink_x_0.enable_axis_labels(True)

        if not True:
          self.qtgui_waterfall_sink_x_0.disable_legend()

        if "complex" == "float" or "complex" == "msg_float":
          self.qtgui_waterfall_sink_x_0.set_plot_pos_half(not True)

        labels = ['', '', '', '', '',
                  '', '', '', '', '']
        colors = [0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]
        for i in xrange(1):
            if len(labels[i]) == 0:
                self.qtgui_waterfall_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_waterfall_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_waterfall_sink_x_0.set_color_map(i, colors[i])
            self.qtgui_waterfall_sink_x_0.set_line_alpha(i, alphas[i])

        self.qtgui_waterfall_sink_x_0.set_intensity_range(-140, -90)

        self._qtgui_waterfall_sink_x_0_win = sip.wrapinstance(self.qtgui_waterfall_sink_x_0.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_waterfall_sink_x_0_win, 2,0)
        self.qtgui_freq_sink_x_0_0 = qtgui.freq_sink_c(
        	1024, #size
        	firdes.WIN_BLACKMAN_hARRIS, #wintype
        	0, #fc
        	samp_rate, #bw
        	"", #name
        	1 #number of inputs
        )
        self.qtgui_freq_sink_x_0_0.set_update_time(0.10)
        self.qtgui_freq_sink_x_0_0.set_y_axis(-140, -20)
        self.qtgui_freq_sink_x_0_0.set_y_label('Relative Gain', 'dB')
        self.qtgui_freq_sink_x_0_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, 0.0, 0, "")
        self.qtgui_freq_sink_x_0_0.enable_autoscale(False)
        self.qtgui_freq_sink_x_0_0.enable_grid(True)
        self.qtgui_freq_sink_x_0_0.set_fft_average(1.0)
        self.qtgui_freq_sink_x_0_0.enable_axis_labels(True)
        self.qtgui_freq_sink_x_0_0.enable_control_panel(False)

        if not True:
          self.qtgui_freq_sink_x_0_0.disable_legend()

        if "complex" == "float" or "complex" == "msg_float":
          self.qtgui_freq_sink_x_0_0.set_plot_pos_half(not True)

        labels = ['', '', '', '', '',
                  '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "black", "cyan",
                  "magenta", "yellow", "dark red", "dark green", "dark blue"]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]
        for i in xrange(1):
            if len(labels[i]) == 0:
                self.qtgui_freq_sink_x_0_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_freq_sink_x_0_0.set_line_label(i, labels[i])
            self.qtgui_freq_sink_x_0_0.set_line_width(i, widths[i])
            self.qtgui_freq_sink_x_0_0.set_line_color(i, colors[i])
            self.qtgui_freq_sink_x_0_0.set_line_alpha(i, alphas[i])

        self._qtgui_freq_sink_x_0_0_win = sip.wrapinstance(self.qtgui_freq_sink_x_0_0.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_freq_sink_x_0_0_win, 4,0)
        self.qtgui_const_sink_x_0 = qtgui.const_sink_c(
        	512, #size
        	"", #name
        	1 #number of inputs
        )
        self.qtgui_const_sink_x_0.set_update_time(512.0/125.0)
        self.qtgui_const_sink_x_0.set_y_axis(-4, 4)
        self.qtgui_const_sink_x_0.set_x_axis(-4, 4)
        self.qtgui_const_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, "")
        self.qtgui_const_sink_x_0.enable_autoscale(False)
        self.qtgui_const_sink_x_0.enable_grid(False)
        self.qtgui_const_sink_x_0.enable_axis_labels(True)

        if not True:
          self.qtgui_const_sink_x_0.disable_legend()

        labels = ['', '', '', '', '',
                  '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        colors = ["blue", "red", "red", "red", "red",
                  "red", "red", "red", "red", "red"]
        styles = [0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0]
        markers = [0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0]
        alphas = [0.3, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]
        for i in xrange(1):
            if len(labels[i]) == 0:
                self.qtgui_const_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_const_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_const_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_const_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_const_sink_x_0.set_line_style(i, styles[i])
            self.qtgui_const_sink_x_0.set_line_marker(i, markers[i])
            self.qtgui_const_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_const_sink_x_0_win = sip.wrapinstance(self.qtgui_const_sink_x_0.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_const_sink_x_0_win, 3,0)
        self.low_pass_filter_3_0_0 = filter.fir_filter_ccf(20, firdes.low_pass(
        	1, if_rate, 0.95e3, 0.05e3, firdes.WIN_HAMMING, 6.76))
        self.fft_correlator_hier_0 = fft_correlator_hier(
            fft_size=512,
            nthreads=1,
            tap_len=512,
            taps=[0.986752+0.162236j, 0.961165+0.275976j, 0.909253+0.416245j, 0.823810+0.566866j, 0.704089+0.710112j, 0.554654+0.832081j, 0.382467+0.923969j, 0.195052+0.980793j, 0.000006+1.000000j, -0.195011+0.980801j, -0.382250+0.924059j, -0.553737+0.832692j, -0.701059+0.713104j, -0.815998+0.578055j, -0.893407+0.449249j, -0.934886+0.354949j, -0.947363+0.320163j, -0.934914+0.354874j, -0.893617+0.448830j, -0.817269+0.576256j, -0.707107+0.707107j, -0.576256+0.817269j, -0.448830+0.893617j, -0.354872+0.934915j, -0.320152+0.947366j, -0.354872+0.934915j, -0.448830+0.893617j, -0.576256+0.817269j, -0.707107+0.707107j, -0.817269+0.576256j, -0.893617+0.448830j, -0.934915+0.354872j, -0.947366+0.320152j, -0.934915+0.354872j, -0.893617+0.448830j, -0.817269+0.576256j, -0.707107+0.707107j, -0.576256+0.817269j, -0.448830+0.893617j, -0.354874+0.934914j, -0.320163+0.947363j, -0.354949+0.934886j, -0.449249+0.893407j, -0.578055+0.815998j, -0.713104+0.701059j, -0.832692+0.553737j, -0.924059+0.382250j, -0.980801+0.195010j, -1.000000-0.000012j, -0.980785-0.195092j, -0.923879-0.382684j, -0.831470-0.555570j, -0.707107-0.707107j, -0.555570-0.831470j, -0.382683-0.923880j, -0.195090-0.980785j, -0.000000-1.000000j, 0.195090-0.980785j, 0.382683-0.923880j, 0.555570-0.831470j, 0.707107-0.707107j, 0.831470-0.555570j, 0.923879-0.382684j, 0.980785-0.195092j, 1.000000-0.000012j, 0.980801+0.195010j, 0.924059+0.382250j, 0.832692+0.553737j, 0.713104+0.701059j, 0.578055+0.815998j, 0.449249+0.893407j, 0.354949+0.934886j, 0.320163+0.947363j, 0.354874+0.934914j, 0.448830+0.893617j, 0.576256+0.817269j, 0.707107+0.707107j, 0.817269+0.576256j, 0.893617+0.448830j, 0.934914+0.354874j, 0.947363+0.320163j, 0.934886+0.354949j, 0.893407+0.449249j, 0.815998+0.578055j, 0.701059+0.713104j, 0.553737+0.832692j, 0.382250+0.924059j, 0.195012+0.980801j, 0.000000+1.000000j, -0.195012+0.980801j, -0.382250+0.924059j, -0.553737+0.832692j, -0.701059+0.713104j, -0.815998+0.578055j, -0.893407+0.449249j, -0.934885+0.354950j, -0.947359+0.320174j, -0.934885+0.354950j, -0.893407+0.449249j, -0.815998+0.578055j, -0.701059+0.713104j, -0.553737+0.832692j, -0.382250+0.924059j, -0.195010+0.980801j, 0.000012+1.000000j, 0.195092+0.980785j, 0.382684+0.923879j, 0.555570+0.831470j, 0.707107+0.707107j, 0.831470+0.555570j, 0.923879+0.382684j, 0.980785+0.195092j, 1.000000+0.000012j, 0.980801-0.195010j, 0.924059-0.382250j, 0.832692-0.553737j, 0.713104-0.701059j, 0.578055-0.815998j, 0.449249-0.893407j, 0.354950-0.934885j, 0.320174-0.947359j, 0.354950-0.934885j, 0.449249-0.893407j, 0.578055-0.815998j, 0.713104-0.701059j, 0.832692-0.553737j, 0.924059-0.382250j, 0.980801-0.195012j, 1.000000-0.000000j, 0.980801+0.195012j, 0.924059+0.382250j, 0.832692+0.553737j, 0.713104+0.701059j, 0.578055+0.815998j, 0.449249+0.893407j, 0.354950+0.934885j, 0.320174+0.947359j, 0.354950+0.934885j, 0.449249+0.893407j, 0.578055+0.815998j, 0.713104+0.701059j, 0.832692+0.553737j, 0.924059+0.382250j, 0.980801+0.195012j, 1.000000-0.000000j, 0.980801-0.195012j, 0.924059-0.382250j, 0.832692-0.553737j, 0.713104-0.701059j, 0.578055-0.815998j, 0.449249-0.893407j, 0.354950-0.934885j, 0.320174-0.947359j, 0.354950-0.934885j, 0.449249-0.893407j, 0.578055-0.815998j, 0.713104-0.701059j, 0.832692-0.553737j, 0.924059-0.382250j, 0.980801-0.195012j, 1.000000-0.000000j, 0.980801+0.195012j, 0.924059+0.382250j, 0.832692+0.553737j, 0.713104+0.701059j, 0.578055+0.815998j, 0.449249+0.893407j, 0.354950+0.934885j, 0.320174+0.947359j, 0.354950+0.934885j, 0.449249+0.893407j, 0.578055+0.815998j, 0.713104+0.701059j, 0.832692+0.553737j, 0.924059+0.382250j, 0.980801+0.195010j, 1.000000-0.000012j, 0.980785-0.195092j, 0.923879-0.382684j, 0.831470-0.555570j, 0.707107-0.707107j, 0.555570-0.831470j, 0.382684-0.923879j, 0.195092-0.980785j, 0.000012-1.000000j, -0.195010-0.980801j, -0.382250-0.924059j, -0.553737-0.832692j, -0.701059-0.713104j, -0.815998-0.578055j, -0.893407-0.449249j, -0.934885-0.354950j, -0.947359-0.320174j, -0.934885-0.354950j, -0.893407-0.449249j, -0.815998-0.578055j, -0.701059-0.713104j, -0.553737-0.832692j, -0.382250-0.924059j, -0.195010-0.980801j, 0.000012-1.000000j, 0.195092-0.980785j, 0.382684-0.923879j, 0.555570-0.831470j, 0.707107-0.707107j, 0.831470-0.555570j, 0.923880-0.382683j, 0.980785-0.195090j, 1.000000-0.000000j, 0.980785+0.195090j, 0.923880+0.382683j, 0.831470+0.555570j, 0.707107+0.707107j, 0.555570+0.831470j, 0.382684+0.923879j, 0.195092+0.980785j, 0.000012+1.000000j, -0.195010+0.980801j, -0.382250+0.924059j, -0.553737+0.832692j, -0.701059+0.713104j, -0.815998+0.578055j, -0.893407+0.449249j, -0.934885+0.354950j, -0.947359+0.320174j, -0.934885+0.354950j, -0.893407+0.449249j, -0.815998+0.578055j, -0.701059+0.713104j, -0.553737+0.832692j, -0.382250+0.924059j, -0.195010+0.980801j, 0.000012+1.000000j, 0.195092+0.980785j, 0.382684+0.923879j, 0.555570+0.831470j, 0.707107+0.707107j, 0.831470+0.555570j, 0.923879+0.382684j, 0.980785+0.195092j, 1.000000+0.000012j, 0.980801-0.195010j, 0.924059-0.382250j, 0.832692-0.553737j, 0.713104-0.701059j, 0.578055-0.815998j, 0.449249-0.893407j, 0.354950-0.934885j, 0.320174-0.947359j, 0.354950-0.934885j, 0.449249-0.893407j, 0.578055-0.815998j, 0.713104-0.701059j, 0.832692-0.553737j, 0.924059-0.382250j, 0.980801-0.195010j, 1.000000+0.000012j, 0.980785+0.195092j, 0.923879+0.382684j, 0.831470+0.555570j, 0.707107+0.707107j, 0.555570+0.831470j, 0.382683+0.923880j, 0.195090+0.980785j, 0.000000+1.000000j, -0.195090+0.980785j, -0.382683+0.923880j, -0.555570+0.831470j, -0.707107+0.707107j, -0.831470+0.555570j, -0.923879+0.382684j, -0.980785+0.195092j, -1.000000+0.000012j, -0.980801-0.195010j, -0.924059-0.382250j, -0.832692-0.553737j, -0.713104-0.701059j, -0.578055-0.815998j, -0.449249-0.893407j, -0.354950-0.934885j, -0.320174-0.947359j, -0.354950-0.934885j, -0.449249-0.893407j, -0.578055-0.815998j, -0.713104-0.701059j, -0.832692-0.553737j, -0.924059-0.382250j, -0.980801-0.195010j, -1.000000+0.000012j, -0.980785+0.195092j, -0.923879+0.382684j, -0.831470+0.555570j, -0.707107+0.707107j, -0.555570+0.831470j, -0.382683+0.923880j, -0.195090+0.980785j, 0.000000+1.000000j, 0.195090+0.980785j, 0.382683+0.923880j, 0.555570+0.831470j, 0.707107+0.707107j, 0.831470+0.555570j, 0.923879+0.382684j, 0.980785+0.195092j, 1.000000+0.000012j, 0.980801-0.195010j, 0.924059-0.382250j, 0.832692-0.553737j, 0.713104-0.701059j, 0.578055-0.815998j, 0.449249-0.893407j, 0.354950-0.934885j, 0.320174-0.947359j, 0.354950-0.934885j, 0.449249-0.893407j, 0.578055-0.815998j, 0.713104-0.701059j, 0.832692-0.553737j, 0.924059-0.382250j, 0.980801-0.195010j, 1.000000+0.000012j, 0.980785+0.195092j, 0.923879+0.382684j, 0.831470+0.555570j, 0.707107+0.707107j, 0.555570+0.831470j, 0.382683+0.923880j, 0.195090+0.980785j, 0.000000+1.000000j, -0.195090+0.980785j, -0.382683+0.923880j, -0.555570+0.831470j, -0.707107+0.707107j, -0.831470+0.555570j, -0.923879+0.382684j, -0.980785+0.195092j, -1.000000+0.000012j, -0.980801-0.195010j, -0.924059-0.382250j, -0.832692-0.553737j, -0.713104-0.701059j, -0.578055-0.815998j, -0.449249-0.893407j, -0.354949-0.934886j, -0.320163-0.947363j, -0.354874-0.934914j, -0.448830-0.893617j, -0.576256-0.817269j, -0.707107-0.707107j, -0.817269-0.576256j, -0.893617-0.448830j, -0.934915-0.354872j, -0.947366-0.320152j, -0.934915-0.354872j, -0.893617-0.448830j, -0.817269-0.576256j, -0.707107-0.707107j, -0.576256-0.817269j, -0.448830-0.893617j, -0.354874-0.934914j, -0.320163-0.947363j, -0.354949-0.934886j, -0.449249-0.893407j, -0.578055-0.815998j, -0.713104-0.701059j, -0.832692-0.553737j, -0.924059-0.382250j, -0.980801-0.195012j, -1.000000+0.000000j, -0.980801+0.195012j, -0.924059+0.382250j, -0.832692+0.553737j, -0.713104+0.701059j, -0.578055+0.815998j, -0.449249+0.893407j, -0.354950+0.934885j, -0.320174+0.947359j, -0.354950+0.934885j, -0.449249+0.893407j, -0.578055+0.815998j, -0.713104+0.701059j, -0.832692+0.553737j, -0.924059+0.382250j, -0.980801+0.195012j, -1.000000+0.000000j, -0.980801-0.195012j, -0.924059-0.382250j, -0.832692-0.553737j, -0.713104-0.701059j, -0.578055-0.815998j, -0.449249-0.893407j, -0.354950-0.934885j, -0.320174-0.947359j, -0.354950-0.934885j, -0.449249-0.893407j, -0.578055-0.815998j, -0.713104-0.701059j, -0.832692-0.553737j, -0.924059-0.382250j, -0.980801-0.195010j, -1.000000+0.000012j, -0.980785+0.195092j, -0.923879+0.382684j, -0.831470+0.555570j, -0.707107+0.707107j, -0.555570+0.831470j, -0.382684+0.923879j, -0.195092+0.980785j, -0.000012+1.000000j, 0.195010+0.980801j, 0.382250+0.924059j, 0.553737+0.832692j, 0.701059+0.713104j, 0.815998+0.578055j, 0.893407+0.449249j, 0.934886+0.354949j, 0.947363+0.320163j, 0.934914+0.354874j, 0.893617+0.448830j, 0.817269+0.576256j, 0.707107+0.707107j, 0.576256+0.817269j, 0.448830+0.893617j, 0.354872+0.934915j, 0.320152+0.947366j, 0.354872+0.934915j, 0.448830+0.893617j, 0.576256+0.817269j, 0.707107+0.707107j, 0.817269+0.576256j, 0.893617+0.448830j, 0.934915+0.354872j, 0.947366+0.320152j, 0.934915+0.354872j, 0.893617+0.448830j, 0.817269+0.576256j, 0.707107+0.707107j, 0.576256+0.817269j, 0.448830+0.893617j, 0.354874+0.934914j, 0.320163+0.947363j, 0.354949+0.934886j, 0.449249+0.893407j, 0.578055+0.815998j, 0.713104+0.701059j, 0.832692+0.553737j, 0.924059+0.382250j, 0.980801+0.195010j, 1.000000-0.000012j, 0.980785-0.195092j, 0.923879-0.382684j, 0.831470-0.555570j, 0.707107-0.707107j, 0.555570-0.831470j, 0.382684-0.923879j, 0.195092-0.980785j, 0.000012-1.000000j, -0.195010-0.980801j, -0.382250-0.924059j, -0.553737-0.832692j, -0.701059-0.713104j, -0.815998-0.578055j, -0.893407-0.449249j, -0.934885-0.354950j, -0.947359-0.320174j, -0.934885-0.354950j, -0.893407-0.449249j, -0.815998-0.578055j, -0.701059-0.713104j, -0.553737-0.832692j, -0.382250-0.924059j, -0.195010-0.980801j, 0.000012-1.000000j, 0.195092-0.980785j, 0.382684-0.923879j, 0.555570-0.831470j, 0.707107-0.707107j, 0.831470-0.555570j, 0.923880-0.382683j, 0.980785-0.195090j, 1.000000-0.000000j, 0.980785+0.195090j, 0.923880+0.382683j, 0.831470+0.555570j, 0.707107+0.707107j, 0.555570+0.831470j, 0.382684+0.923879j, 0.195092+0.980785j, 0.000012+1.000000j, -0.195010+0.980801j, -0.382250+0.924059j, -0.553737+0.832692j, -0.701059+0.713104j, -0.815998+0.578055j, -0.893407+0.449249j, -0.934886+0.354949j, -0.947363+0.320163j, -0.934914+0.354874j, -0.893617+0.448830j, -0.817269+0.576256j, -0.707107+0.707107j, -0.576256+0.817269j, -0.448830+0.893617j, -0.354873+0.934914j, -0.320157+0.947364j, -0.354911+0.934900j, -0.449039+0.893512j, -0.577156+0.816634j, -0.710112+0.704089j, -0.825057+0.565049j, -0.909448+0.415819j, -0.961187+0.275898j],
            threshold=snr_threshold,
        )
        self.top_layout.addWidget(self.fft_correlator_hier_0)
        self.dslwp_tm_parser_0 = dslwp.tm_parser()
        self.dslwp_tm_header_parser_0 = dslwp.tm_header_parser()
        self.dslwp_set_gain_by_tag_cc_0 = dslwp.set_gain_by_tag_cc(512, 1)
        self.dslwp_program_tracking_cc_0 = dslwp.program_tracking_cc(0, 1526774400, '/home/lilac/program_tracking_dslwp-b_20180601.txt', lon, lat, alt, 436400000, if_rate, False, True)
        self.dslwp_oqpsk_coherent_demod_cc_0 = dslwp.oqpsk_coherent_demod_cc(sps*2, ([0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000005, 0.000035, 0.000189, 0.000787, 0.002569, 0.006746, 0.014618, 0.026868, 0.043018, 0.061431, 0.079856, 0.096160, 0.108824, 0.117144, 0.121157, 0.121157, 0.117144, 0.108824, 0.096160, 0.079856, 0.061431, 0.043018, 0.026868, 0.014618, 0.006746, 0.002569, 0.000787, 0.000189, 0.000035, 0.000005, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000]), 4, 1, 2.0*math.pi*pll_loop_bw/samp_rate, 0.707, 3.14, -3.14, 0, 0.05, 0.707, 1.5, 0)
        self.dslwp_kiss_encode_pdu_0 = dslwp.kiss_encode_pdu(-1)
        self.dslwp_kiss_decode_pdu_1 = dslwp.kiss_decode_pdu()
        self.dslwp_kiss_decode_pdu_0 = dslwp.kiss_decode_pdu()
        self.dslwp_frame_spliter_c_0 = dslwp.frame_spliter_c('payload_start', 3576)
        self.dslwp_ccsds_turbo_decode_0 = dslwp.ccsds_turbo_decode(223, 1, 2, 2, 0.707, 1)
        self.dslwp_ccsds_pseudo_randomizer_0 = dslwp.ccsds_pseudo_randomizer(3)
        self.blocks_udp_source_0 = blocks.udp_source(gr.sizeof_gr_complex*1, '127.0.0.1', 7177, 1472, False)
        self.blocks_socket_pdu_0 = blocks.socket_pdu("TCP_CLIENT", '127.0.0.1', '60064', 10000, False)
        self.blocks_multiply_xx_0 = blocks.multiply_vcc(1)
        self.blocks_message_debug_0_0_0 = blocks.message_debug()
        self.analog_sig_source_x_0 = analog.sig_source_c(if_rate, analog.GR_COS_WAVE, f_offset, 1, 0)

        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.dslwp_ccsds_pseudo_randomizer_0, 'out'), (self.dslwp_ccsds_turbo_decode_0, 'in'))
        self.msg_connect((self.dslwp_ccsds_turbo_decode_0, 'out'), (self.dslwp_kiss_encode_pdu_0, 'in'))
        self.msg_connect((self.dslwp_ccsds_turbo_decode_0, 'out'), (self.dslwp_tm_header_parser_0, 'in'))
        self.msg_connect((self.dslwp_frame_spliter_c_0, 'out'), (self.dslwp_ccsds_pseudo_randomizer_0, 'in'))
        self.msg_connect((self.dslwp_kiss_decode_pdu_0, 'out'), (self.dslwp_tm_parser_0, 'in'))
        self.msg_connect((self.dslwp_kiss_decode_pdu_1, 'out'), (self.dslwp_tm_parser_0, 'in'))
        self.msg_connect((self.dslwp_kiss_encode_pdu_0, 'out'), (self.blocks_socket_pdu_0, 'pdus'))
        self.msg_connect((self.dslwp_tm_header_parser_0, 'out 1'), (self.blocks_message_debug_0_0_0, 'print_pdu'))
        self.msg_connect((self.dslwp_tm_header_parser_0, 'out 2'), (self.dslwp_kiss_decode_pdu_0, 'in'))
        self.msg_connect((self.dslwp_tm_header_parser_0, 'out 0'), (self.dslwp_kiss_decode_pdu_1, 'in'))
        self.connect((self.analog_sig_source_x_0, 0), (self.blocks_multiply_xx_0, 0))
        self.connect((self.blocks_multiply_xx_0, 0), (self.dslwp_program_tracking_cc_0, 0))
        self.connect((self.blocks_udp_source_0, 0), (self.blocks_multiply_xx_0, 1))
        self.connect((self.dslwp_oqpsk_coherent_demod_cc_0, 0), (self.dslwp_frame_spliter_c_0, 0))
        self.connect((self.dslwp_oqpsk_coherent_demod_cc_0, 0), (self.qtgui_const_sink_x_0, 0))
        self.connect((self.dslwp_program_tracking_cc_0, 0), (self.low_pass_filter_3_0_0, 0))
        self.connect((self.dslwp_set_gain_by_tag_cc_0, 0), (self.dslwp_oqpsk_coherent_demod_cc_0, 0))
        self.connect((self.fft_correlator_hier_0, 0), (self.dslwp_set_gain_by_tag_cc_0, 0))
        self.connect((self.low_pass_filter_3_0_0, 0), (self.fft_correlator_hier_0, 0))
        self.connect((self.low_pass_filter_3_0_0, 0), (self.qtgui_freq_sink_x_0_0, 0))
        self.connect((self.low_pass_filter_3_0_0, 0), (self.qtgui_waterfall_sink_x_0, 0))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "demod_dslwp_gmsk_b1_250bps_0r5_coherent")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_sps(self):
        return self.sps

    def set_sps(self, sps):
        self.sps = sps
        self.set_snr_threshold(10.0**(self.ebn0_threshold/10.0)/self.sps)

    def get_ebn0_threshold(self):
        return self.ebn0_threshold

    def set_ebn0_threshold(self, ebn0_threshold):
        self.ebn0_threshold = ebn0_threshold
        self.set_snr_threshold(10.0**(self.ebn0_threshold/10.0)/self.sps)

    def get_snr_threshold(self):
        return self.snr_threshold

    def set_snr_threshold(self, snr_threshold):
        self.snr_threshold = snr_threshold
        self.fft_correlator_hier_0.set_threshold(self.snr_threshold)

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.qtgui_waterfall_sink_x_0.set_frequency_range(0, self.samp_rate)
        self.qtgui_freq_sink_x_0_0.set_frequency_range(0, self.samp_rate)

    def get_pll_loop_bw(self):
        return self.pll_loop_bw

    def set_pll_loop_bw(self, pll_loop_bw):
        self.pll_loop_bw = pll_loop_bw

    def get_if_rate(self):
        return self.if_rate

    def set_if_rate(self, if_rate):
        self.if_rate = if_rate
        self.low_pass_filter_3_0_0.set_taps(firdes.low_pass(1, self.if_rate, 0.95e3, 0.05e3, firdes.WIN_HAMMING, 6.76))
        self.analog_sig_source_x_0.set_sampling_freq(self.if_rate)

    def get_f_offset(self):
        return self.f_offset

    def set_f_offset(self, f_offset):
        self.f_offset = f_offset
        Qt.QMetaObject.invokeMethod(self._f_offset_line_edit, "setText", Qt.Q_ARG("QString", eng_notation.num_to_str(self.f_offset)))
        self.analog_sig_source_x_0.set_frequency(self.f_offset)


def main(top_block_cls=demod_dslwp_gmsk_b1_250bps_0r5_coherent, options=None):

    from distutils.version import StrictVersion
    if StrictVersion(Qt.qVersion()) >= StrictVersion("4.5.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()
    tb.start()
    tb.show()

    def quitting():
        tb.stop()
        tb.wait()
    qapp.connect(qapp, Qt.SIGNAL("aboutToQuit()"), quitting)
    qapp.exec_()


if __name__ == '__main__':
    main()
