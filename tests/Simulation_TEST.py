#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *
import tempfile

class PyOpenFLUIDTest_Simulation(PyOpenFLUIDTest):

    def mainTest(self):
        """Test of simulation functions."""

        # creation of a temporary output file and redirecting standard outputs
        FakeOutputFile = tempfile.TemporaryFile(mode="w+b", bufsize=-1)
        sys.stdout = FakeOutputFile
        sys.stderr = FakeOutputFile

        # calling methods
        try:
            self.openfluid.printSimulationInfo()
        except Exception as exc:
            print sys.__stderr__.write("Exception: " + exc.message)

        # moving file pointer to the start of the file
        FakeOutputFile.seek(0,0)
        self.assertGreater(len(FakeOutputFile.read(10)), 0, "function 'printSimulationInfo' didn't print anything")

        # removing temporary output file
        sys.stdout = sys.__stdout__
        sys.stderr = sys.__stderr__
        FakeOutputFile.close() # destroyed


#    self.openfluid.runSimulation()

if __name__ == "__main__":
  unittest.main()
