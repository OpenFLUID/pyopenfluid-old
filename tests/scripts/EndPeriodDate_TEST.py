#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_EndPeriodDate(PyOpenFLUIDTest):

    def runTest(self):
        """Test of end period dates functions."""

        # dataset => true date format
        ListPassDate = ["2012-03-04 15:04:13"]
        ListPassDate.append( "2012-12-31 23:59:59" )
        ListPassDate.append( "2012-02-29 12:00:00" )

        # tests of setPeriodEndDate/getPeriodEndDate
        for PassDate in ListPassDate:
            self.openfluid.setPeriodEndDate(PassDate)
            CheckDate = self.openfluid.getPeriodEndDate()
            self.assertTrue(isinstance(CheckDate, str))
            self.assertEquals(CheckDate, PassDate)

        # dataset => wrong date format
        ListFailDate = ["fail date"]
        ListFailDate.append( "2012 03 04 15 04 13" )
        ListFailDate.append( "2012-03-04 15-04-13" )
        ListFailDate.append( "2012-03-04  15:04:13" )
        ListFailDate.append( "2012-03-04   15:04:13" )
        ListFailDate.append( " 2012-03-04 15:04:13" )
        ListFailDate.append( "2012-03-04  15:04:13 " )
        ListFailDate.append( "2012:03:04 15:04:13" )
        ListFailDate.append( "2012:03:04 15-04-13" )
        ListFailDate.append( "15:04:13 2012-03-04" )
        ListFailDate.append( "2012-03-04-15-04-13" )
        ListFailDate.append( "2012,03,04 15,04,13" )
        ListFailDate.append( "2012/03/04 15:04:13" )

        # tests of setPeriodEndDate/getPeriodEndDate
        for FailDate in ListFailDate:
            self.assertRaises(ValueError, self.openfluid.setPeriodEndDate, FailDate)


if __name__ == "__main__":
    unittest.main()
