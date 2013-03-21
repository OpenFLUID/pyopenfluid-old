#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_UnitsIDs(PyOpenFLUIDTest):

    def runTest(self):
        """Test of units IDs functions."""
        self.preparePyOpenFLUIDClass(ArgList, "dataset",
            optional=["output", "project"])

        # test of unitsA
        ListID = self.openfluid.getUnitsIDs("unitsB")
        self.assertTrue(isinstance(ListID, list))

        ListTest = [1, 11, 2, 7, 3]
        print "ListID:", ListID
        self.assertItemsEqual(ListID, ListTest)

if __name__ == "__main__":
    ArgList = skipArgFromCL()
    unittest.main()
