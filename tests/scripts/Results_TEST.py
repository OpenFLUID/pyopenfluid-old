#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *
import numpy

class PyOpenFLUIDTest_Result(PyOpenFLUIDTest):

    def runTest(self):
        """Test of result functions."""
        self.preparePyOpenFLUIDClass(ArgList, "project")
        Base = self.openfluid.getCurrentOutputDir()

        Vars1 = "var1;var11"
        Vars2 = "var5"
        Vars3 = ("var3",)
        Units1 = "7;3"
        Units2 = "3"
        Units3 = ("5", "9")

        UnitClasses = ["unitsA", "unitsB"]*3

        # test of type
        self.assertRaises(Exception, self.openfluid.addCSVOutput,
                "unitsA", Vars1, None)
        self.assertRaises(Exception, self.openfluid.addCSVOutput,
                "unitsA", None, Units1)
        self.assertRaises(Exception, self.openfluid.addCSVOutput,
                None, Vars1, Units1)

        # add observers
        Obs1 = self.openfluid.addCSVOutput("unitsA", Vars1, Units1)
        Obs2 = self.openfluid.addCSVOutput("unitsB", Vars2, Units2)
        Obs3 = self.openfluid.addCSVOutput("unitsA", Vars3, Units3)
        Obs4 = self.openfluid.addCSVOutput("unitsB", "*", "*")
        Obs5 = self.openfluid.addCSVOutput("unitsA", "*", "*")

        # simulation
        self.openfluid.runSimulation()


        m = [m for m in os.listdir(Base) if m.endswith("csv") and m.startswith("pyof")]; m.sort()
        print "\n---> ".join([""]+m)
        print "-"*40

        # test of type
        self.assertRaises(Exception, self.openfluid.loadCSVOutput,
                Obs1, "unitsA", Vars1, None)
        self.assertRaises(Exception, self.openfluid.loadCSVOutput,
                Obs1, "unitsA", None, Units1)
        self.assertRaises(Exception, self.openfluid.loadCSVOutput,
                Obs1, None, Vars1, Units1)
        self.assertRaises(Exception, self.openfluid.loadCSVOutput,
                None, "unitsA", Vars1, Units1)

        # tests of results
        self.assertEquals(40,
            len(self.openfluid.loadCSVOutput(Obs5, UnitClasses[4], "*", "*")))
        self.assertEquals(5,
            len(self.openfluid.loadCSVOutput(Obs4, UnitClasses[3], "*", "*")))

        ToList = lambda l: l.split(";") if not isinstance(l, (list, tuple)) else l

        for i in range(1,4):
            ObsName = locals()["Obs%d"%i]
            UnitClass = UnitClasses[i-1]
            for ID in ToList(locals()["Units%d"%i]):
                for Var in ToList(locals()["Vars%d"%i]):
                    Res = self.openfluid.loadCSVOutput(ObsName, UnitClass, [ID], [Var])[0]
                    self.assertEquals(Res[0][0], UnitClass)
                    self.assertEquals(Res[0][1], ID)
                    self.assertEquals(Res[0][2], Var)
                    self.assertEquals(Res[1][0], "datetime")
                    self.assertEquals(Res[1][1], Var)
                    self.assertTrue(isinstance(Res[2][0], numpy.ndarray))
                    self.assertEquals(Res[2][0].dtype, numpy.datetime64)
                    self.assertTrue(isinstance(Res[2][1], numpy.ndarray))
                    self.assertEquals(Res[2][1].dtype, numpy.float64)


if __name__ == "__main__":
    ArgList = skipArgFromCL()
    unittest.main()
