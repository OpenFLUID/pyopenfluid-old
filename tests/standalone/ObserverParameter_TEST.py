#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_ObserverParameter(PyOpenFLUIDTest):

    def runTest(self):
        """Test of observer parameters functions."""
        IDParam = "export.test.fake"
        ParamName = "format.c1.header"

        # first part - test of getObserverParam/setObserverParam
        self.openfluid.addObserver(IDParam)
        CheckVal = self.openfluid.getObserverParam(IDParam, ParamName)
        self.assertIsNone(CheckVal)

        Val = "colsname"
        self.openfluid.setObserverParam(IDParam, ParamName, Val)
        CheckVal = self.openfluid.getObserverParam(IDParam, ParamName)
        self.assertTrue(isinstance(CheckVal, str))

        self.assertRaisesOrElse(ValueError, self.openfluid.getObserverParam,
                self.assertIsNone, argObj=("bidon", ParamName) )
        self.assertRaisesOrElse(ValueError, self.openfluid.getObserverParam,
                self.assertIsNone, argObj=(IDParam, "bidon") )

        NvVal = "testmade_" + Val
        self.openfluid.setObserverParam(IDParam, ParamName, NvVal)
        CheckVal = self.openfluid.getObserverParam(IDParam, ParamName)
        self.assertTrue(isinstance(CheckVal, str))
        self.assertNotEquals(CheckVal, Val)
        self.assertEquals(CheckVal, NvVal)

        # test of getObserverParams
        CheckList = self.openfluid.getObserverParams(IDParam)
        self.assertTrue(isinstance(CheckList, (list, tuple)))
        self.assertEquals(len(CheckList), 1)
        self.assertItemsEqual(CheckList, [ParamName])
        self.openfluid.setObserverParam(IDParam, ParamName+"_muchlonguer", "o")
        CheckList = self.openfluid.getObserverParams(IDParam)
        self.assertEquals(len(CheckList), 2)
        self.assertItemsEqual(CheckList, [ParamName, ParamName+"_muchlonguer"])

        # second part - test of removeObserverParam
        self.openfluid.setObserverParam(IDParam, ParamName, Val)
        self.assertEquals(Val, self.openfluid.getObserverParam(IDParam, ParamName))
        self.openfluid.removeObserverParam(IDParam, ParamName)
        self.assertRaisesOrElse(ValueError, self.openfluid.getObserverParam,
                self.assertIsNone, argObj=(IDParam, ParamName) )

        # test of type's parameters
        self.assertRaises(TypeError, self.openfluid.setObserverParam,
                IDParam, ParamName, 9)
        self.assertRaises(TypeError, self.openfluid.setObserverParam,
                IDParam, 9, Val)
        self.assertRaises(TypeError, self.openfluid.setObserverParam,
                9, ParamName, Val)
        self.assertRaises(TypeError, self.openfluid.getObserverParam,
                IDParam, 9)
        self.assertRaises(TypeError, self.openfluid.getObserverParam,
                9, ParamName)
        self.assertRaises(TypeError, self.openfluid.removeObserverParam,
                IDParam, 9)
        self.assertRaises(TypeError, self.openfluid.removeObserverParam,
                9, ParamName)


if __name__ == "__main__":
  unittest.main()
