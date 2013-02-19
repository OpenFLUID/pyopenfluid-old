#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_ModelGlobalParameter(PyOpenFLUIDTest):

  def mainTest(self):
    """Test of model global parameters functions."""
    ParamName = "gvalue"
    ParamValue = "37.2"
    self.openfluid.setModelGlobalParam(ParamName, ParamValue)
    self.assertEquals(self.openfluid.getModelGlobalParam(ParamName), ParamValue)

if __name__ == "__main__":
  unittest.main()
