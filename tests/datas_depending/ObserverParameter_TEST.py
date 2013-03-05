#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_ObserverParameter(PyOpenFLUIDTest):

    def runTest(self):
        """Test of observer parameters functions."""
        self.assertEquals(self.loadAllInputDataset(ArgList), 1)

        IDParam = "export.vars.files.csv"
        ParamName = "format.f2.header"

        Val = self.openfluid.getObserverParam(IDParam, ParamName)
        self.assertTrue(isinstance(Val, str))

        self.assertIsNone(self.openfluid.getObserverParam("bidon", ParamName))
        self.assertIsNone(self.openfluid.getObserverParam(IDParam, "bidon"))

        NvVal = "testmade_" + Val
        self.openfluid.setObserverParam(IDParam, ParamName, NvVal)
        CheckVal = self.openfluid.getObserverParam(IDParam, ParamName)
        self.assertTrue(isinstance(CheckVal, str))
        self.assertNotEquals(CheckVal, Val)
        self.assertEquals(CheckVal, NvVal)


if __name__ == "__main__":
  ArgList = skipArgFromCL()
  unittest.main()
