#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_ExtraObserversPaths(PyOpenFLUIDTest):

    def mainTest(self):
        """Test of extra observers paths functions."""
        self.openfluid.resetExtraObserversPaths()
        self.assertEquals(len(self.openfluid.getExtraObserversPaths()), 0)

        Path1 = "/bidon/chemin1"
        self.openfluid.addExtraObserversPaths(Path1)
        self.assertEquals(self.openfluid.getExtraObserversPaths(), [Path1])

        Path2 = "/chemin2"
        Path3 = "/debut/chemin3"
        self.openfluid.addExtraObserversPaths(":".join([Path2, Path3]))
        ListA, ListB = self.openfluid.getExtraObserversPaths(), [Path1, Path2, Path3]
        ListA.sort(); ListB.sort()
        self.assertEquals(ListA, ListB)

        self.openfluid.resetExtraObserversPaths()
        self.assertEquals(self.openfluid.getExtraObserversPaths(), [])

if __name__ == "__main__":
  unittest.main()
