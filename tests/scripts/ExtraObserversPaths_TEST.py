#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_ExtraObserversPaths(PyOpenFLUIDTest):

    def runTest(self):
        """Test of extra observers paths functions."""

        # tests on addExtraObserversPaths
        self.assertRaises(TypeError, self.openfluid.addExtraObserversPaths, 65)
        self.assertRaises(TypeError, self.openfluid.addExtraObserversPaths, None)

        # tests on resetExtraObserversPaths/getExtraObserversPaths
        self.openfluid.resetExtraObserversPaths()
        Val = self.openfluid.getExtraObserversPaths()
        self.assertTrue(isinstance(Val, list))
        self.assertEquals(len(Val), 0)

        # tests on addExtraObserversPaths/getExtraObserversPaths
        Path1 = "/bidon/chemin1"
        self.openfluid.addExtraObserversPaths(Path1)
        Val = self.openfluid.getExtraObserversPaths()
        self.assertTrue(isinstance(Val, list))
        self.assertItemsEqual(Val, [Path1])

        Path2 = "/chemin2"
        Path3 = "/debut/chemin3"
        self.openfluid.addExtraObserversPaths(":".join([Path2, Path3]))
        ListA, ListB = self.openfluid.getExtraObserversPaths(), [Path1, Path2, Path3]
        self.assertItemsEqual(ListA, ListB)

        # tests on resetExtraObserversPaths/getExtraObserversPaths
        self.openfluid.resetExtraObserversPaths()
        Val = self.openfluid.getExtraObserversPaths()
        self.assertTrue(isinstance(Val, list))
        self.assertEquals(Val, [])


if __name__ == "__main__":
    unittest.main()
