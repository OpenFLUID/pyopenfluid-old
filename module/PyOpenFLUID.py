#!/bin/env/python
# -*- coding: UTF-8 -*-

"""This module allows to load, parameterize, run and analyse OpenFLUID
    simulations within the Python 2.x environment."""

__author__ = "Bastien Vaysse"
__copyright__ = "Copyright 2013, Creative Commons By-NC-ND license"
__credits__ = ["Bastien VAYSSE", "Jean-Christophe FABRE"]
__license__ = "GPLv3"
__version__ = "2.0.0~alpha"
__email__ = "bastien.vaysse@supagro.inra.fr"
__status__ = "Production"


# ########################################################################## #
# ###                                IMPORT                              ### #
# ########################################################################## #


try:
    import _pyopenfluid as pyopenfluid
    from PyOFExceptions import PyOFError
    from PyOFCheckMethods import *
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
    #
    def __init__ (self):
        """Create an OpenFLUID class."""
        try:
            pyopenfluid.PyOpenFLUID.__init__(self)
        except Exception as e:
            raise PyOFError(e.message)


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
        try:
            Version = pyopenfluid.PyOpenFLUID.getVersion(self)
        except Exception as e:
            raise PyOFError(e.message)
        else:
            return Version


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
        if PyOFCheckType((Paths,), str):
            try:
                pyopenfluid.PyOpenFLUID.addExtraFunctionsPaths(self, Paths)
            except Exception as e:
                raise PyOFError(e.message)
        else:
            raise PyOFError("'Paths' is not a string parameter")


# ########################################################################## #
# ########################################################################## #


    ##
    # Reset paths to search for simulation functions.
    #
    def resetExtraFunctionsPaths (self):
        """Reset paths to search for simulation functions."""
        try:
            pyopenfluid.PyOpenFLUID.resetExtraFunctionsPaths(self)
        except Exception as e:
            raise PyOFError(e.message)


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
        try:
            Paths = pyopenfluid.PyOpenFLUID.getExtraFunctionsPaths(self)
        except Exception as e:
            raise PyOFError(e.message)
        else:
            return Paths


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
        if PyOFCheckType((Paths,), str):
            try:
                pyopenfluid.PyOpenFLUID.addExtraObserversPaths(self, Paths)
            except Exception as e:
                raise PyOFError(e.message)
        else:
            raise PyOFError("'Paths' is not a string parameter")


# ########################################################################## #
# ########################################################################## #


    ##
    # Reset paths to search for observers.
    #
    def resetExtraObserversPaths (self):
        """Reset paths to search for observers."""
        try:
            pyopenfluid.PyOpenFLUID.resetExtraObserversPaths(self)
        except Exception as e:
            raise PyOFError(e.message)


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
        try:
            Paths = pyopenfluid.PyOpenFLUID.getExtraObserversPaths(self)
        except Exception as e:
            raise PyOFError(e.message)
        else:
            return Paths


# ########################################################################## #
# ########################################################################## #


    ##
    # Prints informations to screen about simulation definition class (self).
    #
    def printSimulationInfo (self):
        """Prints informations to screen about simulation definition class (self)."""
        try:
            pyopenfluid.PyOpenFLUID.printSimulationInfo(self)
        except Exception as e:
            raise PyOFError(e.message)


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
        if PyOFCheckType((FunID, ParamName), str):
            try:
                Value = pyopenfluid.PyOpenFLUID.getFunctionParam(self, FunID,
                                                                 ParamName)
            except Exception as e:
                raise PyOFError(e.message)
            else:
                return Value
        else:
            raise PyOFError("'FunID' or 'ParamName' is not a string parameter")


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
        if PyOFCheckType((FunID, ParamName, ParamValue), str):
            try:
                pyopenfluid.PyOpenFLUID.setFunctionParam(self, FunID, ParamName,
                                                     ParamValue)
            except Exception as e:
                raise PyOFError(e.message)
        else:
            raise PyOFError("'FunID', 'ParamName' or 'ParamValue' is not a string parameter")


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
        if PyOFCheckType((UnitClass,VarName,ParamName), str):
            try:
                Value = pyopenfluid.PyOpenFLUID.getGeneratorParam(self, UnitClass,
                                                                  VarName, ParamName)
            except Exception as e:
                raise PyOFError(e.message)
            else:
                return Value
        else:
            raise PyOFError("'UnitClass', 'VarName' or 'ParamName' is not a string parameter")


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
        if PyOFCheckType((UnitClass,VarName,ParamName,ParamValue), str):
            try:
                pyopenfluid.PyOpenFLUID.setGeneratorParam(self, UnitClass, VarName,
                                                          ParamName, ParamValue)
            except Exception as e:
                raise PyOFError(e.message)
        else:
            raise PyOFError("'UnitClass', 'VarName', 'ParamName' or 'ParamValue' is not a string parameter")


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
        if PyOFCheckType((ParamName,), str):
            try:
                Value = pyopenfluid.PyOpenFLUID.getModelGlobalParam(self, ParamName)
            except Exception as e:
                raise PyOFError(e.message)
            else:
                return Value
        else:
            raise PyOFError("'ParamName' is not a string parameter")


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
        if PyOFCheckType((ParamName,ParamValue), str):
            try:
                pyopenfluid.PyOpenFLUID.setModelGlobalParam(self, ParamName,
                                                            ParamValue)
            except Exception as e:
                raise PyOFError(e.message)
        else:
            raise PyOFError("'ParamName' or 'ParamValue' is not a string parameter")


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
        try:
            Value = pyopenfluid.PyOpenFLUID.getObserverParam(self, ObsID,
                                                             ParamName)
        except Exception as e:
            raise PyOFError(e.message)
        else:
            return Value


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
        try:
            pyopenfluid.PyOpenFLUID.setObserverParam(self, ObsID, ParamName,
                                                     ParamValue)
        except Exception as e:
            raise PyOFError(e.message)


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
        try:
            List = pyopenfluid.PyOpenFLUID.getUnitsClasses(self)
        except Exception as e:
            raise PyOFError(e.message)
        else:
            return List


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
        if PyOFCheckType((UnitClass,), str):
            try:
                List = pyopenfluid.PyOpenFLUID.getUnitsIDs(self, UnitClass)
            except Exception as e:
                raise PyOFError(e.message)
            else:
                return List
        else:
            raise PyOFError("'UnitClass' is not a string parameter")


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
        if PyOFCheckType((UnitClass, IDataName, IDataVal), str):
            try:
                pyopenfluid.PyOpenFLUID.createInputData(self, UnitClass, IDataName,
                                                        IDataVal)
            except Exception as e:
                raise PyOFError(e.message)
        else:
            raise PyOFError("'UnitClass', 'IDataName' or 'IDataVal' is not a string parameter")


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
        if PyOFCheckType((UnitClass, IDataName), str) and PyOFCheckType((UnitID,), int):
            try:
                Value = pyopenfluid.PyOpenFLUID.getInputData(self, UnitClass,
                                                             UnitID, IDataName)
            except Exception as e:
                raise PyOFError(e.message)
            else:
                return Value
        else:
            raise PyOFError("'UnitClass' or 'IDataName' is not a string parameter, or 'UnitID' is not an integer parameter")


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
        if PyOFCheckType((UnitClass, IDataName, IDataVal), str) and PyOFCheckType((UnitID,), int):
            try:
                pyopenfluid.PyOpenFLUID.setInputData(self, UnitClass, UnitID,
                                                     IDataName, IDataVal)
            except Exception as e:
                raise PyOFError(e.message)
        else:
            raise PyOFError("'UnitClass', 'IDataName' or 'IDataVal' is not a string parameter, or 'UnitID' is not an integer parameter")


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
        if PyOFCheckType((Path,), str):
            try:
                Class = None
                Res = pyopenfluid.PyOpenFLUID.openDataset(self, Path)
                if not Res is None and isinstance(Res, pyopenfluid.PyOpenFLUID):
                    Class = PyOpenFLUID()
                    pyopenfluid.PyOpenFLUID.copy(Class, Res)
                    del Res
            except Exception as e:
                raise PyOFError(e.message)
            else:
                return Class
        else:
            raise PyOFError("'Path' is not a string parameter")


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
        if PyOFCheckType((Path,), str):
            try:
                Class = None
                Res = pyopenfluid.PyOpenFLUID.openProject(self, Path)
                if not Res is None and isinstance(Res, pyopenfluid.PyOpenFLUID):
                    Class = PyOpenFLUID()
                    pyopenfluid.PyOpenFLUID.copy(Class, Res)
                    del Res
            except Exception as e:
                raise PyOFError(e.message)
            else:
                return Class
        else:
            raise PyOFError("'Path' is not a string parameter")


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
        if PyOFCheckType((Path,), str):
            try:
                pyopenfluid.PyOpenFLUID.setCurrentOutputDir(self, Path)
            except Exception as e:
                raise PyOFError(e.message)
        else:
            raise PyOFError("'Paths' is not a string parameter")


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
        try:
            Path = pyopenfluid.PyOpenFLUID.getCurrentOutputDir(self)
        except Exception as e:
            raise PyOFError(e.message)
        else:
            return Path


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
        try:
            DeltaT = pyopenfluid.PyOpenFLUID.getDefaultDeltaT(self)
        except Exception as e:
            raise PyOFError(e.message)
        else:
            return DeltaT


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
        if PyOFCheckType((DefaultDeltaT,), int):
            try:
                pyopenfluid.PyOpenFLUID.setDefaultDeltaT(self, DefaultDeltaT)
            except Exception as e:
                raise PyOFError(e.message)
        else:
            raise PyOFError("'DefaultDeltaT' is not an integer parameter")


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
        try:
            DictDate = pyopenfluid.PyOpenFLUID.getPeriodBeginDate(self)
            StrDate = "%s-%s-%s %s:%s:%s" % (
                str(DictDate["year"]), str(DictDate["month"]).zfill(2),
                str(DictDate["day"]).zfill(2), str(DictDate["hour"]).zfill(2),
                str(DictDate["minute"]).zfill(2), str(DictDate["second"]).zfill(2))
        except Exception as e:
            raise PyOFError(e.message)
        else:
            return StrDate


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
        try:
            DictDate = pyopenfluid.PyOpenFLUID.getPeriodEndDate(self)
            StrDate = "%s-%s-%s %s:%s:%s" % (
                str(DictDate["year"]), str(DictDate["month"]).zfill(2),
                str(DictDate["day"]).zfill(2), str(DictDate["hour"]).zfill(2),
                str(DictDate["minute"]).zfill(2), str(DictDate["second"]).zfill(2))
        except Exception as e:
            raise PyOFError(e.message)
        else:
            return StrDate


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
        if PyOFCheckType((BeginDate,), str):
            DictDate = PyOFExtractDate(BeginDate)
            if DictDate is False:
                raise PyOFError("Bad entry for the begin date of the simulation period.")
            try:
                pyopenfluid.PyOpenFLUID.setPeriodBeginDate(self, DictDate["year"],
                    DictDate["month"], DictDate["day"], DictDate["hour"],
                    DictDate["minute"], DictDate["second"])
            except Exception as e:
                raise PyOFError(e.message)
        else:
            raise PyOFError("'BeginDate' is not a string parameter")


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
        if PyOFCheckType((EndDate,), str):
            DictDate = PyOFExtractDate(EndDate)
            if DictDate is False:
                raise PyOFError("Bad entry for the end date of the simulation period.")
            try:
                pyopenfluid.PyOpenFLUID.setPeriodEndDate(self, DictDate["year"],
                    DictDate["month"], DictDate["day"], DictDate["hour"],
                    DictDate["minute"], DictDate["second"])
            except Exception as e:
                raise PyOFError(e.message)
        else:
            raise PyOFError("'EndDate' is not a string parameter")


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
        if PyOFCheckType((Path,), str):
            try:
                Class = None
                Res = pyopenfluid.PyOpenFLUID.runProject(self, Path)
                if not Res is None and isinstance(Res, pyopenfluid.PyOpenFLUID):
                    Class = PyOpenFLUID()
                    pyopenfluid.PyOpenFLUID.copy(Class, Res)
                    del Res
                else:
                    Res = None
            except Exception as e:
                raise PyOFError(e.message)
            else:
                return Class
        else:
            raise PyOFError("'Path' is not a string parameter")


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
        try:
            return bool(pyopenfluid.PyOpenFLUID.runSimulation(self))
        except Exception as e:
            raise PyOFError(e.message)


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
#        try:
#            Data = pyopenfluid.PyOpenFLUID.loadResult(self, UnitClass, UnitID,
#                                                      Suffix)
#        except Exception as e:
#            raise PyOFError(e.message)
#        else:
#            return Data


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
#        try:
#            Data = pyopenfluid.PyOpenFLUID.loadResultFile(self, FilePath)
#        except Exception as e:
#            raise PyOFError(e.message)
#        else:
#            return Data


# ########################################################################## #
# ###                           OTHER FUNCTIONS                          ### #


    ##
    # Internal method.
    #
    def copy (self):
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
        try:
            Desc = "PyOpenFLUID(" + str( self.getVersion() ) + ")"
        except Exception as e:
            raise PyOFError(e.message)
        else:
            return Desc
