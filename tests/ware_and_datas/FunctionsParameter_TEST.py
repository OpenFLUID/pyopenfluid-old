#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_FunctionsParameter(PyOpenFLUIDTest):

  def mainTest(self):
    """Test of functions parameters functions."""
    self.assertEquals(self.loadAllInputDataset(ArgList), 1)

    FunID = "examples.primitives.unitsA.up"
    ParamName = "gmult"

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

if __name__ == "__main__":
  ArgList = skipArgFromLC()
  unittest.main()
