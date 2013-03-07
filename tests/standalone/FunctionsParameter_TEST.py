#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_FunctionsParameter(PyOpenFLUIDTest):

    def runTest(self):
        """Test of functions parameters functions."""

        FuncID = "tests.primitives.use"
        ParamName = "longparam"

        # test of getFunctionParam/setFunctionParam
        self.openfluid.addFunction(FuncID)
        CheckVal = self.openfluid.getFunctionParam(FuncID, ParamName)
        self.assertIsNone(CheckVal)

        Val = "colsname"
        self.openfluid.setFunctionParam(FuncID, ParamName, Val)
        CheckVal = self.openfluid.getFunctionParam(FuncID, ParamName)
        self.assertTrue(isinstance(CheckVal, str))

        self.assertIsNone(self.openfluid.getFunctionParam("bidon", ParamName))
        self.assertIsNone(self.openfluid.getFunctionParam(FuncID, "bidon"))

        NvVal = "testmade_" + Val
        self.openfluid.setFunctionParam(FuncID, ParamName, NvVal)
        CheckVal = self.openfluid.getFunctionParam(FuncID, ParamName)
        self.assertTrue(isinstance(CheckVal, str))
        self.assertNotEquals(CheckVal, Val)
        self.assertEquals(CheckVal, NvVal)

        # test of getFunctionParams
        CheckList = self.openfluid.getFunctionParams(FuncID)
        self.assertTrue(isinstance(CheckList, (list, tuple)))
        self.assertEquals(len(CheckList), 1)
        self.assertItemsEqual(CheckList, [ParamName])
        self.openfluid.setFunctionParam(FuncID, ParamName+"_muchlonguer", "o")
        CheckList = self.openfluid.getFunctionParams(FuncID)
        self.assertEquals(len(CheckList), 2)
        self.assertItemsEqual(CheckList, [ParamName, ParamName+"_muchlonguer"])

        # test of removeFunctionParam
        self.openfluid.setFunctionParam(FuncID, ParamName, Val)
        self.assertEquals(Val, self.openfluid.getFunctionParam(FuncID, ParamName))
        self.openfluid.removeFunctionParam(FuncID, ParamName)
        self.assertIsNone(self.openfluid.getFunctionParam(FuncID, ParamName))


if __name__ == "__main__":
  unittest.main()
