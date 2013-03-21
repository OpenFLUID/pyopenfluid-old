#!/bin/env/python
# -*- coding: UTF-8 -*-

import unittest
import sys
import os
import re
import PyOpenFLUID

def skipArgFromCL():
    """Gets arguments (in line command) away from sys, because unittest will try to use them."""
    Res = sys.argv[1:]
    sys.argv = sys.argv[:1]

    Args = ()
    Kw = {}

    while len(Res) > 0:
      Word = Res.pop(0)
      if Word.startswith("--"):
        Kw[Word[2:]] = Res.pop(0)
      else:
        Args = Args + (Word,)
    Kw["__unknow__"] = Args

    return Kw


# ########################################################################## #
# ########################################################################## #



class PyOpenFLUIDTest(unittest.TestCase):

# ########################################################################## #
# ########################################################################## #


    def __init__(self, *arg, **kw):
        """Initialize testing. Do not build any object in."""
        unittest.TestCase.__init__(self)
        self.openfluid = None


# ########################################################################## #
# ########################################################################## #


    def setUp(self):
        """First method called.
           Build the PyOpenFLUID object."""
        try:
            self.openfluid = PyOpenFLUID.PyOpenFLUID()
        except Exception as e:
            self.assertTrue(False, "Error building PyOpenFLUID object\n> " + e.message)


# ########################################################################## #
# ########################################################################## #


    def tearDown(self, *arg, **kw):
        """Clean up testing unit."""
        if not self.openfluid is None:
            del self.openfluid


# ########################################################################## #
# ###################         SPECIFIC FUNCTIONS         ################### #


    def loadInputDataset(self, Path):
        self.checkDirectory(Path)
        self.openfluid.openDataset(Path)


# ########################################################################## #
# ########################################################################## #


    def loadProject(self, Path):
        self.checkDirectory(Path)
        self.openfluid.openProject(Path)


# ########################################################################## #
# ########################################################################## #


    def preparePyOpenFLUIDClass(self, DictIn, *Args, **Kw):
        def _actionPreparation(Key, Value):
            if Key == "dataset":
                self.loadInputDataset(Value)
            elif Key == "project":
                self.loadProject(Value)
            elif Key == "output":
                self.checkDirectory(Value)
                self.openfluid.setCurrentOutputDir(Value)
            elif Key == "funpath":
                self.checkDirectory(Value)
                self.openfluid.addExtraFunctionsPaths(Value)
            elif Key == "obspath":
                self.checkDirectory(Value)
                self.openfluid.addExtraObserversPaths(Value)
        #
        for Key in Args:
            self.assertTrue(DictIn.has_key(Key))
            _actionPreparation(Key, DictIn[Key])
        #
        Optional = list(Kw.get("optional", []))
        for Key in Optional:
            if DictIn.has_key(Key):
                _actionPreparation(Key, DictIn[Key])


# ########################################################################## #
# ###################          CHECK FUNCTIONS           ################### #


    def checkDirectory(self, Path):
        self.assertTrue(os.path.exists(Path) and (os.path.isdir(Path) or os.path.isfile(Path)))
        self.assertTrue(os.access(Path, os.R_OK))


# ########################################################################## #
# ########################################################################## #


    def checkFloat(self, InputStr):
        self.assertTrue(isinstance(InputStr, str))
        self.assertEquals(InputStr.count("."), 1)
        if InputStr.startswith("-"):
            InputStr = InputStr[1:]
        ISep = InputStr.index(".")
        self.assertTrue(InputStr[:ISep].isdigit())
        self.assertTrue(InputStr[ISep+1:].isdigit())


# ########################################################################## #
# ########################################################################## #


    def checkInt(self, InputStr):
        self.assertTrue(isinstance(InputStr, str))
        if InputStr.startswith("-"):
            InputStr = InputStr[1:]
        self.assertTrue(InputStr.isdigit())


# ########################################################################## #
# ########################################################################## #


    def checkNumeric(self, InputStr):
        self.assertTrue(isinstance(InputStr, str))
        if InputStr.startswith("-"):
            InputStr = InputStr[1:]
        if not InputStr.isdigit():
            ISep = InputStr.index(".")
            self.assertTrue(InputStr[:ISep].isdigit())
            self.assertTrue(InputStr[ISep+1:].isdigit())


# ########################################################################## #
# ########################################################################## #


    def checkSimulationOutputPath(self, OutPath):
        # verification dossier sortie non vide
        self.checkDirectory(OutPath)
        Contenu = os.listdir(OutPath)
        self.assertGreater(len(Contenu), 0)

        # verification des fichiers que le dossier contient
        ListModel = ["^.*\.(log|csv)$"]
        ListModel = [re.compile(Model) for Model in ListModel]
        for Fichier in Contenu:
            for ValidModel in ListModel:
                if not ValidModel.search(Fichier) is None:
                    break
            else:
                self.assertTrue(False, "file '{0}' doesn't suit any format.".
                        format(Fichier))


# ########################################################################## #
# ########################################################################## #


    def assertRaisesOrElse(self, exception, callObj, elseMethod,
            argObj=(), kwObj={}, argMeth=(), kwMeth={} ):
        if not ( callable(callObj) and callable(elseMethod) and
                issubclass(exception, Exception) and isinstance(argObj, tuple)
                and isinstance(kwObj, dict) and isinstance(argMeth, tuple)
                and isinstance(kwMeth, dict) ):
            print "1:", callable(callObj)
            print "2:", callable(elseMethod)
            print "3:", issubclass(exception, Exception)
            print "5:", isinstance(argObj, tuple)
            print "4:", isinstance(kwObj, dict)
            print "7:", isinstance(argMeth, tuple)
            print "6:", isinstance(kwMeth, dict)
            raise TypeError("'assertRaisesOrElse' method called with some wrong\
 parameter(s)")

        try:
            TmpRes = callObj(*argObj, **kwObj)
        except exception:
            pass
        except Exception:
            raise RuntimeError("exception occured wasn't the one excepted")
        else:
            return elseMethod(TmpRes, *argMeth, **kwMeth)
