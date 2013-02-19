#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_ExtraFunctionsPaths(PyOpenFLUIDTest):

  def mainTest(self):
    """Test of extra functions paths functions."""
    self.resetExtraFunctionsPaths()
    self.assertEquals(self.openfluid.getExtraFunctionsPaths(), [])

    Path1 = "/home"
    self.openfluid.addExtraFunctionsPaths(Path1)
    self.assertEquals(self.openfluid.getExtraFunctionsPaths(), [Path1])

    Path2 = "/usr"
    self.openfluid.addExtraFunctionsPaths(Path2)
    self.assertEquals(self.openfluid.getExtraFunctionsPaths(), [Path1, Path2])

    self.resetExtraFunctionsPaths()
    self.assertEquals(self.openfluid.getExtraFunctionsPaths(), [])

if __name__ == "__main__":
  unittest.main()
