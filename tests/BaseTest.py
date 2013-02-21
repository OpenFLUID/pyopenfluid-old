#!/bin/env/python
# -*- coding: UTF-8 -*-

import unittest
import sys
import os
import PyOpenFLUID

class PyOpenFLUIDTest(unittest.TestCase):
    def __init__(self, *arg, **kw):
        """Initialize testing. Do not build any object in."""
        unittest.TestCase.__init__(self, *arg, **kw)
        self.openfluid = None
        self.addCleanup(self.cleanUp, (), {})

    def setUp(self):
        """First test to run.
           Build the PyOpenFLUID object."""
        try:
            self.openfluid = PyOpenFLUID.PyOpenFLUID()
        except Exception as e:
            self.assertTrue(False, "Error building PyOpenFLUID object\n> " + e.message)

    def cleanUp(self, *arg, **kw):
        """Clean up testing unit."""
        if not self.openfluid is None:
            del self.openfluid

    def test_ErrorHandler(self):
        """Call mainTest self function (user definied). No testing sequence required.
           If an exception is raised, it catches it and gives False to assertTrue
           function, otherwise, gives True."""
        try:
            self.mainTest()
        except Exception as e:
            self.assertTrue(False, "Error handled during test\n> " + e.message)

    def mainTest(self):
        pass
