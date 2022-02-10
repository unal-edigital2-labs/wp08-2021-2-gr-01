from migen import *
from migen.genlib.cdc import MultiReg
from litex.soc.interconnect.csr import *
from litex.soc.interconnect.csr_eventmanager import *

class infrarojo(Module, AutoCSR):
    def __init__(self, iL, iLC, iC, iRC,iR):
        # Conexiones del Dispositivo
        self.iL = iL
        self.iLC = iLC
        self.iC = iC
        self.iRC = iRC
        self.iR = iR

        # Registros
        self.oL = CSRStatus(1)
        self.oLC = CSRStatus(1)
        self.oC = CSRStatus(1)
        self.oRC = CSRStatus(1)
        self.oR = CSRStatus(1)

        self.specials += Instance("infrarojo",
            i_iL = self.iL,
            i_iLC = self.iLC,
            i_iC = self.iC,
            i_iRC = self.iRC,
            i_iR = self.iR,

            o_oL = self.oL.status,
            o_oLC = self.oLC.status,
            o_oC = self.oC.status,
            o_oRC = self.oRC.status,
            o_oR = self.oR.status)
