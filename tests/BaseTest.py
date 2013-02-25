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

    def test_Main(self):
        """Call mainTest self function (user definied). No testing sequence required.
           Allows user to make a complete sequence of testing, without let control to unittest."""
        self.mainTest()

    def mainTest(self):
        pass
