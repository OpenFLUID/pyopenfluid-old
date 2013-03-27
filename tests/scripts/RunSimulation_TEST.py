#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *
from OpenFLUIDConfig import *

class PyOpenFLUIDTest_RunSimulation(PyOpenFLUIDTest):

    def runTest(self):
        """Test of project functions."""
        PPath = ArgList.get("output", None)
        self.assertIsNotNone(PPath)

        # clearing datas AND settings new datas
        Config = dict(\
            begin_date = "2001-01-01 00:00:00",\
            end_date = "2001-01-15 08:01:02",\
            delta_t = 3600,\
            units = [ ("unitsA", 3, 3), ("unitsA", 1, 1),\
                ("unitsA", 5, 1), ("unitsA", 7, 2), ("unitsA", 9, 2),\
                ("unitsA", 6, 2), ("unitsA", 8, 3), ("unitsA", 2, 1),\
                ("unitsB", 1, 1), ("unitsB", 11, 1), ("unitsB", 2, 3),\
                ("unitsB", 7, 4), ("unitsB", 3, 2) ],\
            from_to = [ ("unitsA", 3, [("unitsB", 11)]),\
                ("unitsA", 1, [("unitsB", 2)]), ("unitsA", 5, [("unitsB", 7)]),\
                ("unitsA", 7, [("unitsB", 3)]), ("unitsA", 9, [("unitsA", 8)]),\
                ("unitsA", 6, [("unitsA", 8)]), ("unitsA", 8, [("unitsA", 7)]),\
                ("unitsA", 2, [("unitsA", 9)]), ("unitsB", 1, [("unitsB", 3)]),\
                ("unitsB", 11, [("unitsB", 3)]), ("unitsB", 2, [("unitsB", 7)]),\
                ("unitsB", 3, [("unitsB", 2)]) ],\
            functions = [ ("examples.primitives.unitsA.prod", []),\
                ("examples.primitives.unitsA.up", [("gmult", "3")]),\
                ("examples.primitives.unitsB.prod", []) ],\
            observers = [ ("export.vars.files.csv", [\
                ("format.f1.header","colnames-as-comment"),\
                ("format.f1.date","%Y-%m-%dT%H:%M:%S"),\
                ("format.f1.colsep"," "),\
                ("format.f1.precision","8"),\
                ("set.fullA.unitclass","unitsA"),\
                ("set.fullA.unitsIDs","*"),\
                ("set.fullA.vars","*"),\
                ("set.fullA.format","f1"),\
                ("set.fullB.unitclass","unitsB"),\
                ("set.fullB.unitsIDs","*"),\
                ("set.fullB.vars","*"),\
                ("set.fullB.format","f1")] )],\
            input_data = [ ("unitsA", "inivar1", "0.0"),\
                ("unitsB", "mult", "1")],\
            input_data_by_units = [("unitsA", 3, [("inivar1", "1.25")]),\
                ("unitsA", 8, [("inivar1", "2.385")]),\
                ("unitsA", 5, [("inivar1", "5.1")]),\
                ("unitsA", 9, [("inivar1", "2.1")]),\
                ("unitsA", 6, [("inivar1", "6.3")]),\
                ("unitsA", 2, [("inivar1", "1.235")]),\
                ("unitsA", 7, [("inivar1", "1.0")]),\
                ("unitsA", 1, [("inivar1", "1.0")]),\
                ("unitsB", 1, [("mult", "1")]),\
                ("unitsB", 11, [("mult", "2")]),\
                ("unitsB", 3, [("mult", "5")]),\
                ("unitsB", 2, [("mult", "2")]),\
                ("unitsB", 7, [("mult", "1")]) ]
        )

        # test of runSimulation
        clearOpenFLUIDconfig(self.openfluid)
        loadOpenFLUIDConfig(Config, self.openfluid)
        self.openfluid.setCurrentOutputDir(PPath)
        self.openfluid.runSimulation()


if __name__ == "__main__":
    ArgList = skipArgFromCL()
    unittest.main()
