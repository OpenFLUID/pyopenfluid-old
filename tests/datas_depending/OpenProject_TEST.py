#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_OpenProject(PyOpenFLUIDTest):

    def runTest(self):
        """Test of project functions."""
        self.assertEquals(len(ArgList), 1)
        Path = ArgList[0]

        self.checkDirectory(Path)
        OClass = self.openfluid.openProject(Path)

        self.assertTrue(isinstance(OClass, PyOpenFLUID.PyOpenFLUID))
        self.assertNotEquals(OClass, self.openfluid)

if __name__ == "__main__":
    ArgList = skipArgFromCL()
    unittest.main()
