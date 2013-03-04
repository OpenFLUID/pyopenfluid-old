#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_GeneratorParameter(PyOpenFLUIDTest):

    def runTest(self):
        """Test of generator parameters functions."""
        self.assertEquals(self.loadAllInputDataset(ArgList), 1)

        UnitClass = "TestUnits"
        VarName = "tests.fixed"
        ParamName = "fixedvalue"

        Val = self.openfluid.getGeneratorParam(UnitClass, VarName, ParamName)

        self.assertIsNone(self.openfluid.getGeneratorParam(UnitClass, VarName, "bidon"))
        self.assertIsNone(self.openfluid.getGeneratorParam(UnitClass, "bidon", ParamName))
        self.assertIsNone(self.openfluid.getGeneratorParam("bidon", VarName, ParamName))
        self.assertIsNone(self.openfluid.getGeneratorParam(UnitClass, "bidon", "bidon"))
        self.assertIsNone(self.openfluid.getGeneratorParam("bidon", "bidon", ParamName))
        self.assertIsNone(self.openfluid.getGeneratorParam("bidon", VarName, "bidon"))

        self.assertTrue(isinstance(Val, str))
        self.checkNumeric(Val)

        NvVal = str(float(Val) + 123.6)
        self.openfluid.setGeneratorParam(UnitClass, VarName, ParamName, NvVal)
        CheckVal = self.openfluid.getGeneratorParam(UnitClass, VarName, ParamName)
        self.assertTrue(isinstance(CheckVal, str))
        self.checkNumeric(CheckVal)
        self.assertNotEquals(CheckVal, Val)
        self.assertEquals(CheckVal, NvVal)


if __name__ == "__main__":
  ArgList = skipArgFromLC()
  unittest.main()
