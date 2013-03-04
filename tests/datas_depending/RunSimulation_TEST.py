#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_RunSimulation(PyOpenFLUIDTest):

    def runTest(self):
        """Test of project functions."""
        self.assertEquals(len(ArgList), 3)
        map(ArgList, self.checkDirectory)
        Path = ArgList[0]

        ObjPyOF = self.loadInputDataset(Path)
        ObjPyOF.addExtraFunctionsPaths(ArgList[1])
        ObjPyOF.addExtraObserversPaths(ArgList[2])

        Res = ObjPyOF.runSimulation()

        self.assertTrue(isinstance(Res, bool))
        self.assertTrue(Res)

        # verification dossier sortie
        self.checkSimulationOutputPath(ObjPyOF.getCurrentOutputDir())

if __name__ == "__main__":
  ArgList = skipArgFromCL()
  unittest.main()
