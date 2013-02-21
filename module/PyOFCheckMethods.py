#!/bin/env/python
# -*- coding: UTF-8 -*-

"""Checks functions for PyOpenFLUID parameters."""

__author__ = "Bastien Vaysse"
__copyright__ = "Copyright 2013, Creative Commons By-NC-ND license"
__credits__ = ["Bastien VAYSSE", "Jean-Christophe FABRE"]
__license__ = "GPLv3"
__version__ = "2.0.0~alpha"
__email__ = "bastien.vaysse@supagro.inra.fr"
__status__ = "Production"

import re

# ####################################### #
# ###   PYTHON TO C++ CHECK METHODS   ### #
# ####################################### #

##
# @brief Verify type.
#
# Check the arg parameter, verify arg's type in types list.
#
# @param Arg     the parameter to check
# @param Types   the list of types available for Arg
# @param Error   boolean, if set and if test fail, raise TypeError
#
# @return    True if arg's type is in types list
#
def PyOFCheckType (Arg, Types, Error=False):
    """Check the arg parameter, verify arg's type in types list.

    Keyword arguments:
    Arg     -- the parameter to checked
    Types   -- the list of types available for Arg
    Error   -- boolean, if set and if test fail, raise TypeError

    Returns:
    True if arg's type is in types list
    """

    if not isinstance(Arg, Types) :
        if Error:
            raise TypeError, "parameter should be a/an '%s' type" % (str(types))
        return False
    return True

# ####################################### #
# ###     OPENFLUID CHECK METHODS     ### #
# ####################################### #

##
# @brief Verify and extract date string by format.
#
# Check the date format, for begin and end date of the simulation.
# Do not check if the date exists.
# Format : (%Y-%m-%d %H:%M:%S)
#
# @param StrDate     a string representation of a date
#
# @return    False if string doesn't match the format, a dict otherwise
#
def PyOFExtractDate (StrDate):
    """Verify and extract the date format, for begin and end date of the simulation.
    Do not check if the date exists.
    Format : (%Y-%m-%d %H:%M:%S)

    Keyword arguments:
    StrDate   -- a string representation of a date

    Returns:
    False if string doesn't match the format, a dict otherwise
    """

    Expr = "^([0-9]{1,4})-([0-9]{2})-([0-9]{2}) ([0-9]{2}):([0-9]{2}):([0-9]{2})$"

    Validator = re.compile(Expr)
    Res = Validator.search(StrDate)

    # if wrong expression string
    if Res is None:
        return False

    DictDate = dict(year=int(Res.group(1)), month=int(Res.group(2)),
                    day=int(Res.group(3)), hour=int(Res.group(4)),
                    minute=int(Res.group(5)), second=int(Res.group(6)))
    return DictDate
