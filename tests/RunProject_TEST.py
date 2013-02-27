#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_RunProject(PyOpenFLUIDTest):

    def mainTest(self):
        """Test of project functions."""
        self.assertIsNotNone(self.openfluid.runProject("Path"))

if __name__ == "__main__":
  unittest.main()
