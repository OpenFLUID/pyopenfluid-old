#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_UnitsIDs(PyOpenFLUIDTest):

    def runTest(self):
        """Test of units IDs functions."""
        self.preparePyOpenFLUIDClass(ArgList, "output", "dataset",
            optional="project")

        # test of unitsA
        ListID = self.openfluid.getUnitsIDs("TestUnits")
        self.assertTrue(isinstance(ListID, list))

        ListTest = range(1, 13)
        self.assertItemsEqual(ListID, ListTest)

if __name__ == "__main__":
    ArgList = skipArgFromCL()
    unittest.main()
