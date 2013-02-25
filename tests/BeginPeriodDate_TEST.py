#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_BeginPeriodDate(PyOpenFLUIDTest):

  def mainTest(self):
    """Test of begin period dates functions."""

    # test true date format
    ListPassDateDate = ["2012-03-04 13:04:13"]
    ListPassDate.append( "2012-12-31 23:59:59" )
    ListPassDate.append( "2012-02-29 12:00:00" )

    for PassDate in ListPassDate:
        self.openfluid.setPeriodBeginDate(PassDate)
        self.assertEquals(self.openfluid.getPeriodBeginDate(), PassDate)

    # test wrong date format
    ListFailDate = ["fail date"]
    ListFailDate.append( "2012 03 04 13 04 13" )
    ListFailDate.append( "2012-03-04 13-04-13" )
    ListFailDate.append( "2012-03-04  13:04:13" )
    ListFailDate.append( "2012-03-04   13:04:13" )
    ListFailDate.append( " 2012-03-04 13:04:13" )
    ListFailDate.append( "2012-03-04  13:04:13 " )
    ListFailDate.append( "2012:03:04 13:04:13" )
    ListFailDate.append( "2012:03:04 13-04-13" )
    ListFailDate.append( "13:04:13 2012-03-04" )
    ListFailDate.append( "2012-03-04-13-04-13" )
    ListFailDate.append( "2012,03,04 13,04,13" )
    ListFailDate.append( "2012/03/04 13:04:13" )

    for FailDate in ListFailDate:
        try :
            self.openfluid.setPeriodBeginDate(FailDate)
        except:
            pass
        self.assertEquals(self.openfluid.getPeriodBeginDate(), PassDate)

if __name__ == "__main__":
  unittest.main()
