#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_ExtraFunctionsPaths(PyOpenFLUIDTest):

    def runTest(self):
        """Test of extra functions paths functions."""
        self.openfluid.resetExtraFunctionsPaths()
        Val = self.openfluid.getExtraFunctionsPaths()
        self.assertTrue(isinstance(Val, list))
        self.assertEquals(len(Val), 0)

        Path1 = "/bidon/chemin1"
        self.openfluid.addExtraFunctionsPaths(Path1)
        Val = self.openfluid.getExtraFunctionsPaths()
        self.assertTrue(isinstance(Val, list))
        self.assertEquals(Val, [Path1])

        Path2 = "/chemin2"
        Path3 = "/debut/chemin3"
        self.openfluid.addExtraFunctionsPaths(":".join([Path2, Path3]))
        ListA, ListB = self.openfluid.getExtraFunctionsPaths(), [Path1, Path2, Path3]
        self.assertTrue(isinstance(ListA, list))
        ListA.sort(); ListB.sort()
        self.assertEquals(ListA, ListB)

        self.openfluid.resetExtraFunctionsPaths()
        Val = self.openfluid.getExtraFunctionsPaths()
        self.assertTrue(isinstance(Val, list))
        self.assertEquals(Val, [])

if __name__ == "__main__":
  unittest.main()
