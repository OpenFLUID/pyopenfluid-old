#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_DefaultDeltaT(PyOpenFLUIDTest):

  def mainTest(self):
    """Test of default delta t attribute functions."""
    DeltaT = 23

    self.openfluid.setDefaultDeltaT(DeltaT)
    self.assertEquals(self.openfluid.getDefaultDeltaT(), DeltaT)

    self.openfluid.setDefaultDeltaT(-90)
    self.assertNotEquals(self.openfluid.getDefaultDeltaT(), DeltaT)

if __name__ == "__main__":
  unittest.main()
