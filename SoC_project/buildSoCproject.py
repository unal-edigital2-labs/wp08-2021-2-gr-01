#!/usr/bin/env python3

#from operator import imod
#from turtle import distance
from migen import *
from migen.genlib.io import CRG
from migen.genlib.cdc import MultiReg

import nexys4ddr as tarjeta

from litex.soc.integration.soc_core import *
from litex.soc.integration.builder import *
from litex.soc.interconnect.csr import *

from litex.soc.cores import gpio
from module import rgbled
from module import sevensegment
from module import vgacontroller

from module import movimiento
from module import servomotor
from module import ultrasonido
from module import infrarojo
#from module import camara

# BaseSoC
class BaseSoC(SoCCore):
	def __init__(self):
		platform = tarjeta.Platform()

		# add source verilog
		platform.add_source("module/verilog/movimiento/movimiento.v")
		platform.add_source("module/verilog/servomotor/servomotor.v")
		platform.add_source("module/verilog/ultrasonido/ultrasonido.v")
		platform.add_source("module/verilog/ultrasonido/divFreq.v")
		platform.add_source("module/verilog/infrarojo/infrarojo.v")
#		platform.add_source("module/verilog/camara/camara.v")
#		platform.add_source("module/verilog/camara/Analyzer.v")
#		platform.add_source("module/verilog/camara/cam_read.v")
#		platform.add_source("module/verilog/camara/buffer_ram_dp.v")
#		platform.add_source("module/verilog/camara/clk24_25_nexys4.v")

		# SoC with CPU
		SoCCore.__init__(self, platform,
 			cpu_type = "picorv32",
			clk_freq = 100e6,
			integrated_rom_size = 0x8000,
			integrated_main_ram_size = 16*1024)

		# Clock Reset Generation
		self.submodules.crg = CRG(platform.request("clk"), ~platform.request("cpu_reset"))

		# Leds
		SoCCore.add_csr(self,"leds")
		user_leds = Cat(*[platform.request("led", i) for i in range(10)])
		self.submodules.leds = gpio.GPIOOut(user_leds)
		
		# Switchs
		SoCCore.add_csr(self,"switchs")
		user_switchs = Cat(*[platform.request("sw", i) for i in range(8)])
		self.submodules.switchs = gpio.GPIOIn(user_switchs)
		
		# Buttons
		SoCCore.add_csr(self,"buttons")
		user_buttons = Cat(*[platform.request("btn%c" %c) for c in ['c','r','l']])
		self.submodules.buttons = gpio.GPIOIn(user_buttons)
		
		# 7segments Display
		SoCCore.add_csr(self,"display")
		display_segments = Cat(*[platform.request("display_segment", i) for i in range(8)])
		display_digits = Cat(*[platform.request("display_digit", i) for i in range(8)])
		self.submodules.display = sevensegment.SevenSegment(display_segments, display_digits)

		# RGB leds
		SoCCore.add_csr(self,"ledRGB_1")
		self.submodules.ledRGB_1 = rgbled.RGBLed(platform.request("ledRGB",1))
		SoCCore.add_csr(self,"ledRGB_2")
		self.submodules.ledRGB_2 = rgbled.RGBLed(platform.request("ledRGB",2))
		
		# VGA
		SoCCore.add_csr(self,"vga_cntrl")
		vga_red = Cat(*[platform.request("vga_red", i) for i in range(4)])
		vga_green = Cat(*[platform.request("vga_green", i) for i in range(4)])
		vga_blue = Cat(*[platform.request("vga_blue", i) for i in range(4)])
		self.submodules.vga_cntrl = vgacontroller.VGAcontroller(platform.request("hsync"),platform.request("vsync"), vga_red, vga_green, vga_blue)

		# Movimiento
		SoCCore.add_csr(self,"movimiento_cntrl")
		right = Cat(*[platform.request("right", i) for i in range(2)])
		left = Cat(*[platform.request("left", i) for i in range(2)])
		self.submodules.movimiento_cntrl = movimiento.movimiento(right, left)

		# Servomotor
		SoCCore.add_csr(self,"servomotor_cntrl")
		self.submodules.servomotor_cntrl = servomotor.servomotor(platform.request("servo"))

		# Ultrasonido
		SoCCore.add_csr(self,"ultrasonido_cntrl")
		self.submodules.ultrasonido_cntrl = ultrasonido.ultrasonido(platform.request("echo"), platform.request("trig"))

		# Infrarojo
		SoCCore.add_csr(self,"infrarojo_cntrl")
		self.submodules.infrarojo_cntrl = infrarojo.infrarojo(platform.request("iL"), platform.request("iLC"), platform.request("iC"), platform.request("iRC"), platform.request("iR"))

		#camara
#		SoCCore.add_csr(self,"camara_cntrl")
#		CAM_px_data = Cat(*[platform.request("CAM_px_data", i) for i in range(8)])		
#		self.submodules.camara_cntrl = camara.camara(platform.request("CAM_pclk"), platform.request("CAM_href"), platform.request("CAM_vsync"), CAM_px_data, platform.request("CAM_xclk"))
		


# Build --------------------------------------------------------------------------------------------
if __name__ == "__main__":
	builder = Builder(BaseSoC(),csr_csv="Soc_MemoryMap.csv")
	builder.build()
