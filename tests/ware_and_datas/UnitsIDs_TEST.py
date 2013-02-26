#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_UnitsIDs(PyOpenFLUIDTest):

  def mainTest(self):
    """Test of units IDs functions."""
    self.assertTrue(isinstance(self.openfluid.getUnitsIDs("UnitClass"), list))

if __name__ == "__main__":
  unittest.main()
