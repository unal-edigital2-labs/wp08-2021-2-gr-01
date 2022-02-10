from migen import *
from migen.genlib.cdc import MultiReg
from litex.soc.interconnect.csr import *
from litex.soc.interconnect.csr_eventmanager import *

# Modulo de Camara
class camara(Module,AutoCSR):
    def __init__(self, pclk, href, vsync, px_data, xclk):
        self.clk = ClockSignal() # Reloj  
        self.rst = ResetSignal() # Reset

        # Registros
        self.init = CSRStorage(1)
        self.error = CSRStatus(1)
        self.done= CSRStatus(1)
        self.res = CSRStatus(3)

        # Conexiones del Dispositivo
        self.pclk = pclk
        self.vsync= vsync
        self.href= href
        self.px_data = px_data
        self.xclk = xclk
        
        self.specials += Instance("camara",
            i_clk = self.clk,
            i_rst = self.rst,
            i_init = self.init.storage,
            o_error = self.error.status,
            o_done =self.done.status,
            o_res = self.res.status,
            i_CAM_pclk = self.pclk,
            i_CAM_vsync = self.vsync,
            i_CAM_href = self.href,
            i_CAM_px_data = self.px_data,
            o_CAM_xclk = self.xclk,
        )

