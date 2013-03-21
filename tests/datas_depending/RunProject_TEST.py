#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_RunProject(PyOpenFLUIDTest):

    def runTest(self):
        """Test of project functions."""
        Path = ArgList.get("project", None)
        self.assertIsNotNone(Path)
        self.preparePyOpenFLUIDClass(ArgList, optional=("funpath", "obspath"))

        self.openfluid.runProject(Path)

        # verification dossier sortie
        self.checkSimulationOutputPath(OClass.getCurrentOutputDir())

if __name__ == "__main__":
    ArgList = skipArgFromCL()
    unittest.main()
