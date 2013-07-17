#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_ExtraSimulatorsPaths(PyOpenFLUIDTest):

    def runTest(self):
        """Test of extra simulators paths functions."""

        # tests on addExtraSimulatorsPaths
        self.assertRaises(TypeError, self.openfluid.addExtraSimulatorsPaths, 65)
        self.assertRaises(TypeError, self.openfluid.addExtraSimulatorsPaths, None)

        # tests on resetExtraSimulatorsPaths/getExtraSimulatorsPaths
        self.openfluid.resetExtraSimulatorsPaths()
        Val = self.openfluid.getExtraSimulatorsPaths()
        self.assertTrue(isinstance(Val, list))
        self.assertEquals(len(Val), 0)

        # tests on addExtraSimulatorsPaths/getExtraSimulatorsPaths
        Path1 = "/bidon/chemin1"
        self.openfluid.addExtraSimulatorsPaths(Path1)
        Val = self.openfluid.getExtraSimulatorsPaths()
        self.assertTrue(isinstance(Val, list))
        self.assertItemsEqual(Val, [Path1])

        Path2 = "/chemin2"
        Path3 = "/debut/chemin3"
        self.openfluid.addExtraSimulatorsPaths(":".join([Path2, Path3]))
        ListA, ListB = self.openfluid.getExtraSimulatorsPaths(), [Path1, Path2, Path3]
        self.assertItemsEqual(ListA, ListB)

        # tests on resetExtraSimulatorsPaths/getExtraSimulatorsPaths
        self.openfluid.resetExtraSimulatorsPaths()
        Val = self.openfluid.getExtraSimulatorsPaths()
        self.assertTrue(isinstance(Val, list))
        self.assertEquals(Val, [])


if __name__ == "__main__":
    unittest.main()
