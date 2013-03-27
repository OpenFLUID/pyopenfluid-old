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

        self.assertRaises(TypeError, self.openfluid.addObserver, 9)
        self.openfluid.addObserver(IDParam)

        self.openfluid.setObserverParam(IDParam, ParamName, ParamValue)
        self.assertIsNotNone(self.openfluid.getObserverParam(IDParam, ParamName))

        self.openfluid.removeObserver(IDParam)
        self.assertRaisesOrElse(StandardError, self.openfluid.getObserverParam,
                self.assertIsNone, argObj=(IDParam, ParamName) )

        # test of getObserversInMonitoring
        CheckList = self.openfluid.getObserversInMonitoring()
        self.assertTrue(isinstance(CheckList, (list, tuple)))
        self.assertEquals(len(CheckList), 0)
        self.openfluid.addObserver(IDParam)
        CheckList = self.openfluid.getObserversInMonitoring()
        self.assertEquals(len(CheckList), 1)
        self.assertItemsEqual(CheckList, [IDParam])

        # test of clearMonitoring
        self.openfluid.clearMonitoring()
        self.assertEquals(len(self.openfluid.getObserversInMonitoring()), 0)

        ListIDParam = ["export.test.fake1", "export.test.fake2",
            "export.test.fake3", "export.test.fake4"]
        for IDParam in ListIDParam:
            self.openfluid.addObserver(IDParam)

        self.assertItemsEqual(ListIDParam, self.openfluid.getObserversInMonitoring())
        self.openfluid.clearMonitoring()
        self.assertEquals(len(self.openfluid.getObserversInMonitoring()), 0)


if __name__ == "__main__":
    unittest.main()
