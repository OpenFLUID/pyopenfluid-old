#!/bin/env/python
# -*- coding: UTF-8 -*-

# ########################################################################## #
# ###                                IMPORT                              ### #
# ########################################################################## #


try:
    import _pyopenfluid
except ImportError, msg:
    raise ImportError, str(msg) + ', please install the python-openfluid package'

# settings constants from library
CONST_ATTRIBUTES = ["__doc__", "__author__", "__version__", "__license__"]
for Attr in dir(_pyopenfluid):  
    if Attr in CONST_ATTRIBUTES:
        exec "{0} = _pyopenfluid.{1}".format(Attr, Attr)
del Attr, CONST_ATTRIBUTES


# ########################################################################## #
# ###                           OPENFLUID CLASS                          ### #
# ########################################################################## #

from PyOpenFLUID import PyOpenFLUID
