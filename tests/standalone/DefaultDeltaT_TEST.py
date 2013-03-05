#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_DefaultDeltaT(PyOpenFLUIDTest):

    def runTest(self):
        """Test of default delta t attribute functions."""
        DeltaT = 23

        self.openfluid.setDefaultDeltaT(DeltaT)
        Val = self.openfluid.getDefaultDeltaT()
        self.assertTrue(isinstance(Val, int))
        self.assertEquals(Val, DeltaT)

        self.assertRaises(ValueError, self.openfluid.setDefaultDeltaT, -90)
        self.assertRaises(TypeError, self.openfluid.setDefaultDeltaT, "bidon")
        Val = self.openfluid.getDefaultDeltaT()
        self.assertTrue(isinstance(Val, int))
        self.assertEquals(Val, DeltaT)

if __name__ == "__main__":
  unittest.main()
