#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_RunSimulation(PyOpenFLUIDTest):

    def runTest(self):
        """Test of project functions."""
        self.preparePyOpenFLUIDClass(ArgList, "output", "dataset",
            optional=("project","funpath", "obspath"))

        Res = self.openfluid.runSimulation()

        self.assertTrue(isinstance(Res, bool))
        self.assertTrue(Res)

        # verification dossier sortie
        self.checkSimulationOutputPath(self.openfluid.getCurrentOutputDir())

if __name__ == "__main__":
    ArgList = skipArgFromCL()
    unittest.main()
