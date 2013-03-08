#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_UnitsParentsChildren(PyOpenFLUIDTest):

    def runTest(self):
        """Test of parents and children units functions."""
        UnitClass = "TestClass"
        ProcessOrder = 1

        # 0-,
        # 1-'-2
        #     |-5,
        # 3-4-'  |-7
        # 6------'
        #              0  1  2  3  4  5  6   7
        UnitLinksTo = (2, 2, 5, 4, 5, 7, 7, None)

        # creation of the model
        # tests of addUnitChild
        [self.openfluid.addUnit(UnitClass, i, ProcessOrder)
            for i in range(len(UnitLinksTo))]
        for UnitFrom, UnitTo in enumerate(UnitLinksTo):
            if not UnitTo is None:
                self.openfluid.addUnitChild(UnitClass, UnitFrom, UnitClass, UnitTo)

        # tests of getUnitsChildren
        CheckList = self.openfluid.getUnitsChildren(UnitClass, 0)
        self.assertTrue(isinstance(CheckList, (tuple, list)))
        self.assertTrue(isinstance(CheckList[0], (tuple, list)))
        self.assertTrue(isinstance(CheckList[0][0], str))
        self.assertTrue(isinstance(CheckList[0][1], int))

        UnitLinksFrom = [[] for i in range(len(UnitLinksTo))]
        for UnitFrom, UnitTo in enumerate(UnitLinksTo):
            CheckList = self.openfluid.getUnitsChildren(UnitClass, UnitFrom)
            if not UnitTo is None:
                self.assertItemsEqual(CheckList, [(UnitClass, UnitTo)])
                UnitLinksFrom[UnitTo].append(UnitFrom)
            else:
                self.assertItemsEqual(CheckList, [])

        # tests of getUnitsParents
        CheckList = self.openfluid.getUnitsParents(UnitClass, 7)
        self.assertTrue(isinstance(CheckList, (tuple, list)))
        self.assertTrue(isinstance(CheckList[0], (tuple, list)))
        self.assertTrue(isinstance(CheckList[0][0], str))
        self.assertTrue(isinstance(CheckList[0][1], int))

        for UnitTo, UnitsFrom in enumerate(UnitLinksFrom):
            CheckList = self.openfluid.getUnitsParents(UnitClass, UnitTo)
            self.assertItemsEqual(UnitsFrom, [b for a,b in CheckList])

        # tests of removeUnitChild
        # testing on 5->7, 2->5, 4->5
        CheckList = self.openfluid.getUnitsChildren(UnitClass, 5)
        self.assertEquals(CheckList[0][1], 7)
        CheckList = self.openfluid.getUnitsParents(UnitClass, 5)
        self.assertItemsEqual([b for a,b in CheckList], [2, 4])

        self.openfluid.removeUnitChild(UnitClass, 5, UnitClass, 7)
        self.openfluid.removeUnitChild(UnitClass, 4, UnitClass, 5)
        self.openfluid.removeUnitChild(UnitClass, 2, UnitClass, 5)

        CheckList = self.openfluid.getUnitsChildren(UnitClass, 5)
        self.assertEquals(len(CheckList), 0)
        CheckList = self.openfluid.getUnitsParents(UnitClass, 5)
        self.assertEquals(len(CheckList), 0)


if __name__ == "__main__":
  unittest.main()
