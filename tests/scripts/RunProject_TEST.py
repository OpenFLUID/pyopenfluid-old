#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_RunProject(PyOpenFLUIDTest):

    def runTest(self):
        """Test of project functions."""
        PPath = ArgList.get("project", None)
        self.assertIsNotNone(PPath)

        # test of runSimulation
        self.openfluid.runProject(PPath)

if __name__ == "__main__":
    ArgList = skipArgFromCL()
    unittest.main()
