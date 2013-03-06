#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_FunctionsParameter(PyOpenFLUIDTest):

    def runTest(self):
        """Test of functions parameters functions."""
        FunID = "tests.primitives.use"
        ParamName = "longparam"

        self.openfluid.addFunction(FunID)
        CheckVal = self.openfluid.getFunctionParam(FunID, ParamName)
        self.assertIsNone(CheckVal)

        Val = "colsname"
        self.openfluid.setFunctionParam(FunID, ParamName, Val)
        CheckVal = self.openfluid.getFunctionParam(FunID, ParamName)
        self.assertTrue(isinstance(CheckVal, str))

        self.assertIsNone(self.openfluid.getFunctionParam("bidon", ParamName))
        self.assertIsNone(self.openfluid.getFunctionParam(FunID, "bidon"))

        NvVal = "testmade_" + Val
        self.openfluid.setFunctionParam(FunID, ParamName, NvVal)
        CheckVal = self.openfluid.getFunctionParam(FunID, ParamName)
        self.assertTrue(isinstance(CheckVal, str))
        self.assertNotEquals(CheckVal, Val)
        self.assertEquals(CheckVal, NvVal)

if __name__ == "__main__":
  unittest.main()
