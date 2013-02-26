#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_ExtraFunctionsPaths(PyOpenFLUIDTest):

  def mainTest(self):
    """Test of extra functions paths functions."""
    self.openfluid.resetExtraFunctionsPaths()
    self.assertEquals(len(self.openfluid.getExtraFunctionsPaths()), 0)

    Path1 = "/bidon/chemin1"
    self.openfluid.addExtraFunctionsPaths(Path1)
    self.assertEquals(self.openfluid.getExtraFunctionsPaths(), [Path1])

    Path2 = "/chemin2"
    Path3 = "/debut/chemin3"
    self.openfluid.addExtraFunctionsPaths(":".join([Path2, Path3]))
    ListA, ListB = self.openfluid.getExtraFunctionsPaths(), [Path1, Path2, Path3]
    ListA.sort(); ListB.sort()
    self.assertEquals(ListA, ListB)

    self.openfluid.resetExtraFunctionsPaths()
    self.assertEquals(self.openfluid.getExtraFunctionsPaths(), [])

if __name__ == "__main__":
  unittest.main()
