#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_RunProject(PyOpenFLUIDTest):

    def runTest(self):
        """Test of project functions."""
        self.assertEquals(len(ArgList), 3)
        [self.checkDirectory(p) for p in ArgList]
        Path = ArgList[0]

        self.openfluid.addExtraFunctionsPaths(ArgList[1])
        self.openfluid.addExtraObserversPaths(ArgList[2])

        OClass = self.openfluid.runProject(Path)

        self.assertTrue(isinstance(OClass, PyOpenFLUID.PyOpenFLUID))
        self.assertNotEquals(OClass, self.openfluid)

        # verification dossier sortie
        self.checkSimulationOutputPath(OClass.getCurrentOutputDir())

if __name__ == "__main__":
  ArgList = skipArgFromCL()
  unittest.main()
