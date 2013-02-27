#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *
import tempfile

class PyOpenFLUIDTest_Simulation(PyOpenFLUIDTest):

    def mainTest(self):
        """Test of simulation functions."""

        self.openfluid.runSimulation()


#    self.openfluid.runSimulation()

if __name__ == "__main__":
  unittest.main()
