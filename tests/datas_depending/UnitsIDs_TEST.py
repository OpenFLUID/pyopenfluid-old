#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_UnitsIDs(PyOpenFLUIDTest):

    def runTest(self):
        """Test of units IDs functions."""
        self.assertEquals(self.loadAllInputDataset(ArgList), 1)

        # test of unitsA
        ListID = self.openfluid.getUnitsIDs("TestUnits")
        self.assertTrue(isinstance(ListID, list))

        ListTest = range(1, 13)
        ListID.sort(); ListTest.sort()
        self.assertEquals(ListID, ListTest)

if __name__ == "__main__":
  ArgList = skipArgFromCL()
  unittest.main()
