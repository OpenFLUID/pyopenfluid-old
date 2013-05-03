#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_Simulators(PyOpenFLUIDTest):

    def runTest(self):
        """Test of functions functions."""

        # test of removeSimulator/addSimulator
        FuncID = "tests.primitives.use"
        ParamName = "longparam"
        ParamValue = "12568"

        self.assertRaises(TypeError, self.openfluid.addSimulator, 9)
        self.openfluid.addSimulator(FuncID)

        self.openfluid.setSimulatorParam(FuncID, ParamName, ParamValue)
        self.assertIsNotNone(self.openfluid.getSimulatorParam(FuncID, ParamName))

        self.openfluid.removeSimulator(FuncID)
        self.assertRaisesOrElse(StandardError, self.openfluid.getSimulatorParam,
                self.assertIsNone, argObj=(FuncID, ParamName) )

        # test of getSimulatorsInModel
        CheckList = self.openfluid.getSimulatorsInModel()
        self.assertTrue(isinstance(CheckList, (list, tuple)))
        self.assertEquals(len(CheckList), 0)
        self.openfluid.addSimulator(FuncID)
        CheckList = self.openfluid.getSimulatorsInModel()
        self.assertEquals(len(CheckList), 1)
        self.assertItemsEqual(CheckList, [FuncID])

        # test of clearModel
        self.openfluid.clearModel()
        self.assertEquals(len(self.openfluid.getSimulatorsInModel()), 0)

        ListIDParam = ["export.test.fake1", "export.test.fake2",
            "export.test.fake3", "export.test.fake4"]
        for IDParam in ListIDParam:
            self.openfluid.addSimulator(IDParam)

        self.assertItemsEqual(ListIDParam, self.openfluid.getSimulatorsInModel())
        self.openfluid.clearModel()
        self.assertEquals(len(self.openfluid.getSimulatorsInModel()), 0)

if __name__ == "__main__":
    unittest.main()
