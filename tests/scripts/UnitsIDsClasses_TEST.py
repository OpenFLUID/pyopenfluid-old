#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_UnitsIDsClasses(PyOpenFLUIDTest):

    def runTest(self):
        """Test of units ids and classes functions."""

        UNITS = [ ("unitA", (1,8,5,12,359)), ("unitB", (56,58,60)), ("unitC", ()) ]
        for UnitClass, UnitIDs in UNITS:
            for UnitID in UnitIDs:
              self.openfluid.addUnit(UnitClass, UnitID, 1)
        UNIT_CLASSES = [a for a,b in UNITS if len(b) > 0]

        # test of getUnitsClasses
        ListUC = self.openfluid.getUnitsClasses()
        self.assertTrue(isinstance(ListUC, list))
        self.assertItemsEqual(UNIT_CLASSES, ListUC)

        # test of getUnitsIDs
        for UnitClass, UnitIDs in UNITS:
            ListID = self.openfluid.getUnitsIDs(UnitClass)
            self.assertTrue(isinstance(ListID, list))
            self.assertItemsEqual(ListID, UnitIDs)

if __name__ == "__main__":
    unittest.main()
