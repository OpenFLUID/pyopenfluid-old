#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *
import tempfile

class PyOpenFLUIDTest_Simulation(PyOpenFLUIDTest):

    def mainTest(self):
        """Test of simulation functions."""

        FakeOutputFile = tempfile.NamedTemporaryFile(mode="rw+b", bufsize=20, suffix="_pyopenfluid_test", delete=True)
        print "Dir:", FakeOutputFile.name
        sys.stdout = FakeOutputFile
        sys.stderr = FakeOutputFile
        self.openfluid.printSimulationInfo()
        self.assertGreater(len(FakeOutputFile.read(10)), 0)
        sys.stdout = sys.__stdout__
        sys.stderr = sys.__stderr__
        FakeOutputFile.close() # destroyed

#    self.openfluid.runSimulation()

if __name__ == "__main__":
  unittest.main()
