#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_OpenProject(PyOpenFLUIDTest):

    def mainTest(self):
        """Test of project functions."""
        self.assertEquals(len(ArgList), 1)
        OClass = self.loadProject(ArgList[0])

        self.assertIsNotNone(OClass)
        self.assertTrue(isinstance(OClass, PyOpenFLUID.PyOpenFLUID))
        self.assertNotEquals(OClass, self.openfluid)

if __name__ == "__main__":
  ArgList = skipArgFromLC()
  unittest.main()
