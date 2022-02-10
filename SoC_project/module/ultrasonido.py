from migen import *
from migen.genlib.cdc import MultiReg
from litex.soc.interconnect.csr import *
from litex.soc.interconnect.csr_eventmanager import *

# Modulo de Ultrasonido
class ultrasonido(Module, AutoCSR):
    def __init__(self, echo, trig):
        self.clk = ClockSignal() # Reloj
        
        # Registros
        self.init = CSRStorage(1)
        self.distance = CSRStatus(9)
        self.done = CSRStatus(1)
        
        # Conexiones del Dispositivo
        self.echo = echo
        self.trig = trig

        self.specials += Instance("ultrasonido",
            i_clk = self.clk,
            i_init = self.init.storage,
            o_distance = self.distance.status,
            o_done = self.done.status,
            i_echo = self.echo,
            o_trig = self.trig)

