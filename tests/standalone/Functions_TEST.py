#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_Functions(PyOpenFLUIDTest):

    def runTest(self):
        """Test of functions functions."""
        # first part - test of removeFunction/addFunction
        FunID = "tests.primitives.use"
        ParamName = "longparam"
        ParamValue = "12568"

        self.openfluid.addFunction(FunID)

        self.openfluid.setFunctionParam(FunID, ParamName, ParamValue)
        self.assertIsNotNone(self.openfluid.getFunctionParam(FunID, ParamName))

        self.openfluid.removeFunction(FunID)
        self.assertIsNone(self.openfluid.getFunctionParam(FunID, ParamName))

        # second part - test of clearModel
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
