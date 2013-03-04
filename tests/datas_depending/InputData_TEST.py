#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_InputData(PyOpenFLUIDTest):

    def runTest(self):
        """Test of input datas functions."""
        self.assertEquals(self.loadAllInputDataset(ArgList), 1)

        UnitClass = "TestUnits"
        UnitID = 3
        UnitName = "indataA"
        self.assertIsNone(self.openfluid.getInputData(UnitClass, UnitID, "bidon"))

        Val = self.openfluid.getInputData(UnitClass, UnitID, UnitName)
        self.assertTrue(isinstance(Val, str))
        self.checkFloat(Val)

        NvVal = str(float(Val) + 8.2)
        self.openfluid.setInputData(UnitClass, UnitID, UnitName, NvVal)
        CheckVal = self.openfluid.getInputData(UnitClass, UnitID, UnitName)
        self.assertTrue(isinstance(Val, str))
        self.checkFloat(CheckVal)
        self.assertNotEquals(CheckVal, Val)
        self.assertEquals(CheckVal, NvVal)


if __name__ == "__main__":
  ArgList = skipArgFromLC()
  unittest.main()
