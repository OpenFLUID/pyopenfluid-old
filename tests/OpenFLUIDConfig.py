#!/bin/env/python
# -*- coding: UTF-8 -*-

import PyOpenFLUID

# ** config keys **
# Optional keywords
#    -begin_date          => a string
#    -end_date            => a string
#    -delta_t             => a number
#    -model_global_param  => a list of pair key/value
#    -extra_simulator_path => a list of string
#    -extra_observer_path  => a list of string
#    -simulators           => a list of tuple(name, parameter: list of pair key/value)
#    -observers           => a list of tuple(name, parameter: list of pair key/value)
#    -units               => a list of tuple(class, id, process order)
#    -from_to             => a list of tuple(class from, id from,
#                               a list of tuple(class to, id to) )
#    -parent_child        => a list of tuple(class parent, id parent,
#                               a list of tuple(class child, id child) )
#    -attribute          => a list of tuple(class, attr name, attr val)
#    -attribute_by_units => a list of tuple(class, unit id, list of tuple(attr name, attr val))


def loadOpenFLUIDConfig(config, pyof=None):
    # pyopenfluid instance
    if not isinstance(pyof, PyOpenFLUID.PyOpenFLUID):
        pyof = PyOpenFLUID()
    #
    for mdp, val in config.get("model_global_param", []):
        pyof.setModelGlobalParam(mdp, val)
    if config.has_key("begin_date"):
        pyof.setPeriodBeginDate(config["begin_date"])
    if config.has_key("end_date"):
        pyof.setPeriodEndDate(config["end_date"])
    if config.has_key("delta_t"):
        pyof.setDefaultDeltaT(config["delta_t"])
    extraSimulatorPath = ":".join(config.get("extra_simulator_path", []))
    if len(extraSimulatorPath) > 0:
        pyof.addExtraSimulatorsPaths(extraSimulatorPath)
    extraObserverPath = ":".join(config.get("extra_observer_path", []))
    if len(extraObserverPath) > 0:
        pyof.addExtraObserversPaths(extraObserverPath)
    #
    for f, fParams in config.get("simulators", []):
        pyof.addSimulator(f)
        for key, val in fParams:
            pyof.setSimulatorParam(f, key, val)
    for o, oParams in config.get("observers", []):
        pyof.addObserver(o)
        for key, val in oParams:
            pyof.setObserverParam(o, key, val)
    #
    for UnitClass, UnitID, UnitProcessOrder in config.get("units", []):
        pyof.addUnit(UnitClass, UnitID, UnitProcessOrder)
    #
    for UnitClassFrom, UnitIDFrom, ListTo in config.get("from_to", []):
        for UnitClassTo, UnitIDTo in ListTo:
            pyof.addFromToConnection(UnitClassFrom, UnitIDFrom,\
                UnitClassTo, UnitIDTo)
    for UnitClassParent, UnitIDParent, ListChildren in config.get("parent_child", []):
        for UnitClassChild, UnitIDChild in ListChildren:
            pyof.addParentChildConnection(UnitClassParent, UnitIDParent,\
                UnitClassChild, UnitIDChild)
    for UnitClass, AttrName, AttrVal in config.get("attribute", []):
        pyof.createAttribute(UnitClass, AttrName, AttrVal)
    for UnitClass, UnitID, Params in config.get("attribute_by_units", []):
        for AttrName, AttrVal in Params:
            pyof.setAttribute(UnitClass, UnitID, AttrName, AttrVal)


def checkOpenFLUIDConfig(config, pyof=None):
    # pyopenfluid instance
    if not isinstance(pyof, PyOpenFLUID.PyOpenFLUID):
        pyof = PyOpenFLUID()
    #
    for mdp, val in config.get("model_global_param", []):
        assert pyof.getModelGlobalParam(mdp) == val
    if config.has_key("begin_date"):
        assert pyof.getPeriodBeginDate() == config["begin_date"]
    if config.has_key("end_date"):
        assert pyof.getPeriodEndDate() == config["end_date"]
    if config.has_key("delta_t"):
        assert pyof.getDefaultDeltaT() == config["delta_t"]
    assert pyof.getExtraSimulatorsPaths() == config.get("extra_simulator_path", [])
    assert pyof.getExtraObserversPaths() == config.get("extra_observer_path", [])
    #
    for f, fParams in config.get("simulators", []):
        assert f in pyof.getSimulatorsInModel()
        for key, val in fParams:
            assert pyof.getSimulatorParam(f, key) == val
    for o, oParams in config.get("observers", []):
        assert o in pyof.getObserversInMonitoring()
        for key, val in oParams:
            assert pyof.getObserverParam(o, key) == val
    #
    for UnitClass, UnitID, UnitProcessOrder in config.get("units", []):
        assert UnitClass in pyof.getUnitsClasses()
        assert UnitID in pyof.getUnitsIDs(UnitClass)
        assert UnitProcessOrder == pyof.getProcessOrder(UnitClass, UnitID)
    #
    for UnitClassFrom, UnitIDFrom, ListTo in config.get("from_to", []):
        for UnitClassTo, UnitIDTo in ListTo:
            assert (UnitClassTo, UnitIDTo) in pyof.getUnitTos(UnitClassFrom, UnitIDFrom)
    for UnitClassParent, UnitIDParent, ListChildren in config.get("parent_child", []):
        for UnitClassChild, UnitIDChild in ListChildren:
            assert (UnitClassChild, UnitIDChild) in\
                pyof.getUnitChildren(UnitClassParent, UnitIDParent)
    for UnitClass, AttrName, AttrVal in config.get("attribute", []):
        CheckList = []
        # searching for unset value
        for UClass, UID, Params in config.get("attribute_by_units", []):
            for IDName, IDVal in Params:
                if UClass == UnitClass and IDName == AttrName:
                    CheckList.append(UID)
        # check
        for ID in pyof.getUnitsIDs(UnitClass):
            if not ID in CheckList:
                assert pyof.getAttribute(UnitClass, ID, AttrName)\
                    == AttrVal
                break
    for UnitClass, UnitID, Params in config.get("attribute_by_units", []):
        for AttrName, AttrVal in Params:
            assert pyof.getAttribute(UnitClass, UnitID, AttrName) == AttrVal


def clearOpenFLUIDconfig(pyof):
    pyof.clearModel()
    pyof.clearMonitoring()
    pyof.clearAllUnits()
