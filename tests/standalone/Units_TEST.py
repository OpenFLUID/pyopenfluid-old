#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_Units(PyOpenFLUIDTest):

    def runTest(self):
        """Test of units functions."""

        Units = (("TestClass", 5, 1), ("FakeClass", 3, 2))
        UnitsClasses = map((lambda (a,b,c): a), Units)
        UnitsIDs = map((lambda (a,b,c): b), Units)

        self.assertEquals(len(self.openfluid.getUnitsClasses()), 0)

        # tests of addUnit
        map((lambda (a,b,c): self.openfluid.addUnit(a,b,c)), Units)

        ListVal = self.openfluid.getUnitsClasses()
        self.assertItemsEqual(ListVal, UnitsClasses)

        ListVal = self.openfluid.getUnitsIDs(Units[0][0])
        self.assertItemsEqual(ListVal, [Units[0][1]])

        # tests of setUnitProcessOrder/getUnitProcessOrder
        POVal = self.openfluid.getUnitProcessOrder(Units[0][0], Units[0][1])
        self.assertTrue(isinstance(POVal, int))
        self.assertEquals(POVal, Units[0][2])
        NvPOVal = POVal + 2
        self.openfluid.setUnitProcessOrder(Units[0][0], Units[0][1], NvPOVal)
        CheckPOVal = self.openfluid.getUnitProcessOrder(Units[0][0], Units[0][1])
        self.assertNotEquals(CheckPOVal, POVal)
        self.assertEquals(CheckPOVal, NvPOVal)

        # tests of removeUnit
        (ExUC, ExID, ExPO), Units = Units[0], Units[1:]
        UnitsClasses = map((lambda (a,b,c): a), Units)
        UnitsIDs = map((lambda (a,b,c): b), Units)

        self.openfluid.removeUnit(ExUC, ExID)

        ListVal = self.openfluid.getUnitsClasses()
        self.assertItemsEqual(ListVal, UnitsClasses)

        ListVal = self.openfluid.getUnitsIDs(Units[0][0])
        self.assertItemsEqual(ListVal, [Units[0][1]])

        ListVal = self.openfluid.getUnitsIDs("TestClass")
        self.assertItemsEqual(ListVal, [])

        # tests of clearAllUnits
        self.openfluid.clearAllUnits(Units[0][0])
        self.assertEquals(len(self.openfluid.getUnitsIDs("TestClass")), 0)
        self.assertEquals(len(self.openfluid.getUnitsClasses()), 0)

if __name__ == "__main__":
    unittest.main()
