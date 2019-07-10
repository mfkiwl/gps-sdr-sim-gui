#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Top Block
# Generated: Fri Oct  5 14:43:16 2018
##################################################


from gnuradio import analog
from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import filter
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser


class top_block(gr.top_block):

    def __init__(self):
        gr.top_block.__init__(self, "Top Block")

        ##################################################
        # Blocks
        ##################################################
        self.rational_resampler_xxx_0 = filter.rational_resampler_ccc(
                interpolation=2600000,
                decimation=2600000,
                taps=None,
                fractional_bw=None,
        )
        self.blocks_multiply_const_vxx_1 = blocks.multiply_const_vcc((0.000000000000000000000000000000000000000000000001, ))
        self.blocks_file_source_0 = blocks.file_source(gr.sizeof_gr_complex*1, '/home/sasha/Desktop/MAN/gps-sdr-sim/gpssim.bin', False)
        self.blocks_file_sink_0 = blocks.file_sink(gr.sizeof_gr_complex*1, '/media/sasha/UUI/123.bin', False)
        self.blocks_file_sink_0.set_unbuffered(False)
        self.blocks_add_xx_0 = blocks.add_vcc(1)
        self.analog_noise_source_x_0 = analog.noise_source_c(analog.GR_GAUSSIAN, 1, 0)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_noise_source_x_0, 0), (self.rational_resampler_xxx_0, 0))
        self.connect((self.blocks_add_xx_0, 0), (self.blocks_file_sink_0, 0))
        self.connect((self.blocks_file_source_0, 0), (self.blocks_add_xx_0, 0))
        self.connect((self.blocks_multiply_const_vxx_1, 0), (self.blocks_add_xx_0, 1))
        self.connect((self.rational_resampler_xxx_0, 0), (self.blocks_multiply_const_vxx_1, 0))


def main(top_block_cls=top_block, options=None):

    tb = top_block_cls()
    tb.start()
    try:
        raw_input('Press Enter to quit: ')
    except EOFError:
        pass
    tb.stop()
    tb.wait()


if __name__ == '__main__':
    main()
