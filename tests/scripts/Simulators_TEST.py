#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_Simulators(PyOpenFLUIDTest):

    def runTest(self):
        """Test of simulators functions."""

        # test of removeSimulator/addSimulator
        SimID = "tests.primitives.use"
        ParamName = "longparam"
        ParamValue = "12568"

        self.assertRaises(TypeError, self.openfluid.addSimulator, 9)
        self.openfluid.addSimulator(SimID)

        self.openfluid.setSimulatorParam(SimID, ParamName, ParamValue)
        self.assertIsNotNone(self.openfluid.getSimulatorParam(SimID, ParamName))

        self.openfluid.removeSimulator(SimID)
        self.assertRaisesOrElse(StandardError, self.openfluid.getSimulatorParam,
                self.assertIsNone, argObj=(SimID, ParamName) )

        # test of getSimulatorsInModel
        CheckList = self.openfluid.getSimulatorsInModel()
        self.assertTrue(isinstance(CheckList, (list, tuple)))
        self.assertEquals(len(CheckList), 0)
        self.openfluid.addSimulator(SimID)
        CheckList = self.openfluid.getSimulatorsInModel()
        self.assertEquals(len(CheckList), 1)
        self.assertItemsEqual(CheckList, [SimID])

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
