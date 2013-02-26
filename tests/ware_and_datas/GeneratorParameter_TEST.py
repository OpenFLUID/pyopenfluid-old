#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_GeneratorParameter(PyOpenFLUIDTest):

  def mainTest(self):
    """Test of generator parameters functions."""
    UnitClass = "SU"
    VarName = "var.flux"
    ParamName = "fixedvalue"
    ParamValue = "12.3"
    self.openfluid.setGeneratorParam(UnitClass, VarName, ParamName, ParamValue)
    self.assertEquals(self.openfluid.getGeneratorParam(
                                                UnitClass,
                                                VarName,
                                                ParamName),
                      ParamValue)


if __name__ == "__main__":
  unittest.main()
