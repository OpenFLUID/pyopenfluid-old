#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_Observer(PyOpenFLUIDTest):

    def runTest(self):
        """Test of observer functions."""

        # test of removeObserver/addObserver
        IDParam = "export.test.fake"
        ParamName = "format.c1.header"
        ParamValue = "test"

        self.openfluid.addObserver(IDParam)

        self.openfluid.setObserverParam(IDParam, ParamName, ParamValue)
        self.assertIsNotNone(self.openfluid.getObserverParam(IDParam, ParamName))

        self.openfluid.removeObserver(IDParam)
        self.assertIsNone(self.openfluid.getObserverParam(IDParam, ParamName))

        # test of getObservers
        CheckList = self.openfluid.getObservers()
        self.assertTrue(isinstance(CheckList, (list, tuple)))
        self.assertEquals(len(CheckList), 0)
        self.openfluid.addObserver(IDParam)
        CheckList = self.openfluid.getObservers()
        self.assertEquals(len(CheckList), 1)
        self.assertItemsEqual(CheckList, [IDParam])

        # test of clearMonitoring
        self.openfluid.clearMonitoring()
        self.assertEquals(len(self.openfluid.getObservers()), 0)

        ListIDParam = ["export.test.fake1", "export.test.fake2",
            "export.test.fake3", "export.test.fake4"]
        for IDParam in ListIDParam:
            self.openfluid.addObserver(IDParam)

        self.assertItemsEqual(ListIDParam, self.openfluid.getObservers())
        self.openfluid.clearMonitoring()
        self.assertEquals(len(self.openfluid.getObservers()), 0)


if __name__ == "__main__":
  unittest.main()
