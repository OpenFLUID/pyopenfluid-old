#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_EndPeriodDate(PyOpenFLUIDTest):

  def mainTest(self):
    """Test of end period dates functions."""
    Date = "2012-03-04 15:04:13"

    self.openfluid.setPeriodEndDate(Date)
    self.assertEquals(self.openfluid.getPeriodEndDate(), Date)

    try:
        self.openfluid.setPeriodEndDate("fail date")
    except:
        pass
    self.assertEquals(self.openfluid.getPeriodEndDate(), Date)

if __name__ == "__main__":
  unittest.main()
