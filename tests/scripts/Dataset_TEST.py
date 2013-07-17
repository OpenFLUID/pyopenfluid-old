#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *
from OpenFLUIDConfig import *

class PyOpenFLUIDTest_OpenDataSet(PyOpenFLUIDTest):

    def runTest(self):
        """Test of simulation functions."""
        DSPath = ArgList.get("dataset", None)
        self.assertIsNotNone(DSPath)

        # clearing datas AND settings new datas
        Config = dict(\
            begin_date = "2012-02-01 00:20:10",\
            end_date = "2013-10-10 10:10:10",\
            delta_t = 3600,\
            model_global_param = [("bluesky", "yes"), ("redstone", "no"), ("zero", "0")],\
            extra_simulator_path = ["the/simulator/path", "an/other/simulator/path"],\
            extra_observer_path = ["the/observer/path", "an/other/observer/path"],\
            simulators = [ ("simA", [("fixedvalue","3"), ("minvalue", "-5")]),\
                ("simB", [("rangemin", "0"), ("rangemax", "5"), ("rangeincr", "0.1")]),\
                ("simC", [("empty", "10"), ("random", "0.1454")]) ],\
            observers = [ ("obsA", [("format.h1.header","title")]),\
                ("obsB", [("column.f1.maxsize", "20"), ("column.f1.minsize", "0")]),\
                ("obsC", []) ],\
            units = [("SU", 1, 1), ("SU", 2, 2), ("SU", 3, 3), ("SU", 4, 4), ("SU", 5, 5),\
                ("DD", 1, 1), ("DD", 2, 1), ("DD", 3, 1), ("DD", 4, 1)],\
            from_to = [ ("SU", 1, [("SU", 2), ("SU", 3)]), ("SU", 5, [("SU", 4)]),\
                ("SU", 4, [("DD", 1)]), ("DD", 2, [("DD", 3)]) ],\
            parent_child = [ ("SU", 1, [("DD", 1), ("DD", 2)]), ("DD", 1, [("SU", 2)]) ],\
            attributes = [ ("SU", "area", "0"), ("SU", "color", "blue"),\
                ("DD", "unknown", "none") ],\
            attributes_by_units = [("SU", 1, [("area", "100.0"), ("color", "red")]),\
                ("SU", 2, [("color", "green")]), ("DD", 1, [("unknown", "true")]),\
                ("DD", 2, [("unknown", "true")]) ]
        )

        clearOpenFLUIDconfig(self.openfluid)
        loadOpenFLUIDConfig(Config, self.openfluid)
        checkOpenFLUIDConfig(Config, self.openfluid)

        # tests of saveDataset
        self.openfluid.saveDataset(DSPath)
        clearOpenFLUIDconfig(self.openfluid)

        # tests of openDataset
        self.checkDirectory(DSPath)
        self.openfluid.openDataset(DSPath)

        # tests of content
        checkOpenFLUIDConfig(Config, self.openfluid)

if __name__ == "__main__":
    ArgList = skipArgFromCL()
    unittest.main()
