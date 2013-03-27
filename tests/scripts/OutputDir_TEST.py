#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_OutputDir(PyOpenFLUIDTest):

    def runTest(self):
        """Test of result functions."""

        # tests of setCurrentOutputDir
        self.assertRaises(TypeError, self.openfluid.setCurrentOutputDir, 65)
        self.assertRaises(TypeError, self.openfluid.setCurrentOutputDir, None)

        # tests of setCurrentOutputDir/getCurrentOutputDir
        Path = "/path/fake"
        self.openfluid.setCurrentOutputDir(Path)
        self.assertEquals(self.openfluid.getCurrentOutputDir(), Path)

        self.assertRaises(TypeError, self.openfluid.setCurrentOutputDir, 3)
        self.assertEquals(self.openfluid.getCurrentOutputDir(), Path)

if __name__ == "__main__":
    unittest.main()
