#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_OpenDataSet(PyOpenFLUIDTest):

  def mainTest(self):
    """Test of simulation functions."""
    Res = self.openfluid.openDataset("Path")
    self.assertIsNotNone(Res)
    self.assertTrue(isinstance(Res, PyOpenFLUID.PyOpenFLUID))
    self.assertNotEquals(Res, self.openfluid)

if __name__ == "__main__":
  unittest.main()
