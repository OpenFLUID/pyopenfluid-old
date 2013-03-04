#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_RunSimulation(PyOpenFLUIDTest):

    def runTest(self):
        """Test of project functions."""
        self.assertEquals(len(ArgList), 1)
        Path = ArgList[0]

        self.checkDirectory(Path)
        Res = self.openfluid.runProject(Path)

        self.assertTrue(isinstance(Res, bool))
        self.assertTrue(Res)

if __name__ == "__main__":
  ArgList = skipArgFromLC()
  unittest.main()
