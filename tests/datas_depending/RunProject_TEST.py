#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_RunProject(PyOpenFLUIDTest):

    def runTest(self):
        """Test of project functions."""
        self.assertEquals(len(ArgList), 1)
        Path = ArgList[0]

        self.checkDirectory(Path)
        Res = self.openfluid.runProject(Path)

        self.assertTrue(isinstance(Res, PyOpenFLUID))

        # verification dossier sortie
        self.checkSimulationOutputPath(Res.getCurrentOutputDir())

if __name__ == "__main__":
  ArgList = skipArgFromLC()
  unittest.main()
