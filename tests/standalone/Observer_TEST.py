#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_Observer(PyOpenFLUIDTest):

    def runTest(self):
        """Test of observer functions."""

        # first part - test of removeObserver/addObserver
        IDParam = "export.test.fake"
        ParamName = "format.c1.header"
        ParamValue = "test"

        self.openfluid.addObserver(IDParam)

        self.openfluid.setObserverParam(IDParam, ParamName, ParamValue)
        self.assertIsNotNone(self.openfluid.getObserverParam(IDParam, ParamName))

        self.openfluid.removeObserver(IDParam)
        self.assertIsNone(self.openfluid.getObserverParam(IDParam, ParamName))

        # second part - test of clearMonitoring
        ListIDParam = ["export.test.fake1", "export.test.fake2",
            "export.test.fake3", "export.test.fake4"]
        for IDParam in ListIDParam:
            self.openfluid.addObserver(IDParam)
            self.openfluid.setObserverParam(IDParam, ParamName, ParamValue)
            self.assertIsNotNone(self.openfluid.getObserverParam(IDParam, ParamName))

        self.openfluid.clearMonitoring()

        for IDParam in ListIDParam:
            self.assertIsNone(self.openfluid.getObserverParam(IDParam, ParamName))


if __name__ == "__main__":
  unittest.main()
