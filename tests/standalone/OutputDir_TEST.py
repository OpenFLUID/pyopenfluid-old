#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_OutputDir(PyOpenFLUIDTest):

  def mainTest(self):
    """Test of result functions."""
    Path = "/path/fake"
    self.openfluid.setCurrentOutputDir(Path)
    self.assertEquals(self.openfluid.getCurrentOutputDir(), Path)

    try:
        self.openfluid.setCurrentOutputDir(3)
    except:
        pass
    else:
        self.assertTrue(False, "missed raised exception")

if __name__ == "__main__":
  unittest.main()
