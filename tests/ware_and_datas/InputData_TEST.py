#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_InputData(PyOpenFLUIDTest):

  def mainTest(self):
    """Test of input datas functions."""
    UnitClass = "SU"
    IDataName = "area"
    IDataValue = "13.9"
    self.openfluid.createInputData(UnitClass, IDataName, IDataValue)

    UnitID = 9
    self.openfluid.setInputData(UnitClass, UnitID, IDataName, IDataValue)
    self.assertEquals(self.openfluid.getInputData(UnitClass, UnitID, IDataName),
                      IDataValue)

if __name__ == "__main__":
  unittest.main()
