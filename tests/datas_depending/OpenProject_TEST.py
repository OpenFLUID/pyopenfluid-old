#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_OpenProject(PyOpenFLUIDTest):

    def runTest(self):
        """Test of project functions."""
        Path = ArgList.get("project", None)
        self.assertIsNotNone(Path)

        self.checkDirectory(Path)
        self.openfluid.openProject(Path)

if __name__ == "__main__":
    ArgList = skipArgFromCL()
    unittest.main()
