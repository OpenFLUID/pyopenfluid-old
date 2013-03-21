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

        # tests of clearAllUnits by unitclass
        self.openfluid.clearAllUnits(Units[0][0])
        self.assertEquals(len(self.openfluid.getUnitsIDs("TestClass")), 0)
        self.assertEquals(len(self.openfluid.getUnitsClasses()), 0)

        # tests of clearAllUnits
        self.openfluid.addUnit("SU",10,1)
        self.openfluid.addUnit("OTH",11,1)
        self.openfluid.addUnit("FK",12,1)
        self.openfluid.addParentChildConnection("SU",10,"OTH",11)
        self.openfluid.addFromToConnection("OTH",11,"FK",12)
        self.assertEquals(self.openfluid.getUnitsIDs("SU"), [10])
        self.assertEquals(self.openfluid.getUnitsIDs("OTH"), [11])
        self.assertEquals(self.openfluid.getUnitsIDs("FK"), [12])
        self.assertEquals(self.openfluid.getUnitTos("OTH",11), [("FK", 12)])
        self.assertEquals(self.openfluid.getUnitChildren("SU",10), [("OTH", 11)])
        self.assertEquals(self.openfluid.getUnitParents("OTH",11), [("SU", 10)])
        self.assertItemsEqual(self.openfluid.getUnitsClasses(), ["SU", "OTH", "FK"])
        self.openfluid.clearAllUnits()
        self.assertEquals(len(self.openfluid.getUnitsIDs("SU")), 0)
        self.assertEquals(len(self.openfluid.getUnitsIDs("OTH")), 0)
        self.assertEquals(len(self.openfluid.getUnitsIDs("FK")), 0)
        self.assertEquals(len(self.openfluid.getUnitTos("OTH",11)), 0)
        self.assertEquals(len(self.openfluid.getUnitChildren("SU",10)), 0)
        self.assertEquals(len(self.openfluid.getUnitParents("OTH",11)), 0)
        self.assertEquals(len(self.openfluid.getUnitsClasses()), 0)

if __name__ == "__main__":
    unittest.main()
