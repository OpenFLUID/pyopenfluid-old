#!/bin/env/python
# -*- coding: UTF-8 -*-

"""Exceptions for PyOpenFLUID operations."""

__author__ = "Bastien Vaysse"
__copyright__ = "Copyright 2013, Creative Commons By-NC-ND license"
__credits__ = ["Bastien VAYSSE", "Jean-Christophe FABRE"]
__license__ = "GPLv3"
__version__ = "2.0.0~alpha"
__email__ = "bastien.vaysse@supagro.inra.fr"
__status__ = "Production"

# ####################################### #
# ###      OPENFLUID ERROR CLASS      ### #
# ####################################### #

##
# @class PyOFError
# @brief Exception for PyOpenFLUID.
#
# Exceptions for PyOpenFLUID operations.
#
# @author     Bastien Vaysse <bastien.vaysse@supagro.inra.fr>
# @copyright  Copyright 2013 GPLv3
# @version    2.0.0~alpha
#
class PyOFError(Exception):
    """Base class for exceptions in this module."""
