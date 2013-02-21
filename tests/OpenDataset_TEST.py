#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_OpenDataSet(PyOpenFLUIDTest):

  def mainTest(self):
    """Test of simulation functions."""
    self.assertIsNotNone(self.openfluid.openDataset("Path"))

if __name__ == "__main__":
  unittest.main()
