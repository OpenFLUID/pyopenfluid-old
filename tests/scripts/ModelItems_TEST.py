#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_TestModelItems(PyOpenFLUIDTest):

    def runTest(self):
        """Test of model items globals functions."""
        self.preparePyOpenFLUIDClass(ArgList, "dataset")

        ListCheck = ("examples.primitives.unitsA.prod",
            "GENERATOR__SCALAR__var10__unitsA",
            "GENERATOR__SCALAR__var11__unitsA",
            "examples.primitives.unitsA.up",
            "examples.primitives.unitsB.prod")

        # test of getModelItems
        # check order
        self.assertEquals(ListCheck, tuple(self.openfluid.getModelItems()))


if __name__ == "__main__":
    ArgList = skipArgFromCL()
    unittest.main()
