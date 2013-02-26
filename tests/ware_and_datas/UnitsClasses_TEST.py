#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_UnitsClasses(PyOpenFLUIDTest):

  def mainTest(self):
    """Test of units classes functions."""
    self.assertTrue(isinstance(self.openfluid.getUnitsClasses(), list))

if __name__ == "__main__":
  unittest.main()
