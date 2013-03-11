#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_BeginPeriodDate(PyOpenFLUIDTest):

    def runTest(self):
        """Test of begin period dates functions."""

        # dataset => true date format
        ListPassDate = ["2012-03-04 13:04:13"]
        ListPassDate.append( "2012-12-31 23:59:59" )
        ListPassDate.append( "2012-02-29 12:00:00" )

        # tests of setPeriodBeginDate/getPeriodBeginDate
        for PassDate in ListPassDate:
            self.openfluid.setPeriodBeginDate(PassDate)
            CheckDate = self.openfluid.getPeriodBeginDate()
            self.assertTrue(isinstance(CheckDate, str))
            self.assertEquals(CheckDate, PassDate)

        # dataset => wrong date format
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

        # tests of setPeriodBeginDate/getPeriodBeginDate
        for FailDate in ListFailDate:
            self.openfluid.setPeriodBeginDate(FailDate)
            self.assertEquals(self.openfluid.getPeriodBeginDate(), PassDate)


if __name__ == "__main__":
    unittest.main()
