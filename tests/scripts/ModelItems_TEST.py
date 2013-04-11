#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_TestModelItems(PyOpenFLUIDTest):

    def runTest(self):
        """Test of model items globals functions."""
        self.preparePyOpenFLUIDClass(ArgList, "dataset")

        ListCheck = ("examples.primitives.unitsA.prod",
            "var10.unitsA.genscalar",
            "var11.unitsA.genscalar",
            "examples.primitives.unitsA.up",
            "examples.primitives.unitsB.prod")

        # test of getModelItems
        # check order
        self.assertEquals(ListCheck, tuple(self.openfluid.getModelItems()))


if __name__ == "__main__":
    ArgList = skipArgFromCL()
    unittest.main()
