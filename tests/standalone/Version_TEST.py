#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_Version(PyOpenFLUIDTest):

    def runTest(self):
        """Test of version functions."""
        self.assertIsNotNone(self.openfluid.getVersion())
        self.assertGreaterEqual(self.openfluid.getVersion(), 3)

if __name__ == "__main__":
    unittest.main()
