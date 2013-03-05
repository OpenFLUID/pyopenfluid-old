#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_FunctionsParameter(PyOpenFLUIDTest):

    def runTest(self):
        """Test of functions parameters functions."""
        self.assertEquals(self.loadAllInputDataset(ArgList), 1)

        FunID = "tests.primitives.use"
        ParamName = "longparam"

        self.assertIsNone(self.openfluid.getFunctionParam(FunID, "bidon"))
        self.assertIsNone(self.openfluid.getFunctionParam("bidon", ParamName))

        Val = self.openfluid.getFunctionParam(FunID, ParamName)
        self.assertTrue(isinstance(Val, str))
        self.checkInt(Val)

        NvVal = str(int(Val) + 4)
        self.openfluid.setFunctionParam(FunID, ParamName, NvVal)
        CheckVal = self.openfluid.getFunctionParam(FunID, ParamName)
        self.assertTrue(isinstance(CheckVal, str))
        self.checkInt(CheckVal)
        self.assertNotEquals(CheckVal, Val)
        self.assertEquals(CheckVal, NvVal)

        self.openfluid.removeFunctionParam(FunID, ParamName)
        CheckVal = self.openfluid.getFunctionParam(FunID, ParamName)
        self.assertIsNone(CheckVal)

if __name__ == "__main__":
  ArgList = skipArgFromCL()
  unittest.main()
