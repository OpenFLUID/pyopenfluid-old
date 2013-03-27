#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_UnitsParentsChildren(PyOpenFLUIDTest):

    def runTest(self):
        """Test of parents and children units functions."""

        # subtest of type's parameters
        self.assertRaises(TypeError, self.openfluid.addUnit, "testclass", "couc", 0)
        self.assertRaises(TypeError, self.openfluid.addUnit, "testclass", 0, "inc")
        self.assertRaises(TypeError, self.openfluid.addUnit, 0, 0, 0)
        self.assertRaises(TypeError, self.openfluid.addParentChildConnection, "a", 0, 0, 0)
        self.assertRaises(TypeError, self.openfluid.addParentChildConnection, 0, "a", 0, 0)
        self.assertRaises(TypeError, self.openfluid.addParentChildConnection, 0, 0, "a", 0)
        self.assertRaises(TypeError, self.openfluid.addParentChildConnection, 0, 0, 0, "a")

        #
        UnitClass = "TestClass"
        ProcessOrder = 1

        # 0-,
        # 1-'->2
        #      |->5,
        # 3->4-'   |->7
        # 6------ -'
        #      Parents    0  1  2  3  4  5  6   7
        UnitLinksChild = (2, 2, 5, 4, 5, 7, 7, None)

        # creation of the model
        # tests of addParentChildConnection
        [self.openfluid.addUnit(UnitClass, i, ProcessOrder)
            for i in range(len(UnitLinksChild))]
        for UnitParent, UnitChild in enumerate(UnitLinksChild):
            if not UnitChild is None:
                self.openfluid.addParentChildConnection(UnitClass, UnitParent, UnitClass, UnitChild)

        # subtest of value parameters
        self.assertRaises(StandardError, self.openfluid.addParentChildConnection, UnitClass, 20, UnitClass, 0)
        self.assertRaises(StandardError, self.openfluid.addParentChildConnection, UnitClass, 0, UnitClass, 20)

        # tests of getUnitChildren
        CheckList = self.openfluid.getUnitChildren(UnitClass, 0)
        self.assertTrue(isinstance(CheckList, (tuple, list)))
        self.assertTrue(isinstance(CheckList[0], (tuple, list)))
        self.assertTrue(isinstance(CheckList[0][0], str))
        self.assertTrue(isinstance(CheckList[0][1], int))

        UnitLinksParent = [[] for i in range(len(UnitLinksChild))]
        for UnitParent, UnitChild in enumerate(UnitLinksChild):
            CheckList = self.openfluid.getUnitChildren(UnitClass, UnitParent)
            if not UnitChild is None:
                self.assertItemsEqual(CheckList, [(UnitClass, UnitChild)])
                UnitLinksParent[UnitChild].append(UnitParent)
            else:
                self.assertItemsEqual(CheckList, [])

        # tests of getUnitParents
        CheckList = self.openfluid.getUnitParents(UnitClass, 7)
        self.assertTrue(isinstance(CheckList, (tuple, list)))
        self.assertTrue(isinstance(CheckList[0], (tuple, list)))
        self.assertTrue(isinstance(CheckList[0][0], str))
        self.assertTrue(isinstance(CheckList[0][1], int))

        for UnitChild, UnitsParent in enumerate(UnitLinksParent):
            CheckList = self.openfluid.getUnitParents(UnitClass, UnitChild)
            self.assertItemsEqual(UnitsParent, [b for a,b in CheckList])

        # tests of removeParentChildConnection
        # testing on 5->7, 2->5, 4->5
        CheckList = self.openfluid.getUnitChildren(UnitClass, 5)
        self.assertItemsEqual([b for a,b in CheckList], [7])
        CheckList = self.openfluid.getUnitParents(UnitClass, 5)
        self.assertItemsEqual([b for a,b in CheckList], [2, 4])

        self.openfluid.removeParentChildConnection(UnitClass, 5, UnitClass, 7)
        self.openfluid.removeParentChildConnection(UnitClass, 4, UnitClass, 5)
        self.openfluid.removeParentChildConnection(UnitClass, 2, UnitClass, 5)

        CheckList = self.openfluid.getUnitChildren(UnitClass, 5)
        self.assertEquals(len(CheckList), 0)
        CheckList = self.openfluid.getUnitParents(UnitClass, 5)
        self.assertEquals(len(CheckList), 0)


if __name__ == "__main__":
    unittest.main()
