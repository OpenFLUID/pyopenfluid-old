#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_SimulatorsParameter(PyOpenFLUIDTest):

    def runTest(self):
        """Test of simulators parameters functions."""

        SimuID = "tests.primitives.use"
        ParamName = "longparam"

        # test of getSimulatorParam/setSimulatorParam
        self.openfluid.addSimulator(SimuID)
        CheckVal = self.openfluid.getSimulatorParam(SimuID, ParamName)
        self.assertIsNone(CheckVal)

        Val = "colsname"
        self.openfluid.setSimulatorParam(SimuID, ParamName, Val)
        CheckVal = self.openfluid.getSimulatorParam(SimuID, ParamName)
        self.assertTrue(isinstance(CheckVal, str))

        self.assertRaisesOrElse(StandardError, self.openfluid.getSimulatorParam,
                self.assertIsNone, argObj=("bidon", ParamName) )
        self.assertRaisesOrElse(StandardError, self.openfluid.getSimulatorParam,
                self.assertIsNone, argObj=(SimuID, "bidon") )

        NvVal = "testmade_" + Val
        self.openfluid.setSimulatorParam(SimuID, ParamName, NvVal)
        CheckVal = self.openfluid.getSimulatorParam(SimuID, ParamName)
        self.assertTrue(isinstance(CheckVal, str))
        self.assertNotEquals(CheckVal, Val)
        self.assertEquals(CheckVal, NvVal)

        # test of getSimulatorParams
        CheckList = self.openfluid.getSimulatorParams(SimuID)
        self.assertTrue(isinstance(CheckList, (list, tuple)))
        self.assertEquals(len(CheckList), 1)
        self.assertItemsEqual(CheckList, [ParamName])
        self.openfluid.setSimulatorParam(SimuID, ParamName+"_muchlonguer", "o")
        CheckList = self.openfluid.getSimulatorParams(SimuID)
        self.assertEquals(len(CheckList), 2)
        self.assertItemsEqual(CheckList, [ParamName, ParamName+"_muchlonguer"])

        # test of removeSimulatorParam
        self.openfluid.setSimulatorParam(SimuID, ParamName, Val)
        self.assertEquals(Val, self.openfluid.getSimulatorParam(SimuID, ParamName))
        self.openfluid.removeSimulatorParam(SimuID, ParamName)
        self.assertRaisesOrElse(StandardError, self.openfluid.getSimulatorParam,
                self.assertIsNone, argObj=(SimuID, ParamName) )

        # test of type's parameters
        self.assertRaises(TypeError, self.openfluid.setSimulatorParam,
                SimuID, ParamName, 9)
        self.assertRaises(TypeError, self.openfluid.setSimulatorParam,
                SimuID, 9, Val)
        self.assertRaises(TypeError, self.openfluid.setSimulatorParam,
                9, ParamName, Val)
        self.assertRaises(TypeError, self.openfluid.getSimulatorParam,
                SimuID, 9)
        self.assertRaises(TypeError, self.openfluid.getSimulatorParam,
                9, ParamName)
        self.assertRaises(TypeError, self.openfluid.removeSimulatorParam,
                SimuID, 9)
        self.assertRaises(TypeError, self.openfluid.removeSimulatorParam,
                9, ParamName)


if __name__ == "__main__":
    unittest.main()
