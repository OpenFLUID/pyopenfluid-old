#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_Result(PyOpenFLUIDTest):

    def mainTest(self):
        """Test of result functions."""
        UnitClass = "RS"
        UnitID = 18
        Suffix = "full"
        self.assertIsNotNone(self.openfluid.loadResult(UnitClass, UnitID, Suffix))
        self.assertIsNotNone(self.openfluid.loadResultFile("imposssible path/"))

if __name__ == "__main__":
  unittest.main()
