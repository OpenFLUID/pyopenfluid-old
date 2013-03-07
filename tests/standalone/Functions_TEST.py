#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_Functions(PyOpenFLUIDTest):

    def runTest(self):
        """Test of functions functions."""

        # test of removeFunction/addFunction
        FunID = "tests.primitives.use"
        ParamName = "longparam"
        ParamValue = "12568"

        self.openfluid.addFunction(FunID)

        self.openfluid.setFunctionParam(FunID, ParamName, ParamValue)
        self.assertIsNotNone(self.openfluid.getFunctionParam(FunID, ParamName))

        self.openfluid.removeFunction(FunID)
        self.assertIsNone(self.openfluid.getFunctionParam(FunID, ParamName))

        # test of getFunctions
        CheckList = self.openfluid.getFunctions()
        self.assertTrue(isinstance(CheckList, (list, tuple)))
        self.assertEquals(len(CheckList), 0)
        self.openfluid.addFunction(FunID)
        CheckList = self.openfluid.getFunctions()
        self.assertEquals(len(CheckList), 1)
        self.assertItemsEqual(CheckList, [FunID])

        # test of clearModel
        ListFunID = ["tests.primitives.fake1", "tests.primitives.fake2",
            "tests.primitives.fake3", "tests.primitives.fake4"]
        for FunID in ListFunID:
            self.openfluid.addFunction(FunID)
            self.openfluid.setFunctionParam(FunID, ParamName, ParamValue)
            self.assertIsNotNone(self.openfluid.getFunctionParam(FunID, ParamName))

        self.openfluid.clearModel()

        for FunID in ListFunID:
            self.assertIsNone(self.openfluid.getFunctionParam(FunID, ParamName))

if __name__ == "__main__":
  unittest.main()
