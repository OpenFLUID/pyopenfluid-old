#!/bin/env/python
# -*- coding: UTF-8 -*-

import unittest
import sys
import os
import re
import PyOpenFLUID

def skipArgFromLC():
    """Gets arguments (in line command) away from sys, because unittest will try to use them."""
    Res = sys.argv[1:]
    sys.argv = sys.argv[:1]
    return Res


# ########################################################################## #
# ########################################################################## #



class PyOpenFLUIDTest(unittest.TestCase):

# ########################################################################## #
# ########################################################################## #


    def __init__(self, *arg, **kw):
        """Initialize testing. Do not build any object in."""
        unittest.TestCase.__init__(self, *arg, **kw)
        self.openfluid = None
        self.addCleanup(self.cleanUp, (), {})


# ########################################################################## #
# ########################################################################## #


    def setUp(self):
        """First test to run.
           Build the PyOpenFLUID object."""
        try:
            self.openfluid = PyOpenFLUID.PyOpenFLUID()
        except Exception as e:
            self.assertTrue(False, "Error building PyOpenFLUID object\n> " + e.message)


# ########################################################################## #
# ########################################################################## #


    def cleanUp(self, *arg, **kw):
        """Clean up testing unit."""
        if not self.openfluid is None:
            del self.openfluid


# ########################################################################## #
# ########################################################################## #


    def test_Main(self):
        """Call mainTest self function (user definied). No testing sequence required.
           Allows user to make a complete sequence of testing, without let control to unittest."""
        self.mainTest()


# ########################################################################## #
# ########################################################################## #


    def mainTest(self):
        pass


# ########################################################################## #
# ###################         SPECIFIC FUNCTIONS         ################### #


    def loadInputDataset(self, Path):
        self.checkDirectory(Path)
        return self.openfluid.openDataset(Path)


# ########################################################################## #
# ########################################################################## #


    def loadProject(self, Path):
        self.checkDirectory(Path)
        return self.openfluid.openProject(Path)


# ########################################################################## #
# ########################################################################## #


    def loadAllInputDataset(self, List):
        for DTPath in List:
            try:
                self.openfluid = self.loadInputDataset(DTPath)
            except Exception as e:
                print "Loading input dataset fail : " + e.message
        else:
            return len(List)


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
