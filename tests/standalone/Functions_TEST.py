#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_Functions(PyOpenFLUIDTest):

    def runTest(self):
        """Test of functions functions."""

        # test of removeFunction/addFunction
        FuncID = "tests.primitives.use"
        ParamName = "longparam"
        ParamValue = "12568"

        self.assertRaises(TypeError, self.openfluid.addFunction, 9)
        self.openfluid.addFunction(FuncID)

        self.openfluid.setFunctionParam(FuncID, ParamName, ParamValue)
        self.assertIsNotNone(self.openfluid.getFunctionParam(FuncID, ParamName))

        self.assertRaises(StandardError, self.openfluid.addFunction, FuncID)

        self.openfluid.removeFunction(FuncID)
        self.assertRaisesOrElse(ValueError, self.openfluid.getFunctionParam,
                self.assertIsNone, argObj=(FuncID, ParamName) )

        # test of getFunctions
        CheckList = self.openfluid.getFunctions()
        self.assertTrue(isinstance(CheckList, (list, tuple)))
        self.assertEquals(len(CheckList), 0)
        self.openfluid.addFunction(FuncID)
        CheckList = self.openfluid.getFunctions()
        self.assertEquals(len(CheckList), 1)
        self.assertItemsEqual(CheckList, [FuncID])

        # test of clearModel
        self.openfluid.clearModel()
        self.assertEquals(len(self.openfluid.getFunctions()), 0)

        ListIDParam = ["export.test.fake1", "export.test.fake2",
            "export.test.fake3", "export.test.fake4"]
        for IDParam in ListIDParam:
            self.openfluid.addFunction(IDParam)

        self.assertItemsEqual(ListIDParam, self.openfluid.getFunctions())
        self.openfluid.clearModel()
        self.assertEquals(len(self.openfluid.getFunctions()), 0)

if __name__ == "__main__":
    unittest.main()
