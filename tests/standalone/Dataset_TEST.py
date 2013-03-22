#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *
from random import randint, random

def randbool (nb=2) :
    assert nb > 0, "randbool impossible"
    return random() < (1.0 / nb)

def popRandom (list_, avoid=[]):
    a = list_[randint(0, len(list_)-1)]
    while a in avoid:
        a = list_[randint(0, len(list_)-1)]
    return a

def clear(pyof):
    pyof.clearAllUnits()
    pyof.clearModel()
    pyof.clearMonitoring()

class PyOpenFLUIDTest_OpenDataSet(PyOpenFLUIDTest):

    def runTest(self):
        """Test of simulation functions."""
        DSPath = ArgList.get("dataset", None)
        self.assertIsNotNone(DSPath)

        # clearing datas
        clear(self.openfluid)
        # adding datas to dataset
        LIST_UNIT = dict(
            UnitClassTest = [(i, randint(1,20)) for i in range(8)],
            SecClass = [(i, randint(1,20)) for i in range(10, 20)] )
        LIST_FUNCTIONS = dict(funcA = dict(zero="0"), funcB = dict(),
            funcC = dict(one="one", two="two", three="three"))
        LIST_OBSERVERS = dict(genA = dict(paramOne="one", paramTwo="two"), genB = dict())
        LIST_PARENT_CHILD_RELATION = dict()
        LIST_FROM_TO_RELATION = dict()

        for nmFun, paramFun in LIST_FUNCTIONS.items():
            self.openfluid.addFunction(nmFun)
            for nmParam, vlParam in paramFun.items():
                self.openfluid.setFunctionParam(nmFun, nmParam, vlParam)

        for nmObs, paramObs in LIST_OBSERVERS.items():
            self.openfluid.addObserver(nmObs)
            for nmParam, vlParam in paramObs.items():
                self.openfluid.setObserverParam(nmObs, nmParam, vlParam)

        for unitClass, lUnit in LIST_UNIT.items():
            for unitID, unitPO in lUnit:
                self.openfluid.addUnit(unitClass, unitID, unitPO)

        for unitClass, lUnit in LIST_UNIT.items():
            LIST_PARENT_CHILD_RELATION[unitClass] = dict()
            LIST_FROM_TO_RELATION[unitClass] = dict()
            _tmp_LISTID = map((lambda (a,b):a), lUnit)

            for unitID, unitPO in lUnit:
                LIST_PARENT_CHILD_RELATION[unitClass][unitID] =\
                    [i for i in _tmp_LISTID if i != unitID and randbool(3)]
                LIST_FROM_TO_RELATION[unitClass][unitID] =\
                    popRandom(_tmp_LISTID, avoid=[unitID])

                for childID in LIST_PARENT_CHILD_RELATION[unitClass][unitID]:
                    self.openfluid.addParentChildConnection(unitClass, unitID, unitClass, childID)
                self.openfluid.addFromToConnection(unitClass, unitID, unitClass,
                    LIST_FROM_TO_RELATION[unitClass][unitID])

        self.openfluid.setPeriodBeginDate("2001-01-01 01:01:01")
        self.openfluid.setPeriodEndDate("2002-02-02 02:02:02")
        self.openfluid.setDefaultDeltaT(3600)

        # tests of saveDataset
        self.openfluid.saveDataset(DSPath)
        clear(self.openfluid)

        # tests of openDataset
        self.checkDirectory(DSPath)
        self.openfluid.openDataset(DSPath)

        # tests of content
        self.assertItemsEqual(LIST_FUNCTIONS.keys(), self.openfluid.getFunctionsInModel())
        for nmFun, paramFun in LIST_FUNCTIONS.items():
            for nmParam, vlParam in paramFun.items():
                self.assertEquals(self.openfluid.getFunctionParam(nmFun, nmParam), vlParam)

        self.assertItemsEqual(LIST_OBSERVERS.keys(), self.openfluid.getObserversInMonitoring())
        for nmObs, paramObs in LIST_OBSERVERS.items():
            for nmParam, vlParam in paramObs.items():
                self.assertEquals(self.openfluid.getObserverParam(nmObs, nmParam), vlParam)

        self.assertItemsEqual(LIST_UNIT.keys(), self.openfluid.getUnitsClasses())
        for unitClass, lUnit in LIST_UNIT.items():
            for unitID, unitPO in lUnit:
                self.assertEquals(unitPO, self.openfluid.getProcessOrder(unitClass, unitID))
            self.assertEquals(self.openfluid.getUnitTos(unitClass, unitID),
                [(unitClass, LIST_FROM_TO_RELATION[unitClass][unitID])])
            self.assertItemsEqual(self.openfluid.getUnitChildren(unitClass, unitID),
                [(unitClass, a) for a in LIST_PARENT_CHILD_RELATION[unitClass][unitID] ])

if __name__ == "__main__":
    ArgList = skipArgFromCL()
    unittest.main()
