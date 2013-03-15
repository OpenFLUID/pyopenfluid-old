#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_GeneratorParameter(PyOpenFLUIDTest):

    def runTest(self):
        """Test of generator parameters functions."""
        self.preparePyOpenFLUIDClass(ArgList, "output", "dataset",
            optional="project")

        UnitClass = "TestUnits"
        VarName = "tests.fixed"
        ParamName = "fixedvalue"

        # tests of getGeneratorParam
        Val = self.openfluid.getGeneratorParam(UnitClass, VarName, ParamName)

        self.assertRaisesOrElse(ValueError, self.openfluid.getGeneratorParam,
                self.assertIsNone, argObj=(UnitClass, VarName, "bidon") )
        self.assertRaisesOrElse(ValueError, self.openfluid.getGeneratorParam,
                self.assertIsNone, argObj=(UnitClass, "bidon", ParamName) )
        self.assertRaisesOrElse(ValueError, self.openfluid.getGeneratorParam,
                self.assertIsNone, argObj=("bidon", VarName, ParamName) )

        self.assertRaisesOrElse(ValueError, self.openfluid.getGeneratorParam,
                self.assertIsNone, argObj=(UnitClass, "bidon", "bidon") )
        self.assertRaisesOrElse(ValueError, self.openfluid.getGeneratorParam,
                self.assertIsNone, argObj=("bidon", "bidon", ParamName) )
        self.assertRaisesOrElse(ValueError, self.openfluid.getGeneratorParam,
                self.assertIsNone, argObj=(UnitClass, "bidon", "bidon") )

        print "Val:", Val
        self.assertTrue(isinstance(Val, str))
        self.checkNumeric(Val)

        # tests of getGeneratorParam/setGeneratorParam
        NvVal = str(float(Val) + 123.6)
        self.openfluid.setGeneratorParam(UnitClass, VarName, ParamName, NvVal)
        CheckVal = self.openfluid.getGeneratorParam(UnitClass, VarName, ParamName)
        self.assertTrue(isinstance(CheckVal, str))
        self.checkNumeric(CheckVal)
        self.assertNotEquals(CheckVal, Val)
        self.assertEquals(CheckVal, NvVal)


if __name__ == "__main__":
    ArgList = skipArgFromCL()
    unittest.main()
