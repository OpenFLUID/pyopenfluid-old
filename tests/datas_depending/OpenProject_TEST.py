#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_OpenProject(PyOpenFLUIDTest):

    def runTest(self):
        """Test of project functions."""
        Path = ArgList.get("project", None)
        self.assertIsNotNone(Path)

        self.checkDirectory(Path)
        OClass = self.openfluid.openProject(Path)

        self.assertTrue(isinstance(OClass, PyOpenFLUID.PyOpenFLUID))
        self.assertNotEquals(OClass, self.openfluid)

if __name__ == "__main__":
    ArgList = skipArgFromCL()
    unittest.main()
