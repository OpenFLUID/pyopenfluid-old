#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_OpenDataSet(PyOpenFLUIDTest):

    def runTest(self):
        """Test of simulation functions."""
        self.assertEquals(self.loadAllInputDataset(ArgList), len(ArgList))

if __name__ == "__main__":
    ArgList = skipArgFromCL()
    unittest.main()
