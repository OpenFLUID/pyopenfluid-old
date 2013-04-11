#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_UnitsFromsTos(PyOpenFLUIDTest):

    def runTest(self):
        """Test of parents and children units functions."""

        # subtest of type's parameters
        self.assertRaises(TypeError, self.openfluid.addUnit, "testclass", "couc", 0)
        self.assertRaises(TypeError, self.openfluid.addUnit, "testclass", 0, "inc")
        self.assertRaises(TypeError, self.openfluid.addUnit, 0, 0, 0)
        self.assertRaises(TypeError, self.openfluid.addFromToConnection, "a", 0, 0, 0)
        self.assertRaises(TypeError, self.openfluid.addFromToConnection, 0, "a", 0, 0)
        self.assertRaises(TypeError, self.openfluid.addFromToConnection, 0, 0, "a", 0)
        self.assertRaises(TypeError, self.openfluid.addFromToConnection, 0, 0, 0, "a")

        #
        UnitClass = "TestClass"
        ProcessOrder = 1

        # 0-,
        # 1-'->2
        #      |->5,
        # 3->4-'   |->7
        # 6------ -'
        #      Froms    0  1  2  3  4  5  6   7
        UnitLinksTo = (2, 2, 5, 4, 5, 7, 7, None)

        # creation of the model
        # tests of addFromToConnection
        [self.openfluid.addUnit(UnitClass, i, ProcessOrder)
            for i in range(len(UnitLinksTo))]
        for UnitFrom, UnitTo in enumerate(UnitLinksTo):
            if not UnitTo is None:
                self.openfluid.addFromToConnection(UnitClass, UnitFrom, UnitClass, UnitTo)

        # subtest of value parameters
        self.assertRaises(StandardError, self.openfluid.addFromToConnection, UnitClass, 20, UnitClass, 0)
        self.assertRaises(StandardError, self.openfluid.addFromToConnection, UnitClass, 0, UnitClass, 20)

        # tests of getUnitTos
        CheckList = self.openfluid.getUnitTos(UnitClass, 0)
        self.assertTrue(isinstance(CheckList, (tuple, list)))
        self.assertTrue(isinstance(CheckList[0], (tuple, list)))
        self.assertTrue(isinstance(CheckList[0][0], str))
        self.assertTrue(isinstance(CheckList[0][1], int))

        UnitLinksFrom = [[] for i in range(len(UnitLinksTo))]
        for UnitFrom, UnitTo in enumerate(UnitLinksTo):
            CheckList = self.openfluid.getUnitTos(UnitClass, UnitFrom)
            if not UnitTo is None:
                self.assertItemsEqual(CheckList, [(UnitClass, UnitTo)])
                UnitLinksFrom[UnitTo].append(UnitFrom)
            else:
                self.assertItemsEqual(CheckList, [])

        # tests of getUnitFroms
        CheckList = self.openfluid.getUnitFroms(UnitClass, 7)
        self.assertTrue(isinstance(CheckList, (tuple, list)))
        self.assertTrue(isinstance(CheckList[0], (tuple, list)))
        self.assertTrue(isinstance(CheckList[0][0], str))
        self.assertTrue(isinstance(CheckList[0][1], int))

        for UnitTo, UnitsFrom in enumerate(UnitLinksFrom):
            CheckList = self.openfluid.getUnitFroms(UnitClass, UnitTo)
            self.assertItemsEqual(UnitsFrom, [b for a,b in CheckList])

        # tests of removeFromToConnection
        # testing on 5->7, 2->5, 4->5
        CheckList = self.openfluid.getUnitTos(UnitClass, 5)
        self.assertItemsEqual([b for a,b in CheckList], [7])
        CheckList = self.openfluid.getUnitFroms(UnitClass, 5)
        self.assertItemsEqual([b for a,b in CheckList], [2, 4])

        self.openfluid.removeFromToConnection(UnitClass, 5, UnitClass, 7)
        self.openfluid.removeFromToConnection(UnitClass, 4, UnitClass, 5)
        self.openfluid.removeFromToConnection(UnitClass, 2, UnitClass, 5)

        CheckList = self.openfluid.getUnitTos(UnitClass, 5)
        self.assertEquals(len(CheckList), 0)
        CheckList = self.openfluid.getUnitFroms(UnitClass, 5)
        self.assertEquals(len(CheckList), 0)


if __name__ == "__main__":
    unittest.main()
