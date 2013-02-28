#!/bin/env/python
# -*- coding: UTF-8 -*-

"""This module allows to load, parameterize, run and analyse OpenFLUID
 simulations within the Python 2.x environment."""

__author__ = ["Bastien VAYSSE"]
__credits__ = ["Bastien VAYSSE <bastien.vaysse@supagro.inra.fr>", "Jean-Christophe FABRE <fabrejc@supagro.inra.fr>"]
__license__ = "GPLv3"
__version__ = "2.0.0~alpha"


# ########################################################################## #
# ###                                IMPORT                              ### #
# ########################################################################## #


try:
    import _pyopenfluid as pyopenfluid
except ImportError, msg:
    raise ImportError, str(msg) + ', please install the python-openfluid package'

__version__ = pyopenfluid.__version__


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
    def __init__ (self):
        """Create an OpenFLUID class."""
        pyopenfluid.PyOpenFLUID.__init__(self)


# ########################################################################## #
# ###############              GENERAL FUNCTIONS             ############### #


    ##
    # Returns the OpenFLUID version.
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
    def resetExtraFunctionsPaths (self):
        """Reset paths to search for simulation functions."""
        pyopenfluid.PyOpenFLUID.resetExtraFunctionsPaths(self)


# ########################################################################## #
# ########################################################################## #


    ##
    # Returns the added paths to search for simulation functions.
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
    def resetExtraObserversPaths (self):
        """Reset paths to search for observers."""
        pyopenfluid.PyOpenFLUID.resetExtraObserversPaths(self)


# ########################################################################## #
# ########################################################################## #


    ##
    # Returns the added paths to search for observers.
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
    def printSimulationInfo (self):
        """Prints informations to screen about simulation definition class (self)."""
        pyopenfluid.PyOpenFLUID.printSimulationInfo(self)


# ########################################################################## #
# ###############               MODEL FUNCTIONS              ############### #


    ##
    # Returns a function parameter value.
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
    # Returns a generator parameter value.
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
# ###############             MONITORING FUNCTIONS           ############### #


    ##
    # Returns an observer parameter value.
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
# ###############           SPATIAL DOMAIN FUNCTIONS         ############### #


    ##
    # Returns the existing units classes.
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
    # Creates an inputdata for alla spatial units of a class,
    #  initialized with a default value.
    #
    # @param UnitClass   the unit class
    # @param IDataName   the inputdata name
    # @param IDataVal    the default inputdata value for alla units
    #
    def createInputData (self, UnitClass, IDataName, IDataVal):
        """Creates an inputdata for alla spatial units of a class, initialized with a default value

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
# ###############            INPUT OUTPUT FUNCTIONS          ############### #


    ##
    # Opens a dataset and returns a simulation definition class (self).
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
            pyopenfluid.PyOpenFLUID._copy(Class, Res)
            return Class
        return None


# ########################################################################## #
# ########################################################################## #


    ##
    # Opens a project and returns a simulation definition class (PyOpenFLUID).
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
            pyopenfluid.PyOpenFLUID._copy(Class, Res)
            return Class
        return None


# ########################################################################## #
# ########################################################################## #


    ##
    # Sets the current output directory for simulations.
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
            pyopenfluid.PyOpenFLUID._copy(Class, Res)
            return Class
        return None


# ########################################################################## #
# ########################################################################## #


    ##
    # Runs a project from a simulation definition class (PyOpenFLUID).
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

#Keyword arguments:
#FilePath  -- the full path of the file to load

#Returns:
#a dataframe containing the simulation results
#"""
#        return pyopenfluid.PyOpenFLUID.loadResultFile(self, FilePath)


# ########################################################################## #
# ###                           OTHER FUNCTIONS                          ### #


    ##
    # Internal method.
    #
    def _copy (self):
        """Internal method."""
        raise PyOFError("Unavaible method : internal private method.")


# ########################################################################## #
# ###                     PYTHON specifics functions                     ### #


    ##
    # Return a description of the class.
    #
    # @return   a string representation
    #
    def __str__ (self):
        """Return a description of the classe."""
        return "PyOpenFLUID({0})".format(self.getVersion())
