#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_BeginPeriodDate(PyOpenFLUIDTest):

  def mainTest(self):
    """Test of begin period dates functions."""
    Date = "2012-03-04 13-04-13"

    self.openfluid.setPeriodBeginDate(Date)
    self.assertEquals(self.openfluid.getPeriodBeginDate(), Date)

    self.openfluid.setPeriodBeginDate("fail date")
    self.assertEquals(self.openfluid.getPeriodBeginDate(), Date)

if __name__ == "__main__":
  unittest.main()
