#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_TestModelItems(PyOpenFLUIDTest):

    def runTest(self):
        """Test of model items globals functions."""

        FUNCTION = "function"
        GENERATOR = "generator"

        ListOfItems = [(FUNCTION, "fctA"), (FUNCTION, "fctB"), (GENERATOR, "genA"),\
            (FUNCTION, "fctC"), (GENERATOR, "genB"), (GENERATOR, "genC"),\
            (GENERATOR, "genD"), (FUNCTION, "fctLast")]

        # building
        UNITCLASS = "SU"
        self.openfluid.addUnit(UNITCLASS, 1, 1)
        for _type, name in ListOfItems:
            if _type == FUNCTION:
                self.openfluid.addFunction(name)
            elif _type == GENERATOR:
                self.openfluid.addGenerator(UNITCLASS, name)

        # test of getModelItems
        ListCheck = [b for a,b in ListOfItems]
        self.assertItemsEqual(ListCheck, self.openfluid.getModelItems())


if __name__ == "__main__":
    unittest.main()
