#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_UnitsClasses(PyOpenFLUIDTest):

    def runTest(self):
        """Test of units classes functions."""
        self.assertEquals(self.loadAllInputDataset(ArgList), 1)

        ListUC = self.openfluid.getUnitsClasses()
        self.assertTrue(isinstance(ListUC, list))

        ListTest = ['TestUnits', 'ParentTestUnits']

        self.assertItemsEqual(ListTest, ListUC)

if __name__ == "__main__":
    ArgList = skipArgFromCL()
    unittest.main()
