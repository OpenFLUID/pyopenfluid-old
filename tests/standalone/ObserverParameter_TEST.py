#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_ObserverParameter(PyOpenFLUIDTest):

    def runTest(self):
        """Test of observer parameters functions."""
        IDParam = "export.test.fake"
        ParamName = "format.c1.header"

        self.openfluid.addObserver(IDParam)
        CheckVal = self.openfluid.getObserverParam(IDParam, ParamName)
        self.assertIsNone(CheckVal)

        Val = "colsname"
        self.openfluid.setObserverParam(IDParam, ParamName, Val)
        CheckVal = self.openfluid.getObserverParam(IDParam, ParamName)
        self.assertTrue(isinstance(CheckVal, str))

        self.assertIsNone(self.openfluid.getObserverParam("bidon", ParamName))
        self.assertIsNone(self.openfluid.getObserverParam(IDParam, "bidon"))

        NvVal = "testmade_" + Val
        self.openfluid.setObserverParam(IDParam, ParamName, NvVal)
        CheckVal = self.openfluid.getObserverParam(IDParam, ParamName)
        self.assertTrue(isinstance(CheckVal, str))
        self.assertNotEquals(CheckVal, Val)
        self.assertEquals(CheckVal, NvVal)


if __name__ == "__main__":
  unittest.main()
