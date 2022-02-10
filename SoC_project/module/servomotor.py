from migen import *
from migen.genlib.cdc import MultiReg
from litex.soc.interconnect.csr import *
from litex.soc.interconnect.csr_eventmanager import *

# Modulo de Servomotor
class servomotor(Module, AutoCSR):
    def __init__(self, servo):
        self.clk = ClockSignal() # Reloj

        # Registros
        self.posicion = CSRStorage(2)

        # Conexiones del Dispositivo
        self.servo = servo

        self.specials += Instance("servomotor",
            i_clk = self.clk,
            i_posicion = self.posicion.storage,
            o_servo = self.servo)