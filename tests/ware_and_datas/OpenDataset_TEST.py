#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_OpenDataSet(PyOpenFLUIDTest):

    def mainTest(self):
        """Test of simulation functions."""
        self.assertEquals(self.loadAllInputDataset(ArgList), 2)

if __name__ == "__main__":
  ArgList = skipArgFromLC()
  unittest.main()
