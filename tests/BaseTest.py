#!/bin/env/python
# -*- coding: UTF-8 -*-

import unittest
import sys
import os

class PyOpenFLUIDTest(unittest.TestCase):
    def __init__(self, *args, **kw):
        """Initialize testing. Do not build any object in."""
        import PyOpenFLUID
        self.openfluid = None
        self.addCleanup(self.cleanUp, (), {})

    def setUp(self):
        """First test to run.
           Build the PyOpenFLUID object."""
        try:
            self.openfluid = PyOpenFLUID.PyOpenFLUID()
        except Exception:
            wlog( "Construction error" )
            self.assertTrue(False)
        finally:
            self.assertTrue(True)

    def cleanUp(self):
        """Clean up testing unit."""
        del PyOpenFLUID
        if not self.openfluid is None:
            del self.openfluid

    def test_ErrorHandler(self):
        """Call mainTest self function (user definied). No testing sequence required.
           If an exception is raised, it catches it and gives False to assertTrue
           function, otherwise, gives True."""
        try:
            self.mainTest()
        except Exception:
            self.assertTrue(False)
        finally:
            self.assertTrue(True)
