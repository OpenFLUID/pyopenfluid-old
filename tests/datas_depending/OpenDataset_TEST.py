#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_OpenDataSet(PyOpenFLUIDTest):

    def runTest(self):
        """Test of simulation functions."""
        DSPath = ArgList.get("dataset", None)
        self.assertIsNotNone(DSPath)
        self.loadInputDataset(DSPath)

if __name__ == "__main__":
    ArgList = skipArgFromCL()
    unittest.main()
