#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_RunSimulation(PyOpenFLUIDTest):

    def runTest(self):
        """Test of project functions."""
        PPath = ArgList.get("project", None)
        self.assertIsNotNone(PPath)

        # test of runSimulation
        self.openfluid.openProject(PPath)
        Res = self.openfluid.runSimulation()
        self.assertTrue(isinstance(Res, bool))


if __name__ == "__main__":
    ArgList = skipArgFromCL()
    unittest.main()
