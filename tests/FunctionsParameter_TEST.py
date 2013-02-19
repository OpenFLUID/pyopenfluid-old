#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_FunctionsParameter(PyOpenFLUIDTest):

  def mainTest(self):
    """Test of functions parameters functions."""
    FunID = "my.function"
    ParamName = "coeff"
    ParamVal = "3"
    self.openfluid.setFunctionParam(FunID, ParamName, ParamVal) )
    self.assertEquals(self.openfluid.getFunctionsParam(FunID, ParamName),
                      ParamVal)

if __name__ == "__main__":
  unittest.main()
