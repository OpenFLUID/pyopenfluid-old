#!/bin/env/python
# -*- coding: UTF-8 -*-

##
# @file PyOpenFLUID.py
# @author Bastien VAYSSE
#


# ########################################################################## #
# ###                                IMPORT                              ### #
# ########################################################################## #


try:
    import _pyopenfluid as pyopenfluid
except ImportError, msg:
    raise ImportError, str(msg) + ', please install the python-openfluid package'

# settings constants from library
__doc__ = pyopenfluid.__doc__
__author__ = pyopenfluid.__author__
__version__ = pyopenfluid.__version__
__license__ = pyopenfluid.__license__
__all__ = ["PyOpenFLUID"]


# ########################################################################## #
# ###                           OPENFLUID CLASS                          ### #
# ########################################################################## #


##
# @class PyOpenFLUID
# @brief OpenFLUID python class.
#
# This class provides OpenFLUID simulations, by loading, parameterizing and
#  running them. It uses the OpenFLUID framework to do simulations.
#
# @author     Bastien Vaysse <bastien.vaysse@supagro.inra.fr>
# @copyright  Copyright 2013 GPLv3
# @version    2.0.0~alpha
#
class PyOpenFLUID (pyopenfluid.PyOpenFLUID):
    """This class provides OpenFLUID simulations, by loading, parameterizing and running them. It uses the OpenFLUID framework to do simulations."""
    ##
    # Initialize a new PyOpenFLUID class.
    #
    #
    def __init__ (self):
        """Create an OpenFLUID class."""
        pyopenfluid.PyOpenFLUID.__init__(self)


# ########################################################################## #
# ###############              GENERAL FUNCTIONS             ############### #


    ##
    # Returns the OpenFLUID version.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{v = obj.@HLImportant{getVersion}()}
    # @EndExample
    #
    # @return   the OpenFLUID version number
    #
    def getVersion (self):
        """Returns the OpenFLUID version.

Returns:
the OpenFLUID version number
"""
        return pyopenfluid.PyOpenFLUID.getVersion(self)


# ########################################################################## #
# ########################################################################## #


    ##
    # Adds paths to search for simulation functions.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.@HLImportant{addExtraFunctionsPaths}(\"/first/path/to/add\")}
    #   @LineExSimple{@HLReserv{print} obj.getExtraFunctionsPaths()}
    #   @LineExResult{[\"/first/path/to/add\"]}
    #   @LineExSimple{obj.@HLImportant{addExtraFunctionsPaths}(\"/second/path/to/add:/third/path/to/add\")}
    #   @LineExSimple{@HLReserv{print} obj.getExtraFunctionsPaths()}
    #   @LineExResult{[\"/second/path/to/add:/third/path/to/add:/first/path/to/add\"]}
    #   @LineExSimple{obj.resetExtraFunctionsPaths()}
    #   @LineExSimple{@HLReserv{print} obj.getExtraFunctionsPaths()}
    #   @LineExResult{[]}
    # @EndExample
    #
    # @param Paths   the semicolon separated paths to add
    #
    def addExtraFunctionsPaths (self, Paths):
        """Adds paths to search for simulation functions.

Keyword arguments:
Paths  -- the semicolon separated paths to add
"""
        pyopenfluid.PyOpenFLUID.addExtraFunctionsPaths(self, Paths)


# ########################################################################## #
# ########################################################################## #


    ##
    # Reset paths to search for simulation functions.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.addExtraFunctionsPaths(\"/first/path/to/add\")}
    #   @LineExSimple{@HLReserv{print} obj.getExtraFunctionsPaths()}
    #   @LineExResult{[\"/first/path/to/add\"]}
    #   @LineExSimple{obj.addExtraFunctionsPaths(\"/second/path/to/add:/third/path/to/add\")}
    #   @LineExSimple{@HLReserv{print} obj.getExtraFunctionsPaths()}
    #   @LineExResult{[\"/second/path/to/add:/third/path/to/add:/first/path/to/add\"]}
    #   @LineExSimple{obj.@HLImportant{resetExtraFunctionsPaths}()}
    #   @LineExSimple{@HLReserv{print} obj.getExtraFunctionsPaths()}
    #   @LineExResult{[]}
    # @EndExample
    #
    def resetExtraFunctionsPaths (self):
        """Reset paths to search for simulation functions."""
        pyopenfluid.PyOpenFLUID.resetExtraFunctionsPaths(self)


# ########################################################################## #
# ########################################################################## #


    ##
    # Returns the added paths to search for simulation functions.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.addExtraFunctionsPaths(\"/first/path/to/add\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getExtraFunctionsPaths}()}
    #   @LineExResult{[\"/first/path/to/add\"]}
    #   @LineExSimple{obj.addExtraFunctionsPaths(\"/second/path/to/add:/third/path/to/add\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getExtraFunctionsPaths}()}
    #   @LineExResult{[\"/second/path/to/add:/third/path/to/add:/first/path/to/add\"]}
    #   @LineExSimple{obj.resetExtraFunctionsPaths()}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getExtraFunctionsPaths}()}
    #   @LineExResult{[]}
    # @EndExample
    #
    # @return   a list of Paths
    #
    def getExtraFunctionsPaths (self):
        """Returns the added paths to search for simulation functions.

Returns:
a list of Paths
"""
        return pyopenfluid.PyOpenFLUID.getExtraFunctionsPaths(self)


# ########################################################################## #
# ########################################################################## #


    ##
    # Adds paths to search for observers.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.@HLImportant{addExtraObserversPaths}(\"/first/path/to/add\")}
    #   @LineExSimple{@HLReserv{print} obj.getExtraObserversPaths()}
    #   @LineExResult{[\"/first/path/to/add\"]}
    #   @LineExSimple{obj.@HLImportant{addExtraObserversPaths}(\"/second/path/to/add:/third/path/to/add\")}
    #   @LineExSimple{@HLReserv{print} obj.getExtraObserversPaths()}
    #   @LineExResult{[\"/second/path/to/add:/third/path/to/add:/first/path/to/add\"]}
    #   @LineExSimple{obj.resetExtraObserversPaths()}
    #   @LineExSimple{@HLReserv{print} obj.getExtraObserversPaths()}
    #   @LineExResult{[]}
    # @EndExample
    #
    # @param Paths   the semicolon separated paths to add
    #
    def addExtraObserversPaths (self, Paths):
        """Adds paths to search for observers.

Keyword arguments:
Paths  -- the semicolon separated paths to add
"""
        pyopenfluid.PyOpenFLUID.addExtraObserversPaths(self, Paths)


# ########################################################################## #
# ########################################################################## #


    ##
    # Reset paths to search for observers.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.addExtraObserversPaths(\"/first/path/to/add\")}
    #   @LineExSimple{@HLReserv{print} obj.getExtraObserversPaths()}
    #   @LineExResult{[\"/first/path/to/add\"]}
    #   @LineExSimple{obj.addExtraObserversPaths(\"/second/path/to/add:/third/path/to/add\")}
    #   @LineExSimple{@HLReserv{print} obj.getExtraObserversPaths()}
    #   @LineExResult{[\"/second/path/to/add:/third/path/to/add:/first/path/to/add\"]}
    #   @LineExSimple{obj.@HLImportant{resetExtraObserversPaths}()}
    #   @LineExSimple{@HLReserv{print} obj.getExtraObserversPaths()}
    #   @LineExResult{[]}
    # @EndExample
    #
    def resetExtraObserversPaths (self):
        """Reset paths to search for observers."""
        pyopenfluid.PyOpenFLUID.resetExtraObserversPaths(self)


# ########################################################################## #
# ########################################################################## #


    ##
    # Returns the added paths to search for observers.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.addExtraObserversPaths(\"/first/path/to/add\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getExtraObserversPaths}()}
    #   @LineExResult{[\"/first/path/to/add\"]}
    #   @LineExSimple{obj.addExtraObserversPaths(\"/second/path/to/add:/third/path/to/add\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getExtraObserversPaths}()}
    #   @LineExResult{[\"/second/path/to/add:/third/path/to/add:/first/path/to/add\"]}
    #   @LineExSimple{obj.resetExtraObserversPaths()}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getExtraObserversPaths}()}
    #   @LineExResult{[]}
    # @EndExample
    #
    # @return   a list of Paths
    #
    def getExtraObserversPaths (self):
        """Returns the added paths to search for observers.

Returns:
a list of Paths
"""
        return pyopenfluid.PyOpenFLUID.getExtraObserversPaths(self)


# ########################################################################## #
# ########################################################################## #


    ##
    # Prints informations to screen about simulation definition class (self).
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{... @LineExComment{ open a project or configure the simulation}}
    #   @LineExSimple{obj.@HLImportant{printSimulationInfo}()}
    #   @LineExResult{Spatial domain is made of ....}
    # @EndExample
    #
    def printSimulationInfo (self):
        """Prints informations to screen about simulation definition class (self)."""
        pyopenfluid.PyOpenFLUID.printSimulationInfo(self)


# ########################################################################## #
# ###############               MODEL FUNCTIONS              ############### #


    ##
    # Returns a function parameter value.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.addFunction(\"my.function\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getFunctionParam}s(\"my.function\")}
    #   @LineExResult{[]}
    #   @LineExSimple{obj.setFunctionParam(\"my.function\"\,\"coeff\"\,\"3\")}
    #   @LineExSimple{@HLReserv{assert} obj.@HLImportant{getFunctionParam}(\"my_function\"\, \"coeff\") == \"3\"}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getFunctionParam}s(\"my.function\")}
    #   @LineExResult{[\"coeff\"]}
    #   @LineExSimple{obj.setFunctionParam(\"my.function\"\,\"tolerance\"\,\"0.2\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getFunctionParam}s(\"my.function\")}
    #   @LineExResult{[\"coeff\"\, \"tolerance\"]}
    #   @LineExSimple{obj.removeFunctionParam(\"my.function\"\, \"coeff\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getFunctionParam}s(\"my.function\")}
    #   @LineExResult{[\"tolerance\"]}
    # @EndExample
    #
    # @param FunID       the simulation function id
    # @param ParamName   the name of the parameter
    #
    # @return   the parameter value
    #
    def getFunctionParam (self, FunID, ParamName):
        """Returns a function parameter value.

Keyword arguments:
FunID      -- the simulation function id
ParamName  -- the name of the parameter

Returns:
the parameter value
"""
        return pyopenfluid.PyOpenFLUID.getFunctionParam(self, FunID, ParamName)


# ########################################################################## #
# ########################################################################## #


    ##
    # Sets a function parameter value.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.addFunction(\"my.function\")}
    #   @LineExSimple{@HLReserv{print} obj.getFunctionParams(\"my.function\")}
    #   @LineExResult{[]}
    #   @LineExSimple{obj.@HLImportant{setFunctionParam}(\"my.function\"\,\"coeff\"\,\"3\")}
    #   @LineExSimple{@HLReserv{assert} obj.getFunctionParam(\"my_function\"\, \"coeff\") == \"3\"}
    #   @LineExSimple{@HLReserv{print} obj.getFunctionParams(\"my.function\")}
    #   @LineExResult{[\"coeff\"]}
    #   @LineExSimple{obj.@HLImportant{setFunctionParam}(\"my.function\"\,\"tolerance\"\,\"0.2\")}
    #   @LineExSimple{@HLReserv{print} obj.getFunctionParams(\"my.function\")}
    #   @LineExResult{[\"coeff\"\, \"tolerance\"]}
    #   @LineExSimple{obj.removeFunctionParam(\"my.function\"\, \"coeff\")}
    #   @LineExSimple{@HLReserv{print} obj.getFunctionParams(\"my.function\")}
    #   @LineExResult{[\"tolerance\"]}
    # @EndExample
    #
    # @param FunID        the simulation function id
    # @param ParamName    the name of the parameter
    # @param ParamValue   the parameter value
    #
    def setFunctionParam (self, FunID, ParamName, ParamValue):
        """Sets a function parameter value.

Keyword arguments:
FunID        -- the simulation function id
ParamName    -- the name of the parameter
ParamValue   -- the parameter value
"""
        pyopenfluid.PyOpenFLUID.setFunctionParam(self, FunID, ParamName,
            ParamValue)


# ########################################################################## #
# ########################################################################## #


    ##
    # Removes a function parameter value.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.addFunction(\"my.function\")}
    #   @LineExSimple{@HLReserv{print} obj.getFunctionParams(\"my.function\")}
    #   @LineExResult{[]}
    #   @LineExSimple{obj.setFunctionParam(\"my.function\"\,\"coeff\"\,\"3\")}
    #   @LineExSimple{@HLReserv{assert} obj.getFunctionParam(\"my_function\"\, \"coeff\") == \"3\"}
    #   @LineExSimple{@HLReserv{print} obj.getFunctionParams(\"my.function\")}
    #   @LineExResult{[\"coeff\"]}
    #   @LineExSimple{obj.setFunctionParam(\"my.function\"\,\"tolerance\"\,\"0.2\")}
    #   @LineExSimple{@HLReserv{print} obj.getFunctionParams(\"my.function\")}
    #   @LineExResult{[\"coeff\"\, \"tolerance\"]}
    #   @LineExSimple{obj.@HLImportant{removeFunctionParam}(\"my.function\"\, \"coeff\")}
    #   @LineExSimple{@HLReserv{print} obj.getFunctionParams(\"my.function\")}
    #   @LineExResult{[\"tolerance\"]}
    # @EndExample
    #
    # @param FunID        the simulation function id
    # @param ParamName    the name of the parameter
    #
    def removeFunctionParam (self, FunID, ParamName):
        """Removes a function parameter value.

Keyword arguments:
FunID        -- the simulation function id
ParamName    -- the name of the parameter
"""
        pyopenfluid.PyOpenFLUID.removeFunctionParam(self, FunID, ParamName)


# ########################################################################## # ########################################################################## #


    ##
    # Returns all functions parameters.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.addFunction(\"my.function\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getFunctionParams}(\"my.function\")}
    #   @LineExResult{[]}
    #   @LineExSimple{obj.setFunctionParam(\"my.function\"\,\"coeff\"\,\"3\")}
    #   @LineExSimple{@HLReserv{assert} obj.getFunctionParam(\"my_function\"\, \"coeff\") == \"3\"}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getFunctionParams}(\"my.function\")}
    #   @LineExResult{[\"coeff\"]}
    #   @LineExSimple{obj.setFunctionParam(\"my.function\"\,\"tolerance\"\,\"0.2\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getFunctionParams}(\"my.function\")}
    #   @LineExResult{[\"coeff\"\, \"tolerance\"]}
    #   @LineExSimple{obj.removeFunctionParam(\"my.function\"\, \"coeff\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getFunctionParams}(\"my.function\")}
    #   @LineExResult{[\"tolerance\"]}
    # @EndExample
    #
    # @param FunID       the simulation function id
    #
    # @return   a list of parameter
    #
    def getFunctionParams (self, FunID):
        """Returns all functions parameters.

Keyword arguments:
FunID      -- the simulation function id

Returns:
a list of parameter
"""
        return pyopenfluid.PyOpenFLUID.getFunctionParams(self, FunID)


# ########################################################################## #
# ########################################################################## #


    ##
    # Returns a generator parameter value.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 1\, 1)}
    #   @LineExSimple{@LineExComment{obj.addGenerator(\"SU\"\\, \"var\")}}
    #   @LineExSimple{obj.setGeneratorParam(\"SU\"\,\"var.flux\"\,\"fixedvalue\"\,\"12.3\")}
    #   @LineExSimple{@HLReserv{assert} obj.@HLImportant{getGeneratorParam}(\"SU\"\,\"var.flux\"\,\"fixedvalue\") == \"12.3\"}
    # @EndExample
    #
    # @param UnitClass   the unit class to which the generator is applied
    # @param VarName     the variable name to which the generator is applied
    # @param ParamName   the name of the parameter
    #
    # @return   the parameter value
    #
    def getGeneratorParam (self, UnitClass, VarName, ParamName):
        """Returns a generator parameter value.

Keyword arguments:
UnitClass  -- the unit class to which the generator is applied
VarName    -- the variable name to which the generator is applied
ParamName  -- the name of the parameter

Returns:
the parameter value
"""
        return pyopenfluid.PyOpenFLUID.getGeneratorParam(self, UnitClass,
            VarName, ParamName)


# ########################################################################## #
# ########################################################################## #


    ##
    # Sets a generator parameter value.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 1\, 1)}
    #   @LineExSimple{@LineExComment{obj.addGenerator(\"SU\"\\, \"var\")}}
    #   @LineExSimple{obj.@HLImportant{setGeneratorParam}(\"SU\"\,\"var.flux\"\,\"fixedvalue\"\,\"12.3\")}
    #   @LineExSimple{@HLReserv{assert} obj.getGeneratorParam(\"SU\"\,\"var.flux\"\,\"fixedvalue\") == \"12.3\"}
    # @EndExample
    #
    # @param UnitClass    the unit class to which the generator is applied
    # @param VarName      the variable name to which the generator is applied
    # @param ParamName    the name of the parameter
    # @param ParamValue   the parameter value
    #
    def setGeneratorParam (self, UnitClass, VarName, ParamName, ParamValue):
        """Sets a generator parameter value.

Keyword arguments:
UnitClass   -- the unit class to which the generator is applied
VarName     -- the variable name to which the generator is applied
ParamName   -- the name of the parameter
ParamValue  -- the parameter value
"""
        return pyopenfluid.PyOpenFLUID.setGeneratorParam(self, UnitClass,
            VarName, ParamName, ParamValue)


# ########################################################################## #
# ########################################################################## #


    ##
    # Returns a model global parameter value.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getModelGlobalParam}s()}
    #   @LineExResult{[]}
    #   @LineExSimple{obj.setModelGlobalParam(\"gvalue\"\,\"37.2\")}
    #   @LineExSimple{@HLReserv{assert} obj.@HLImportant{getModelGlobalParam}(\"gvalue\") == \"37.2\"}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getModelGlobalParam}s()}
    #   @LineExResult{[\"gvalue\"]}
    #   @LineExSimple{obj.setModelGlobalParam(\"bluesky\"\,\"YES\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getModelGlobalParam}s()}
    #   @LineExResult{[\"gvalue\"\, \"bluesky\"]}
    #   @LineExSimple{obj.removeModelGlobalParam(\"gvalue\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getModelGlobalParam}s()}
    #   @LineExResult{[\"bluesky\"]}
    # @EndExample
    #
    # @param ParamName   the name of the parameter
    #
    # @return   the parameter value
    #
    def getModelGlobalParam (self, ParamName):
        """Returns a model global parameter value.

Keyword arguments:
ParamName  -- the name of the parameter

Returns:
the parameter value
"""
        return pyopenfluid.PyOpenFLUID.getModelGlobalParam(self, ParamName)


# ########################################################################## #
# ########################################################################## #


    ##
    # Sets a model global parameter value.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{@HLReserv{print} obj.getModelGlobalParams()}
    #   @LineExResult{[]}
    #   @LineExSimple{obj.@HLImportant{setModelGlobalParam}(\"gvalue\"\,\"37.2\")}
    #   @LineExSimple{@HLReserv{assert} obj.getModelGlobalParam(\"gvalue\") == \"37.2\"}
    #   @LineExSimple{@HLReserv{print} obj.getModelGlobalParams()}
    #   @LineExResult{[\"gvalue\"]}
    #   @LineExSimple{obj.@HLImportant{setModelGlobalParam}(\"bluesky\"\,\"YES\")}
    #   @LineExSimple{@HLReserv{print} obj.getModelGlobalParams()}
    #   @LineExResult{[\"gvalue\"\, \"bluesky\"]}
    #   @LineExSimple{obj.removeModelGlobalParam(\"gvalue\")}
    #   @LineExSimple{@HLReserv{print} obj.getModelGlobalParams()}
    #   @LineExResult{[\"bluesky\"]}
    # @EndExample
    #
    # @param ParamName    the name of the parameter
    # @param ParamValue   the parameter value
    #
    def setModelGlobalParam (self, ParamName, ParamValue):
        """Sets a model global parameter value.

Keyword arguments:
ParamName   -- the name of the parameter
ParamValue  -- the parameter value
"""
        return pyopenfluid.PyOpenFLUID.setModelGlobalParam(self, ParamName,
            ParamValue)


# ########################################################################## #
# ########################################################################## #


    ##
    # Returns all model global parameter.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getModelGlobalParams}()}
    #   @LineExResult{[]}
    #   @LineExSimple{obj.setModelGlobalParam(\"gvalue\"\,\"37.2\")}
    #   @LineExSimple{@HLReserv{assert} obj.getModelGlobalParam(\"gvalue\") == \"37.2\"}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getModelGlobalParams}()}
    #   @LineExResult{[\"gvalue\"]}
    #   @LineExSimple{obj.setModelGlobalParam(\"bluesky\"\,\"YES\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getModelGlobalParams}()}
    #   @LineExResult{[\"gvalue\"\, \"bluesky\"]}
    #   @LineExSimple{obj.removeModelGlobalParam(\"gvalue\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getModelGlobalParams}()}
    #   @LineExResult{[\"bluesky\"]}
    # @EndExample
    #
    def getModelGlobalParams (self):
        """Returns all model global parameter.

Returns:
a list of parameter name.
"""
        return pyopenfluid.PyOpenFLUID.getModelGlobalParams(self)


# ########################################################################## #
# ########################################################################## #


    ##
    # Returns all model global parameter.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{@HLReserv{print} obj.getModelGlobalParams()}
    #   @LineExResult{[]}
    #   @LineExSimple{obj.setModelGlobalParam(\"gvalue\"\,\"37.2\")}
    #   @LineExSimple{@HLReserv{assert} obj.getModelGlobalParam(\"gvalue\") == \"37.2\"}
    #   @LineExSimple{@HLReserv{print} obj.getModelGlobalParams()}
    #   @LineExResult{[\"gvalue\"]}
    #   @LineExSimple{obj.setModelGlobalParam(\"bluesky\"\,\"YES\")}
    #   @LineExSimple{@HLReserv{print} obj.getModelGlobalParams()}
    #   @LineExResult{[\"gvalue\"\, \"bluesky\"]}
    #   @LineExSimple{obj.@HLImportant{removeModelGlobalParam}(\"gvalue\")}
    #   @LineExSimple{@HLReserv{print} obj.getModelGlobalParams()}
    #   @LineExResult{[\"bluesky\"]}
    # @EndExample
    #
    # @param ParamName    the name of the parameter
    #
    def removeModelGlobalParam (self, ParamName):
        """Returns all model global parameter.

Keyword arguments:
ParamName   -- the name of the parameter
"""
        return pyopenfluid.PyOpenFLUID.removeModelGlobalParam(self, ParamName)


# ########################################################################## #
# ########################################################################## #


    ##
    # Adds a function.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{@HLReserv{print} obj.getFunctionsInModel()}
    #   @LineExResult{[]}
    #   @LineExSimple{obj.@HLImportant{addFunction}(\"firstFunc\")}
    #   @LineExSimple{@HLReserv{print} obj.getFunctionsInModel()}
    #   @LineExResult{[\"firstFunc\"]}
    #   @LineExSimple{obj.@HLImportant{addFunction}(\"secFunc\")}
    #   @LineExSimple{@HLReserv{print} obj.getFunctionsInModel()}
    #   @LineExResult{[\"firstFunc\"\, \"secFunc\"]}
    #   @LineExSimple{obj.removeFunction(\"firstFunc\")}
    #   @LineExSimple{@HLReserv{print} obj.getFunctionsInModel()}
    #   @LineExResult{[\"secFunc\"]}
    #   @LineExSimple{obj.clearModel()}
    #   @LineExSimple{@HLReserv{print} obj.getFunctionsInModel()}
    #   @LineExResult{[]}
    # @EndExample
    #
    # @param FuncID       the simulation function id
    #
    def addFunction (self, FuncID):
        """Adds a function.

Keyword arguments:
FuncID   -- the simulation function id
"""
        return pyopenfluid.PyOpenFLUID.addFunction(self, FuncID)


# ########################################################################## #
# ########################################################################## #


    ##
    # Removes a function.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{@HLReserv{print} obj.getFunctionsInModel()}
    #   @LineExResult{[]}
    #   @LineExSimple{obj.addFunction(\"firstFunc\")}
    #   @LineExSimple{@HLReserv{print} obj.getFunctionsInModel()}
    #   @LineExResult{[\"firstFunc\"]}
    #   @LineExSimple{obj.addFunction(\"secFunc\")}
    #   @LineExSimple{@HLReserv{print} obj.getFunctionsInModel()}
    #   @LineExResult{[\"firstFunc\"\, \"secFunc\"]}
    #   @LineExSimple{obj.@HLImportant{removeFunction}(\"firstFunc\")}
    #   @LineExSimple{@HLReserv{print} obj.getFunctionsInModel()}
    #   @LineExResult{[\"secFunc\"]}
    #   @LineExSimple{obj.clearModel()}
    #   @LineExSimple{@HLReserv{print} obj.getFunctionsInModel()}
    #   @LineExResult{[]}
    # @EndExample
    #
    # @param FuncID       the simulation function id
    #
    def removeFunction (self, FuncID):
        """Removes a function.

Keyword arguments:
FuncID   -- the simulation function id
"""
        return pyopenfluid.PyOpenFLUID.removeFunction(self, FuncID)


# ########################################################################## #
# ########################################################################## #


    ##
    # Removes all functions.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{@HLReserv{print} obj.getFunctionsInModel()}
    #   @LineExResult{[]}
    #   @LineExSimple{obj.addFunction(\"firstFunc\")}
    #   @LineExSimple{@HLReserv{print} obj.getFunctionsInModel()}
    #   @LineExResult{[\"firstFunc\"]}
    #   @LineExSimple{obj.addFunction(\"secFunc\")}
    #   @LineExSimple{@HLReserv{print} obj.getFunctionsInModel()}
    #   @LineExResult{[\"firstFunc\"\, \"secFunc\"]}
    #   @LineExSimple{obj.removeFunction(\"firstFunc\")}
    #   @LineExSimple{@HLReserv{print} obj.getFunctionsInModel()}
    #   @LineExResult{[\"secFunc\"]}
    #   @LineExSimple{obj.@HLImportant{clearModel}()}
    #   @LineExSimple{@HLReserv{print} obj.getFunctionsInModel()}
    #   @LineExResult{[]}
    # @EndExample
    #
    def clearModel (self):
        """Removes all functions."""
        return pyopenfluid.PyOpenFLUID.clearModel(self)


# ########################################################################## #
# ########################################################################## #


    ##
    # Gets all functions names.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getFunctionsInModel}()}
    #   @LineExResult{[]}
    #   @LineExSimple{obj.addFunction(\"firstFunc\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getFunctionsInModel}()}
    #   @LineExResult{[\"firstFunc\"]}
    #   @LineExSimple{obj.addFunction(\"secFunc\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getFunctionsInModel}()}
    #   @LineExResult{[\"firstFunc\"\, \"secFunc\"]}
    #   @LineExSimple{obj.removeFunction(\"firstFunc\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getFunctionsInModel}()}
    #   @LineExResult{[\"secFunc\"]}
    #   @LineExSimple{obj.clearModel()}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getFunctionsInModel}()}
    #   @LineExResult{[]}
    # @EndExample
    #
    # @return   a list of function name
    #
    def getFunctionsInModel (self):
        """Gets all functions names.

Returns:
a list of function name
"""
        return pyopenfluid.PyOpenFLUID.getFunctionsInModel(self)


# ########################################################################## #
# ###############             MONITORING FUNCTIONS           ############### #


    ##
    # Returns an observer parameter value.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.addObserver(\"export.test.fake\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getObserverParam}s(\"export.test.fake\")}
    #   @LineExResult{[]}
    #   @LineExSimple{obj.setObserverParam(\"@HLImportant{getObserverParam}s\"\, \"format.f1.header\"\, \"colsname\")}
    #   @LineExSimple{@HLReserv{assert} obj.@HLImportant{getObserverParam}(\"@HLImportant{getObserverParam}s\"\, \"format.f1.header\") == \"colsname\"}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getObserverParam}s(\"export.test.fake\")}
    #   @LineExResult{[\"format.f1.header\"]}
    #   @LineExSimple{obj.setObserverParam(\"@HLImportant{getObserverParam}s\"\, \"format.f1.maxwidth\"\, \"50\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getObserverParam}s(\"export.test.fake\")}
    #   @LineExResult{[\"format.f1.header\"\, \"format.f1.maxwidth\"]}
    #   @LineExSimple{obj.removeObserverParam(\"export.test.fake\"\, \"format.f1.header\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getObserverParam}s(\"export.test.fake\")}
    #   @LineExResult{[\"format.f1.maxwidth\"]}
    # @EndExample
    #
    # @param ObsID       the observer id
    # @param ParamName   the name of the parameter
    #
    # @return   the parameter value
    #
    def getObserverParam (self, ObsID, ParamName):
        """Returns an observer parameter value.

Keyword arguments:
ObsID      -- the observer id
ParamName  -- the name of the parameter

Returns:
the parameter value
"""
        return pyopenfluid.PyOpenFLUID.getObserverParam(self, ObsID, ParamName)


# ########################################################################## #
# ########################################################################## #


    ##
    # Sets an observer parameter value.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.addObserver(\"export.test.fake\")}
    #   @LineExSimple{@HLReserv{print} obj.getObserverParams(\"export.test.fake\")}
    #   @LineExResult{[]}
    #   @LineExSimple{obj.@HLImportant{setObserverParam}(\"getObserverParams\"\, \"format.f1.header\"\, \"colsname\")}
    #   @LineExSimple{@HLReserv{assert} obj.getObserverParam(\"getObserverParams\"\, \"format.f1.header\") == \"colsname\"}
    #   @LineExSimple{@HLReserv{print} obj.getObserverParams(\"export.test.fake\")}
    #   @LineExResult{[\"format.f1.header\"]}
    #   @LineExSimple{obj.@HLImportant{setObserverParam}(\"getObserverParams\"\, \"format.f1.maxwidth\"\, \"50\")}
    #   @LineExSimple{@HLReserv{print} obj.getObserverParams(\"export.test.fake\")}
    #   @LineExResult{[\"format.f1.header\"\, \"format.f1.maxwidth\"]}
    #   @LineExSimple{obj.removeObserverParam(\"export.test.fake\"\, \"format.f1.header\")}
    #   @LineExSimple{@HLReserv{print} obj.getObserverParams(\"export.test.fake\")}
    #   @LineExResult{[\"format.f1.maxwidth\"]}
    # @EndExample
    #
    # @param ObsID       the observer id
    # @param ParamName   the name of the parameter
    # @param ParamValue  the parameter value
    #
    def setObserverParam (self, ObsID, ParamName, ParamValue):
        """Sets an observer parameter value.

Keyword arguments:
ObsID       -- the observer id
ParamName   -- the name of the parameter
ParamValue  -- the parameter value
"""
        return pyopenfluid.PyOpenFLUID.setObserverParam(self, ObsID, ParamName,
            ParamValue)


# ########################################################################## #
# ########################################################################## #


    ##
    # Removes an observer parameter.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.addObserver(\"export.test.fake\")}
    #   @LineExSimple{@HLReserv{print} obj.getObserverParams(\"export.test.fake\")}
    #   @LineExResult{[]}
    #   @LineExSimple{obj.setObserverParam(\"getObserverParams\"\, \"format.f1.header\"\, \"colsname\")}
    #   @LineExSimple{@HLReserv{assert} obj.getObserverParam(\"getObserverParams\"\, \"format.f1.header\") == \"colsname\"}
    #   @LineExSimple{@HLReserv{print} obj.getObserverParams(\"export.test.fake\")}
    #   @LineExResult{[\"format.f1.header\"]}
    #   @LineExSimple{obj.setObserverParam(\"getObserverParams\"\, \"format.f1.maxwidth\"\, \"50\")}
    #   @LineExSimple{@HLReserv{print} obj.getObserverParams(\"export.test.fake\")}
    #   @LineExResult{[\"format.f1.header\"\, \"format.f1.maxwidth\"]}
    #   @LineExSimple{obj.@HLImportant{removeObserverParam}(\"export.test.fake\"\, \"format.f1.header\")}
    #   @LineExSimple{@HLReserv{print} obj.getObserverParams(\"export.test.fake\")}
    #   @LineExResult{[\"format.f1.maxwidth\"]}
    # @EndExample
    #
    # @param ObsID       the observer id
    # @param ParamName   the name of the parameter
    #
    def removeObserverParam (self, ObsID, ParamName):
        """Removes an observer parameter.

Keyword arguments:
ObsID       -- the observer id
ParamName   -- the name of the parameter
"""
        return pyopenfluid.PyOpenFLUID.removeObserverParam(self, ObsID,
            ParamName)


# ########################################################################## #
# ########################################################################## #


    ##
    # Gets all observer parameters name.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.addObserver(\"export.test.fake\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getObserverParams}(\"export.test.fake\")}
    #   @LineExResult{[]}
    #   @LineExSimple{obj.setObserverParam(\"@HLImportant{getObserverParams}\"\, \"format.f1.header\"\, \"colsname\")}
    #   @LineExSimple{@HLReserv{assert} obj.getObserverParam(\"@HLImportant{getObserverParams}\"\, \"format.f1.header\") == \"colsname\"}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getObserverParams}(\"export.test.fake\")}
    #   @LineExResult{[\"format.f1.header\"]}
    #   @LineExSimple{obj.setObserverParam(\"@HLImportant{getObserverParams}\"\, \"format.f1.maxwidth\"\, \"50\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getObserverParams}(\"export.test.fake\")}
    #   @LineExResult{[\"format.f1.header\"\, \"format.f1.maxwidth\"]}
    #   @LineExSimple{obj.removeObserverParam(\"export.test.fake\"\, \"format.f1.header\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getObserverParams}(\"export.test.fake\")}
    #   @LineExResult{[\"format.f1.maxwidth\"]}
    # @EndExample
    #
    # @param ObsID       the observer id
    #
    def getObserverParams (self, ObsID):
        """Gets all observer parameters name.

Keyword arguments:
ObsID       -- the observer id

Returns:
a list of observer parameters name.
"""
        return pyopenfluid.PyOpenFLUID.getObserverParams(self, ObsID)


# ########################################################################## #
# ########################################################################## #


    ##
    # Adds an observer.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{@HLReserv{print} obj.getObserversInMonitoring()}
    #   @LineExResult{[]}
    #   @LineExSimple{obj.@HLImportant{addObserver}(\"export.test.firstObs\")}
    #   @LineExSimple{@HLReserv{print} obj.getObserversInMonitoring()}
    #   @LineExResult{[\"export.test.firstObs\"]}
    #   @LineExSimple{obj.@HLImportant{addObserver}(\"export.test2.secObs\")}
    #   @LineExSimple{@HLReserv{print} obj.getObserversInMonitoring()}
    #   @LineExResult{[\"export.test.firstObs\"\, \"export.test2.secObs\"]}
    #   @LineExSimple{obj.removeObserver(\"export.test.firstObs\")}
    #   @LineExSimple{@HLReserv{print} obj.getObserversInMonitoring()}
    #   @LineExResult{[\"export.test2.secObs\"]}
    #   @LineExSimple{obj.clearMonitoring()}
    #   @LineExSimple{@HLReserv{print} obj.getObserversInMonitoring()}
    #   @LineExResult{[]}
    # @EndExample
    #
    # @param ObsID       the observer id
    #
    def addObserver (self, ObsID):
        """Adds an observer.

Keyword arguments:
ObsID       -- the observer id
"""
        return pyopenfluid.PyOpenFLUID.addObserver(self, ObsID)


# ########################################################################## #
# ########################################################################## #


    ##
    # Removes an observer.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{@HLReserv{print} obj.getObserversInMonitoring()}
    #   @LineExResult{[]}
    #   @LineExSimple{obj.addObserver(\"export.test.firstObs\")}
    #   @LineExSimple{@HLReserv{print} obj.getObserversInMonitoring()}
    #   @LineExResult{[\"export.test.firstObs\"]}
    #   @LineExSimple{obj.addObserver(\"export.test2.secObs\")}
    #   @LineExSimple{@HLReserv{print} obj.getObserversInMonitoring()}
    #   @LineExResult{[\"export.test.firstObs\"\, \"export.test2.secObs\"]}
    #   @LineExSimple{obj.@HLImportant{removeObserver}(\"export.test.firstObs\")}
    #   @LineExSimple{@HLReserv{print} obj.getObserversInMonitoring()}
    #   @LineExResult{[\"export.test2.secObs\"]}
    #   @LineExSimple{obj.clearMonitoring()}
    #   @LineExSimple{@HLReserv{print} obj.getObserversInMonitoring()}
    #   @LineExResult{[]}
    # @EndExample
    #
    # @param ObsID       the observer id
    #
    def removeObserver (self, ObsID):
        """Removes an observer.

Keyword arguments:
ObsID       -- the observer id
"""
        return pyopenfluid.PyOpenFLUID.removeObserver(self, ObsID)


# ########################################################################## #
# ########################################################################## #


    ##
    # Removes all observers.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{@HLReserv{print} obj.getObserversInMonitoring()}
    #   @LineExResult{[]}
    #   @LineExSimple{obj.addObserver(\"export.test.firstObs\")}
    #   @LineExSimple{@HLReserv{print} obj.getObserversInMonitoring()}
    #   @LineExResult{[\"export.test.firstObs\"]}
    #   @LineExSimple{obj.addObserver(\"export.test2.secObs\")}
    #   @LineExSimple{@HLReserv{print} obj.getObserversInMonitoring()}
    #   @LineExResult{[\"export.test.firstObs\"\, \"export.test2.secObs\"]}
    #   @LineExSimple{obj.removeObserver(\"export.test.firstObs\")}
    #   @LineExSimple{@HLReserv{print} obj.getObserversInMonitoring()}
    #   @LineExResult{[\"export.test2.secObs\"]}
    #   @LineExSimple{obj.@HLImportant{clearMonitoring}()}
    #   @LineExSimple{@HLReserv{print} obj.getObserversInMonitoring()}
    #   @LineExResult{[]}
    # @EndExample
    #
    def clearMonitoring (self):
        """Removes all observers.
"""
        return pyopenfluid.PyOpenFLUID.clearMonitoring(self)


# ########################################################################## #
# ########################################################################## #


    ##
    # Gets all observer name.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getObserversInMonitoring}()}
    #   @LineExResult{[]}
    #   @LineExSimple{obj.addObserver(\"export.test.firstObs\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getObserversInMonitoring}()}
    #   @LineExResult{[\"export.test.firstObs\"]}
    #   @LineExSimple{obj.addObserver(\"export.test2.secObs\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getObserversInMonitoring}()}
    #   @LineExResult{[\"export.test.firstObs\"\, \"export.test2.secObs\"]}
    #   @LineExSimple{obj.removeObserver(\"export.test.firstObs\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getObserversInMonitoring}()}
    #   @LineExResult{[\"export.test2.secObs\"]}
    #   @LineExSimple{obj.clearMonitoring()}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getObserversInMonitoring}()}
    #   @LineExResult{[]}
    # @EndExample
    #
    def getObserversInMonitoring (self):
        """Gets all observer name.

Returns:
a list of observer name
"""
        return pyopenfluid.PyOpenFLUID.getObserversInMonitoring(self)


# ########################################################################## #
# ###############           SPATIAL DOMAIN FUNCTIONS         ############### #


    ##
    # Returns the existing units classes.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getUnitsClasses}()}
    #   @LineExResult{[]}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 1\, 1)}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getUnitsClasses}()}
    #   @LineExResult{[\"SU\"]}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsIDs(\"SU\")}
    #   @LineExResult{[1]}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 2\, 1)}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getUnitsClasses}()}
    #   @LineExResult{[\"SU\"]}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsIDs(\"SU\")}
    #   @LineExResult{[1\, 2]}
    #   @LineExSimple{obj.addUnit(\"WQ\"\, 1\, 1)}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getUnitsClasses}()}
    #   @LineExResult{[\"SU\"\, \"WQ\"]}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsIDs(\"WQ\")}
    #   @LineExResult{[1]}
    #   @LineExSimple{obj.removeUnit(\"SU\"\, 1)}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getUnitsClasses}()}
    #   @LineExResult{[\"SU\"\, \"WQ\"]}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsIDs(\"SU\")}
    #   @LineExResult{[2]}
    #   @LineExSimple{obj.clearUnitClass(\"SU\")}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getUnitsClasses}()}
    #   @LineExResult{[\"WQ\"]}
    # @EndExample
    #
    # @return   a list of units classes
    #
    def getUnitsClasses (self):
        """Returns the existing units classes.

Returns:
a list of units classes
"""
        return pyopenfluid.PyOpenFLUID.getUnitsClasses(self)


# ########################################################################## #
# ########################################################################## #


    ##
    # Returns the existing units IDs for a given units class.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsClasses()}
    #   @LineExResult{[]}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 1\, 1)}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsClasses()}
    #   @LineExResult{[\"SU\"]}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getUnitsIDs}(\"SU\")}
    #   @LineExResult{[1]}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 2\, 1)}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsClasses()}
    #   @LineExResult{[\"SU\"]}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getUnitsIDs}(\"SU\")}
    #   @LineExResult{[1\, 2]}
    #   @LineExSimple{obj.addUnit(\"WQ\"\, 1\, 1)}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsClasses()}
    #   @LineExResult{[\"SU\"\, \"WQ\"]}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getUnitsIDs}(\"WQ\")}
    #   @LineExResult{[1]}
    #   @LineExSimple{obj.removeUnit(\"SU\"\, 1)}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsClasses()}
    #   @LineExResult{[\"SU\"\, \"WQ\"]}
    #   @LineExSimple{@HLReserv{print} obj.@HLImportant{getUnitsIDs}(\"SU\")}
    #   @LineExResult{[2]}
    #   @LineExSimple{obj.clearUnitClass(\"SU\")}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsClasses()}
    #   @LineExResult{[\"WQ\"]}
    # @EndExample
    #
    # @param UnitClass   the unit class
    #
    # @return   a list of units IDs
    #
    def getUnitsIDs (self, UnitClass):
        """Returns the existing units IDs for a given units class.

Keyword arguments:
UnitClass  -- the unit class

Returns:
a list of units IDs
"""
        return pyopenfluid.PyOpenFLUID.getUnitsIDs(self, UnitClass)


# ########################################################################## #
# ########################################################################## #


    ##
    # Adds an new unit.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsClasses()}
    #   @LineExResult{[]}
    #   @LineExSimple{obj.@HLImportant{addUnit}(\"SU\"\, 1\, 1)}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsClasses()}
    #   @LineExResult{[\"SU\"]}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsIDs(\"SU\")}
    #   @LineExResult{[1]}
    #   @LineExSimple{obj.@HLImportant{addUnit}(\"SU\"\, 2\, 1)}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsClasses()}
    #   @LineExResult{[\"SU\"]}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsIDs(\"SU\")}
    #   @LineExResult{[1\, 2]}
    #   @LineExSimple{obj.@HLImportant{addUnit}(\"WQ\"\, 1\, 1)}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsClasses()}
    #   @LineExResult{[\"SU\"\, \"WQ\"]}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsIDs(\"WQ\")}
    #   @LineExResult{[1]}
    #   @LineExSimple{obj.removeUnit(\"SU\"\, 1)}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsClasses()}
    #   @LineExResult{[\"SU\"\, \"WQ\"]}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsIDs(\"SU\")}
    #   @LineExResult{[2]}
    #   @LineExSimple{obj.clearUnitClass(\"SU\")}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsClasses()}
    #   @LineExResult{[\"WQ\"]}
    # @EndExample
    #
    # @param UnitClass   an unit class
    # @param UnitID      an new unit id for this unit class
    # @param PcsOrder    a process order
    #
    def addUnit (self, UnitClass, UnitID, PcsOrder):
        """Adds an new unit.

Keyword arguments:
UnitClass  -- an unit class
UnitID     -- an new unit id for this unit class
PcsOrder   -- a process order
"""
        return pyopenfluid.PyOpenFLUID.addUnit(self, UnitClass,
            UnitID, PcsOrder)


# ########################################################################## #
# ########################################################################## #


    ##
    # Removes an unit.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsClasses()}
    #   @LineExResult{[]}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 1\, 1)}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsClasses()}
    #   @LineExResult{[\"SU\"]}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsIDs(\"SU\")}
    #   @LineExResult{[1]}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 2\, 1)}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsClasses()}
    #   @LineExResult{[\"SU\"]}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsIDs(\"SU\")}
    #   @LineExResult{[1\, 2]}
    #   @LineExSimple{obj.addUnit(\"WQ\"\, 1\, 1)}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsClasses()}
    #   @LineExResult{[\"SU\"\, \"WQ\"]}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsIDs(\"WQ\")}
    #   @LineExResult{[1]}
    #   @LineExSimple{obj.@HLImportant{removeUnit}(\"SU\"\, 1)}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsClasses()}
    #   @LineExResult{[\"SU\"\, \"WQ\"]}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsIDs(\"SU\")}
    #   @LineExResult{[2]}
    #   @LineExSimple{obj.clearUnitClass(\"SU\")}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsClasses()}
    #   @LineExResult{[\"WQ\"]}
    # @EndExample
    #
    # @param UnitClass   an unit class
    # @param UnitID      an unit id for this unit class
    #
    def removeUnit (self, UnitClass, UnitID):
        """Removes an unit.

Keyword arguments:
UnitClass  -- an unit class
UnitID     -- an unit id for this unit class
"""
        return pyopenfluid.PyOpenFLUID.removeUnit(self, UnitClass,
            UnitID)


# ########################################################################## #
# ########################################################################## #


    ##
    # Removes all units from an unit class.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsClasses()}
    #   @LineExResult{[]}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 1\, 1)}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsClasses()}
    #   @LineExResult{[\"SU\"]}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsIDs(\"SU\")}
    #   @LineExResult{[1]}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 2\, 1)}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsClasses()}
    #   @LineExResult{[\"SU\"]}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsIDs(\"SU\")}
    #   @LineExResult{[1\, 2]}
    #   @LineExSimple{obj.addUnit(\"WQ\"\, 1\, 1)}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsClasses()}
    #   @LineExResult{[\"SU\"\, \"WQ\"]}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsIDs(\"WQ\")}
    #   @LineExResult{[1]}
    #   @LineExSimple{obj.removeUnit(\"SU\"\, 1)}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsClasses()}
    #   @LineExResult{[\"SU\"\, \"WQ\"]}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsIDs(\"SU\")}
    #   @LineExResult{[2]}
    #   @LineExSimple{obj.@HLImportant{clearUnitClass}(\"SU\")}
    #   @LineExSimple{@HLReserv{print} obj.getUnitsClasses()}
    #   @LineExResult{[\"WQ\"]}
    # @EndExample
    #
    # @param UnitClass   an unit class
    #
    def clearUnitClass (self, UnitClass):
        """Removes all units from an unit class.

Keyword arguments:
UnitClass  -- an unit class
"""
        return pyopenfluid.PyOpenFLUID.clearUnitClass(self, UnitClass)


# ########################################################################## #
# ########################################################################## #


    ##
    # Sets the process order of an unit.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 1\, 1)}
    #   @LineExSimple{@HLReserv{assert} obj.getUnitProcessOrder(\"SU\"\, 1) == 1}
    #   @LineExSimple{obj.@HLImportant{setUnitProcessOrder}(\"SU\"\, 1\, 5)}
    #   @LineExSimple{@HLReserv{assert} obj.getUnitProcessOrder(\"SU\"\, 1) == 5}
    # @EndExample
    #
    # @param UnitClass   an unit class
    # @param UnitID      an unit id for this unit class
    # @param PcsOrder    a process order
    #
    def setUnitProcessOrder (self, UnitClass, UnitID, PcsOrder):
        """Sets the process order of an unit.

Keyword arguments:
UnitClass  -- an unit class
UnitID     -- an unit id for this unit class
PcsOrder   -- a process order
"""
        return pyopenfluid.PyOpenFLUID.setUnitProcessOrder(self, UnitClass,
            UnitID, PcsOrder)


# ########################################################################## #
# ########################################################################## #


    ##
    # Gets the process order of an unit.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 1\, 1)}
    #   @LineExSimple{@HLReserv{assert} obj.@HLImportant{getUnitProcessOrder}(\"SU\"\, 1) == 1}
    #   @LineExSimple{obj.setUnitProcessOrder(\"SU\"\, 1\, 5)}
    #   @LineExSimple{@HLReserv{assert} obj.@HLImportant{getUnitProcessOrder}(\"SU\"\, 1) == 5}
    # @EndExample
    #
    # @param UnitClass   an unit class
    # @param UnitID      an unit id for this unit class
    #
    # @return   the process order
    #
    def getUnitProcessOrder (self, UnitClass, UnitID):
        """Gets the process order of an unit.

Keyword arguments:
UnitClass  -- an unit class
UnitID  -- an unit id for this unit class

Returns:
the process order
"""
        return pyopenfluid.PyOpenFLUID.getUnitProcessOrder(self, UnitClass,
            UnitID)


# ########################################################################## #
# ########################################################################## #


    ##
    # Gets children units of an unit.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 1\, 1)}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 2\, 1)}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.getUnitsParents(\"SU\"\, 1)) == 0}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.getUnitsParents(\"SU\"\, 2)) == 0}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.@HLImportant{getUnitsChildren}(\"SU\"\, 1)) == 0}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.@HLImportant{getUnitsChildren}(\"SU\"\, 2)) == 0}
    #   @LineExSimple{obj.addUnitChild(\"SU\"\, 1\, \"SU\"\, 2)}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.getUnitsParents(\"SU\"\, 1)) == 0}
    #   @LineExSimple{@HLReserv{assert} obj.getUnitsParents(\"SU\"\, 2) == [(\"SU\"\, 1)]}
    #   @LineExSimple{@HLReserv{assert} obj.@HLImportant{getUnitsChildren}(\"SU\"\, 1) == [(\"SU\"\, 2)]}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.@HLImportant{getUnitsChildren}(\"SU\"\, 2)) == 0}
    #   @LineExSimple{obj.removeUnitChild(\"SU\"\, 1\, \"SU\"\, 2)}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.getUnitsParents(\"SU\"\, 2)) == 0}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.@HLImportant{getUnitsChildren}(\"SU\"\, 1)) == 0}
    # @EndExample
    #
    # @param UnitClass   an unit class
    # @param UnitID      an unit id for this unit class
    #
    # @return   a list of tuple of units classes and units
    #
    def getUnitsChildren (self, UnitClass, UnitID):
        """Gets children units of an unit.

Keyword arguments:
UnitClass  -- an unit class
UnitID  -- an unit id for this unit class

Returns:
a list of tuple of units classes and units
"""
        return pyopenfluid.PyOpenFLUID.getUnitsChildren(self, UnitClass,
            UnitID)


# ########################################################################## #
# ########################################################################## #


    ##
    # Gets parents units of an unit.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 1\, 1)}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 2\, 1)}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.@HLImportant{getUnitsParents}(\"SU\"\, 1)) == 0}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.@HLImportant{getUnitsParents}(\"SU\"\, 2)) == 0}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.getUnitsChildren(\"SU\"\, 1)) == 0}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.getUnitsChildren(\"SU\"\, 2)) == 0}
    #   @LineExSimple{obj.addUnitChild(\"SU\"\, 1\, \"SU\"\, 2)}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.@HLImportant{getUnitsParents}(\"SU\"\, 1)) == 0}
    #   @LineExSimple{@HLReserv{assert} obj.@HLImportant{getUnitsParents}(\"SU\"\, 2) == [(\"SU\"\, 1)]}
    #   @LineExSimple{@HLReserv{assert} obj.getUnitsChildren(\"SU\"\, 1) == [(\"SU\"\, 2)]}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.getUnitsChildren(\"SU\"\, 2)) == 0}
    #   @LineExSimple{obj.removeUnitChild(\"SU\"\, 1\, \"SU\"\, 2)}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.@HLImportant{getUnitsParents}(\"SU\"\, 2)) == 0}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.getUnitsChildren(\"SU\"\, 1)) == 0}
    # @EndExample
    #
    # @param UnitClass   an unit class
    # @param UnitID      an unit id for this unit class
    #
    # @return   a list of tuple of units classes and units
    #
    def getUnitsParents (self, UnitClass, UnitID):
        """Gets parents units of an unit.

Keyword arguments:
UnitClass  -- an unit class
UnitID  -- an unit id for this unit class

Returns:
a list of tuple of units classes and units
"""
        return pyopenfluid.PyOpenFLUID.getUnitsParents(self, UnitClass,
            UnitID)


# ########################################################################## #
# ########################################################################## #


    ##
    # Adds a child on an unit.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 1\, 1)}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 2\, 1)}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.getUnitsParents(\"SU\"\, 1)) == 0}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.getUnitsParents(\"SU\"\, 2)) == 0}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.getUnitsChildren(\"SU\"\, 1)) == 0}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.getUnitsChildren(\"SU\"\, 2)) == 0}
    #   @LineExSimple{obj.@HLImportant{addUnitChild}(\"SU\"\, 1\, \"SU\"\, 2)}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.getUnitsParents(\"SU\"\, 1)) == 0}
    #   @LineExSimple{@HLReserv{assert} obj.getUnitsParents(\"SU\"\, 2) == [(\"SU\"\, 1)]}
    #   @LineExSimple{@HLReserv{assert} obj.getUnitsChildren(\"SU\"\, 1) == [(\"SU\"\, 2)]}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.getUnitsChildren(\"SU\"\, 2)) == 0}
    #   @LineExSimple{obj.removeUnitChild(\"SU\"\, 1\, \"SU\"\, 2)}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.getUnitsParents(\"SU\"\, 2)) == 0}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.getUnitsChildren(\"SU\"\, 1)) == 0}
    # @EndExample
    #
    # @param UnitClassParent   an unit class (parent)
    # @param UnitIDParent      an unit id (parent)
    # @param UnitClassChild    an unit class (child)
    # @param UnitIDChild       an unit id (child)
    #
    def addUnitChild (self, UnitClassParent, UnitIDParent, UnitClassChild,
                      UnitIDChild):
        """Adds a child on an unit.

Keyword arguments:
UnitClassParent  -- an unit class (parent)
UnitIDParent     -- an unit id (parent)
UnitClassChild   -- an unit class (child)
UnitIDChild      -- an unit id (child)
"""
        return pyopenfluid.PyOpenFLUID.addUnitChild(self, UnitClassParent,
            UnitIDParent, UnitClassChild, UnitIDChild)


# ########################################################################## #
# ########################################################################## #


    ##
    # Removes a child of an unit.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 1\, 1)}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 2\, 1)}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.getUnitsParents(\"SU\"\, 1)) == 0}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.getUnitsParents(\"SU\"\, 2)) == 0}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.getUnitsChildren(\"SU\"\, 1)) == 0}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.getUnitsChildren(\"SU\"\, 2)) == 0}
    #   @LineExSimple{obj.addUnitChild(\"SU\"\, 1\, \"SU\"\, 2)}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.getUnitsParents(\"SU\"\, 1)) == 0}
    #   @LineExSimple{@HLReserv{assert} obj.getUnitsParents(\"SU\"\, 2) == [(\"SU\"\, 1)]}
    #   @LineExSimple{@HLReserv{assert} obj.getUnitsChildren(\"SU\"\, 1) == [(\"SU\"\, 2)]}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.getUnitsChildren(\"SU\"\, 2)) == 0}
    #   @LineExSimple{obj.@HLImportant{removeUnitChild}(\"SU\"\, 1\, \"SU\"\, 2)}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.getUnitsParents(\"SU\"\, 2)) == 0}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{len}(obj.getUnitsChildren(\"SU\"\, 1)) == 0}
    # @EndExample
    #
    # @param UnitClassParent   an unit class (parent)
    # @param UnitIDParent      an unit id (parent)
    # @param UnitClassChild    an unit class (child)
    # @param UnitIDChild       an unit id (child)
    #
    def removeUnitChild (self, UnitClassParent, UnitIDParent, UnitClassChild,
                         UnitIDChild):
        """Removes a child of an unit.

Keyword arguments:
UnitClassParent  -- an unit class (parent)
UnitIDParent     -- an unit id (parent)
UnitClassChild   -- an unit class (child)
UnitIDChild      -- an unit id (child)
"""
        return pyopenfluid.PyOpenFLUID.removeUnitChild(self, UnitClassParent,
            UnitIDParent, UnitClassChild, UnitIDChild)


# ########################################################################## #
# ########################################################################## #


    ##
    # Creates an inputdata for alla spatial units of a class\,
    #  initialized with a default value.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 1\, 1)}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 2\, 1)}
    #   @LineExSimple{obj.@HLImportant{createInputData}(\"SU\"\, \"area\"\, \"1.0\")}
    #   @LineExSimple{@HLReserv{assert} obj.getInputData(\"SU\"\, 1\, \"area\") == \"1.0\"}
    #   @LineExSimple{@HLReserv{assert} obj.getInputData(\"SU\"\, 2\, \"area\") == \"1.0\"}
    #   @LineExSimple{obj.setInputData(\"SU\"\, 1\, \"area\"\, \"162\")}
    #   @LineExSimple{@HLReserv{assert} obj.getInputData(\"SU\"\, 1\, \"area\") == \"162\"}
    #   @LineExSimple{@HLReserv{assert} obj.getInputData(\"SU\"\, 2\, \"area\") == \"1.0\"}
    #   @LineExSimple{obj.removeInputData(\"SU\"\, \"area\")}
    #   @LineExSimple{@HLReserv{assert} obj.getInputData(\\"SU\\"\, 1\, \\"area\\") @HLReserv{is} @HLValue{None}}
    #   @LineExSimple{@HLReserv{assert} obj.getInputData(\\"SU\\"\, 2\, \\"area\\") @HLReserv{is} @HLValue{None}}
    # @EndExample
    #
    # @param UnitClass   the unit class
    # @param IDataName   the inputdata name
    # @param IDataVal    the default inputdata value for alla units
    #
    def createInputData (self, UnitClass, IDataName, IDataVal):
        """Creates an inputdata for alla spatial units of a class, initialized with a default value.

Keyword arguments:
UnitClass  -- the unit class
IDataName  -- the inputdata name
IDataVal   -- the default inputdata value for alla units
"""
        return pyopenfluid.PyOpenFLUID.createInputData(self, UnitClass,
            IDataName, IDataVal)


# ########################################################################## #
# ########################################################################## #


    ##
    # Returns an inputdata value for a given spatial unit.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 1\, 1)}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 2\, 1)}
    #   @LineExSimple{obj.createInputData(\"SU\"\, \"area\"\, \"1.0\")}
    #   @LineExSimple{@HLReserv{assert} obj.@HLImportant{getInputData}(\"SU\"\, 1\, \"area\") == \"1.0\"}
    #   @LineExSimple{@HLReserv{assert} obj.@HLImportant{getInputData}(\"SU\"\, 2\, \"area\") == \"1.0\"}
    #   @LineExSimple{obj.setInputData(\"SU\"\, 1\, \"area\"\, \"162\")}
    #   @LineExSimple{@HLReserv{assert} obj.@HLImportant{getInputData}(\"SU\"\, 1\, \"area\") == \"162\"}
    #   @LineExSimple{@HLReserv{assert} obj.@HLImportant{getInputData}(\"SU\"\, 2\, \"area\") == \"1.0\"}
    #   @LineExSimple{obj.removeInputData(\"SU\"\, \"area\")}
    #   @LineExSimple{@HLReserv{assert} obj.@HLImportant{getInputData}(\\"SU\\"\, 1\, \\"area\\") @HLReserv{is} @HLValue{None}}
    #   @LineExSimple{@HLReserv{assert} obj.@HLImportant{getInputData}(\\"SU\\"\, 2\, \\"area\\") @HLReserv{is} @HLValue{None}}
    # @EndExample
    #
    # @param UnitClass   the unit class
    # @param UnitID      the unit
    # @param IDataName   the inputdata name
    #
    # @return   the inputdata value
    #
    def getInputData (self, UnitClass, UnitID, IDataName):
        """Returns an inputdata value for a given spatial unit.

Keyword arguments:
UnitClass  -- the unit class
UnitID     -- the unit
IDataName  -- the name of the inputdata

Returns:
the inputdata value
"""
        return pyopenfluid.PyOpenFLUID.getInputData(self, UnitClass,
            UnitID, IDataName)


# ########################################################################## #
# ########################################################################## #


    ##
    # Sets an inputdata value for a given spatial unit.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 1\, 1)}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 2\, 1)}
    #   @LineExSimple{obj.createInputData(\"SU\"\, \"area\"\, \"1.0\")}
    #   @LineExSimple{@HLReserv{assert} obj.getInputData(\"SU\"\, 1\, \"area\") == \"1.0\"}
    #   @LineExSimple{@HLReserv{assert} obj.getInputData(\"SU\"\, 2\, \"area\") == \"1.0\"}
    #   @LineExSimple{obj.@HLImportant{setInputData}(\"SU\"\, 1\, \"area\"\, \"162\")}
    #   @LineExSimple{@HLReserv{assert} obj.getInputData(\"SU\"\, 1\, \"area\") == \"162\"}
    #   @LineExSimple{@HLReserv{assert} obj.getInputData(\"SU\"\, 2\, \"area\") == \"1.0\"}
    #   @LineExSimple{obj.removeInputData(\"SU\"\, \"area\")}
    #   @LineExSimple{@HLReserv{assert} obj.getInputData(\\"SU\\"\, 1\, \\"area\\") @HLReserv{is} @HLValue{None}}
    #   @LineExSimple{@HLReserv{assert} obj.getInputData(\\"SU\\"\, 2\, \\"area\\") @HLReserv{is} @HLValue{None}}
    # @EndExample
    #
    # @param UnitClass   the unit class
    # @param UnitID      the unit
    # @param IDataName   the inputdata name
    # @param IDataVal    the value of the inputdata
    #
    def setInputData (self, UnitClass, UnitID, IDataName, IDataVal):
        """Sets an inputdata value for a given spatial unit.

Keyword arguments:
UnitClass  -- the unit class
UnitID     -- the unit ID
IDataName  -- the name of the inputdata
IDataVal   -- the value of the inputdata
"""
        return pyopenfluid.PyOpenFLUID.setInputData(self, UnitClass, UnitID,
            IDataName, IDataVal)


# ########################################################################## #
# ########################################################################## #


    ##
    # Removes an inputdata value for a given spatial unit.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 1\, 1)}
    #   @LineExSimple{obj.addUnit(\"SU\"\, 2\, 1)}
    #   @LineExSimple{obj.createInputData(\"SU\"\, \"area\"\, \"1.0\")}
    #   @LineExSimple{@HLReserv{assert} obj.getInputData(\"SU\"\, 1\, \"area\") == \"1.0\"}
    #   @LineExSimple{@HLReserv{assert} obj.getInputData(\"SU\"\, 2\, \"area\") == \"1.0\"}
    #   @LineExSimple{obj.setInputData(\"SU\"\, 1\, \"area\"\, \"162\")}
    #   @LineExSimple{@HLReserv{assert} obj.getInputData(\"SU\"\, 1\, \"area\") == \"162\"}
    #   @LineExSimple{@HLReserv{assert} obj.getInputData(\"SU\"\, 2\, \"area\") == \"1.0\"}
    #   @LineExSimple{obj.@HLImportant{removeInputData}(\"SU\"\, \"area\")}
    #   @LineExSimple{@HLReserv{assert} obj.getInputData(\\"SU\\"\, 1\, \\"area\\") @HLReserv{is} @HLValue{None}}
    #   @LineExSimple{@HLReserv{assert} obj.getInputData(\\"SU\\"\, 2\, \\"area\\") @HLReserv{is} @HLValue{None}}
    # @EndExample
    #
    # @param UnitClass   the unit class
    # @param IDataName   the inputdata name
    #
    def removeInputData (self\, UnitClass, IDataName):
        """Removes an inputdata value for a given spatial unit.

Keyword arguments:
UnitClass  -- the unit class
IDataName  -- the name of the inputdata
"""
        return pyopenfluid.PyOpenFLUID.removeInputData(self, UnitClass,
            IDataName)


# ########################################################################## #
# ###############            INPUT OUTPUT FUNCTIONS          ############### #


    ##
    # Opens a dataset and returns a simulation definition class (self).
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{otherClass = obj.@HLImportant{openDataset}(\"/path/to/dataset\")}
    #   @LineExSimple{@HLReserv{assert} obj != otherClass}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{isinstance}(otherClass\, PyOpenFLUID)}
    # @EndExample
    #
    # @param Path   the full path of the dataset to open
    #
    # @return   a simulation definition class (PyOpenFLUID)
    #
    def openDataset (self, Path):
        """Opens a dataset and returns a simulation definition class (self).

Keyword arguments:
Path  -- the full path of the dataset to open

Returns:
a simulation definition class (PyOpenFLUID)
"""
        Res = pyopenfluid.PyOpenFLUID.openDataset(self, Path)
        if not Res is None and isinstance(Res, pyopenfluid.PyOpenFLUID):
            Class = PyOpenFLUID()
            pyopenfluid._copy(Res, Class)
            return Class
        return None


# ########################################################################## #
# ########################################################################## #


    ##
    # Opens a project and returns a simulation definition class (PyOpenFLUID).
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{otherClass = obj.@HLImportant{openProject}(\"/path/to/project\")}
    #   @LineExSimple{@HLReserv{assert} obj != otherClass}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{isinstance}(otherClass\, PyOpenFLUID)}
    # @EndExample
    #
    # @param Path   the full path of the project to open
    #
    # @return   a simulation definition class (PyOpenFLUID)
    #
    def openProject (self, Path):
        """Opens a project and returns a simulation definition class (PyOpenFLUID).

Keyword arguments:
Path  -- the full path of the project to open

Returns:
a simulation definition class (PyOpenFLUID)
"""
        Res = pyopenfluid.PyOpenFLUID.openProject(self, Path)
        if not Res is None and isinstance(Res, pyopenfluid.PyOpenFLUID):
            Class = PyOpenFLUID()
            pyopenfluid._copy(Res, Class)
            return Class
        return None


# ########################################################################## #
# ########################################################################## #


    ##
    # Sets the current output directory for simulations.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.@HLImportant{setCurrentOutputDir}(\"/path/to/output\")}
    #   @LineExSimple{path = obj.getCurrentOutputDir()}
    #   @LineExSimple{@HLReserv{print} path}
    #   @LineExResult{\"/path/to/output\"}
    # @EndExample
    #
    # @param Path   the output directory path
    #
    def setCurrentOutputDir (self, Path):
        """Sets the current output directory for simulations.

Keyword arguments:
Path  -- the output directory path
"""
        pyopenfluid.PyOpenFLUID.setCurrentOutputDir(self, Path)


# ########################################################################## #
# ########################################################################## #


    ##
    # Gets the current output directory for simulations.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.setCurrentOutputDir(\"/path/to/output\")}
    #   @LineExSimple{path = obj.@HLImportant{getCurrentOutputDir}()}
    #   @LineExSimple{@HLReserv{print} path}
    #   @LineExResult{\"/path/to/output\"}
    # @EndExample
    #
    # @return   the output directory path
    #
    def getCurrentOutputDir (self):
        """Gets the current output directory for simulations.

Returns:
the output directory path
"""
        return pyopenfluid.PyOpenFLUID.getCurrentOutputDir(self)


# ########################################################################## #
# ###############             SIMULATION FUNCTIONS           ############### #


    ##
    # Returns the simulation time step.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.setDefaultDeltaT(60)}
    #   @LineExSimple{deltat = obj.@HLImportant{getDefaultDeltaT}()}
    #   @LineExSimple{@HLReserv{print} deltat}
    #   @LineExResult{60}
    # @EndExample
    #
    # @return   the time step value in seconds
    #
    def getDefaultDeltaT (self):
        """Returns the simulation time step.

Returns:
the time step value in seconds
"""
        return pyopenfluid.PyOpenFLUID.getDefaultDeltaT(self)


# ########################################################################## #
# ########################################################################## #


    ##
    # Sets the simulation time step.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.@HLImportant{setDefaultDeltaT}(60)}
    #   @LineExSimple{deltat = obj.getDefaultDeltaT()}
    #   @LineExSimple{@HLReserv{print} deltat}
    #   @LineExResult{60}
    # @EndExample
    #
    # @param DefaultDeltaT   the time step value in seconds
    #
    def setDefaultDeltaT (self, DefaultDeltaT):
        """Sets the simulation time step.

Keyword arguments:
DefaultDeltaT  -- the time step value in seconds
"""
        pyopenfluid.PyOpenFLUID.setDefaultDeltaT(self, DefaultDeltaT)


# ########################################################################## #
# ########################################################################## #


    ##
    # Returns the simulation period begin date.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.setPeriodBeginDate(\"1997-06-05 04:00:00\")}
    #   @LineExSimple{bdate = obj.@HLImportant{getPeriodBeginDate}()}
    #   @LineExSimple{@HLReserv{print} bdate}
    #   @LineExSimple{\"1997-06-05 04:00:00\"}
    # @EndExample
    #
    # @return   the begin date as an ISO datetime string (%Y-%m-%d %H:%M:%S)
    #
    def getPeriodBeginDate (self):
        """Returns the simulation period begin date.

Returns:
the begin date as an ISO datetime string (%Y-%m-%d %H:%M:%S)
"""
        return pyopenfluid.PyOpenFLUID.getPeriodBeginDate(self)


# ########################################################################## #
# ########################################################################## #


    ##
    # Returns the simulation period end date.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.setPeriodEndDate(\"1997-06-05 04:00:00\")}
    #   @LineExSimple{bdate = obj.@HLImportant{getPeriodEndDate}()}
    #   @LineExSimple{@HLReserv{print} bdate}
    #   @LineExResult{\"1997-06-05 04:00:00\"}
    # @EndExample
    #
    # @return   the end date as an ISO datetime string (%Y-%m-%d %H:%M:%S)
    #
    def getPeriodEndDate (self):
        """Returns the simulation period end date.

Returns:
the end date as an ISO datetime string (%Y-%m-%d %H:%M:%S)
"""
        return pyopenfluid.PyOpenFLUID.getPeriodEndDate(self)


# ########################################################################## #
# ########################################################################## #


    ##
    # Sets the simulation period begin date.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.@HLImportant{setPeriodBeginDate}(\"1997-06-05 04:00:00\")}
    #   @LineExSimple{bdate = obj.getPeriodBeginDate()}
    #   @LineExSimple{@HLReserv{print} bdate}
    #   @LineExSimple{\"1997-06-05 04:00:00\"}
    # @EndExample
    #
    # @param BeginDate   the begin date as an ISO datetime string (%Y-%m-%d %H:%M:%S)
    #
    def setPeriodBeginDate (self, BeginDate):
        """Sets the simulation period begin date.

  Keyword arguments:
  BeginDate  -- the begin date as an ISO datetime string (%Y-%m-%d %H:%M:%S)
"""
        return pyopenfluid.PyOpenFLUID.setPeriodBeginDate(self, BeginDate)


# ########################################################################## #
# ########################################################################## #


    ##
    # Sets the simulation period end date.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{obj.@HLImportant{setPeriodEndDate}(\"1997-06-05 04:00:00\")}
    #   @LineExSimple{bdate = obj.getPeriodEndDate()}
    #   @LineExSimple{@HLReserv{print} bdate}
    #   @LineExResult{\"1997-06-05 04:00:00\"}
    # @EndExample
    #
    # @param EndDate   the end date as an ISO datetime string (%Y-%m-%d %H:%M:%S)
    #
    def setPeriodEndDate (self, EndDate):
        """Sets the simulation period end date.

Keyword arguments:
EndDate  -- the end date as an ISO datetime string (%Y-%m-%d %H:%M:%S)
"""
        return pyopenfluid.PyOpenFLUID.setPeriodEndDate(self, EndDate)


# ########################################################################## #
# ########################################################################## #


    ##
    # Runs a project and returns a simulation definition class (PyOpenFLUID).
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{ofsim = obj.@HLImportant{runProject}(\"/path/to/dataset\")}
    #   @LineExSimple{@HLReserv{assert} obj != ofsim}
    #   @LineExSimple{@HLReserv{assert} not (obj is ofsim)}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{isinstance}(ofsim\, PyOpenFLUID)}
    # @EndExample
    #
    # @param Path   the full path of the project to open
    #
    # @return   a simulation definition class (PyOpenFLUID)
    #
    def runProject (self, Path):
        """Runs a project and returns a simulation definition class (PyOpenFLUID).

Keyword arguments:
Path  -- the full path of the project to open

Returns:
a simulation definition class (PyOpenFLUID)
"""
        Res = pyopenfluid.PyOpenFLUID.runProject(self, Path)
        if not Res is None and isinstance(Res, pyopenfluid.PyOpenFLUID):
            Class = PyOpenFLUID()
            pyopenfluid._copy(Res, Class)
            return Class
        return None


# ########################################################################## #
# ########################################################################## #


    ##
    # Runs a project from a simulation definition class (PyOpenFLUID).
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{... @LineExComment{ open a project or configure the simulation}}
    #   @LineExSimple{res = obj.@HLImportant{runSimulation}()}
    #   @LineExSimple{@HLReserv{assert} @HLSpecial{isinstance}(res\, bool)}
    # @EndExample
    #
    # @return   True if the simulation is runned without problems, False otherwise
    #
    def runSimulation (self):
        """Runs a simulation from a simulation definition class (self).

Returns:
True if the simulation is runned without problems, False otherwise
"""
        return bool(pyopenfluid.PyOpenFLUID.runSimulation(self))


# ########################################################################## #
# ########################################################################## #


    # #
    # Loads results as a dataframe, giving output dataset informations.
    #
    # @param UnitClass   the unit class
    # @param UnitID      the unit ID
    # @param Suffix      the output dataset suffix
    #
    # @return   a dataframe containing the simulation results
    #
#    def loadResult (self, UnitClass, UnitID, Suffix):
#        """Loads results as a dataframe, giving output dataset informations.

#Keyword arguments:
#UnitClass  -- the unit class
#UnitID     -- the unit ID
#Suffix     -- the output dataset suffix

#Returns:
#a dataframe containing the simulation results
#"""
#        return pyopenfluid.PyOpenFLUID.loadResult(self, UnitClass, UnitID,
#           Suffix)


# ########################################################################## #
# ########################################################################## #


    # #
    # Loads results as a dataframe, giving output file name.
    #
    # @param FilePath   the full path of the file to load
    #
    # @return   a dataframe containing the simulation results
    #
#    def loadResultFile (self, FilePath):
#        """Loads results as a dataframe, giving output file name.

#FilePath  -- the full path of the file to load

#Returns:
#a dataframe containing the simulation results
#"""
#        return pyopenfluid.PyOpenFLUID.loadResultFile(self, FilePath)


# ########################################################################## #
# ###                           OTHER FUNCTIONS                          ### #


# ########################################################################## #
# ###                     PYTHON specifics functions                     ### #


    ##
    # Return a description of the class.
    #
    # Examples: @StartExample
    #   @LineExSimple{obj = PyOpenFLUID()}
    #   @LineExSimple{v = @HLSpecial{str}(obj)}
    #   @LineExSimple{@HLReserv{print} obj}
    # @EndExample
    #
    # @return   a string representation
    #
    def __str__ (self):
        """Return a description of the class."""
        return "PyOpenFLUID({0})".format(self.getVersion())
