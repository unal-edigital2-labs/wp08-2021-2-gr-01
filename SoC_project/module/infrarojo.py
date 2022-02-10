from migen import *
from migen.genlib.cdc import MultiReg
from litex.soc.interconnect.csr import *
from litex.soc.interconnect.csr_eventmanager import *

class infrarojo(Module, AutoCSR):
    def __init__(self, ising):
        # Conexiones del Dispositivo
        self.ising = ising

        # Registros
        self.osing = CSRStatus(1)

        self.specials += Instance("infrarojo",
            i_ising = self.ising,
            o_osing = self.osing.status)
