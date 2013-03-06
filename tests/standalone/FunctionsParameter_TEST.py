#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_FunctionsParameter(PyOpenFLUIDTest):

    def runTest(self):
        """Test of functions parameters functions."""
        FuncID = "tests.primitives.use"
        ParamName = "longparam"

        # first part - test of getFunctionParam/setFunctionParam
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

        # second part - test of removeFunctionParam
        self.openfluid.setFunctionParam(FuncID, ParamName, Val)
        self.assertEquals(Val, self.openfluid.getFunctionParam(FuncID, ParamName))
        self.openfluid.removeFunctionParam(FuncID, ParamName)
        self.assertIsNone(self.openfluid.getFunctionParam(FuncID, ParamName))


if __name__ == "__main__":
  unittest.main()
