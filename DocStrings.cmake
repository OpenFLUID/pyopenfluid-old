#
# CMake build for PyOpenFLUID
#
# Author : Bastien VAYSSE <bastien.vaysse@supagro.inra.fr>
#


SET(DOCSTRINGRAW_GETVERSION
"Return a description of the class.

Returns:
A string representation of the class.

Examples:
>>> obj = PyOpenFLUID()
>>> info = str(obj)")


SET(DOCSTRINGRAW_ADDEXTRAFUNCTIONSPATHS
"Adds paths to search for simulation functions.

Keyword arguments:
Paths  -- the semicolon separated paths to add")


SET(DOCSTRINGRAW_RESETEXTRAFUNCTIONSPATHS
"Reset paths to search for simulation functions.")


SET(DOCSTRINGRAW_GETEXTRAFUNCTIONSPATHS
"Returns the added paths to search for simulation functions.

Returns:
a list of Paths")


SET(DOCSTRINGRAW_ADDEXTRAOBSERVERSPATHS
"Adds paths to search for observers.

Keyword arguments:
Paths  -- the semicolon separated paths to add")


SET(DOCSTRINGRAW_RESETEXTRAOBSERVERSPATHS
"Reset paths to search for observers.")


SET(DOCSTRINGRAW_GETEXTRAOBSERVERSPATHS
"Returns the added paths to search for observers.

Returns:
a list of Paths")


SET(DOCSTRINGRAW_PRINTSIMULATIONINFO
"Prints informations to screen about simulation definition class (self).")


SET(DOCSTRINGRAW_GETFUNCTIONPARAM
"Returns a function parameter value.

Keyword arguments:
FunID      -- the simulation function id
ParamName  -- the name of the parameter

Returns:
the parameter value")


SET(DOCSTRINGRAW_SETFUNCTIONPARAM
"Sets a function parameter value.

Keyword arguments:
FunID        -- the simulation function id
ParamName    -- the name of the parameter
ParamValue   -- the parameter value")


SET(DOCSTRINGRAW_REMOVEFUNCTIONPARAM
"Removes a function parameter value.

Keyword arguments:
FunID        -- the simulation function id
ParamName    -- the name of the parameter")


SET(DOCSTRINGRAW_GETFUNCTIONPARAMS
"Returns all functions parameters.

Keyword arguments:
FunID      -- the simulation function id

Returns:
a list of parameter")


SET(DOCSTRINGRAW_GETGENERATORPARAM
"Returns a generator parameter value.

Keyword arguments:
UnitClass  -- the unit class to which the generator is applied
VarName    -- the variable name to which the generator is applied
ParamName  -- the name of the parameter

Returns:
the parameter value")


SET(DOCSTRINGRAW_SETGENERATORPARAM
"Sets a generator parameter value.

Keyword arguments:
UnitClass   -- the unit class to which the generator is applied
VarName     -- the variable name to which the generator is applied
ParamName   -- the name of the parameter
ParamValue  -- the parameter value")


SET(DOCSTRINGRAW_GETMODELGLOBALPARAM
"Returns a model global parameter value.

Keyword arguments:
ParamName  -- the name of the parameter

Returns:
the parameter value")


SET(DOCSTRINGRAW_SETMODELGLOBALPARAM
"Sets a model global parameter value.

Keyword arguments:
ParamName   -- the name of the parameter
ParamValue  -- the parameter value")


SET(DOCSTRINGRAW_REMOVEMODELGLOBALPARAM
"Returns all model global parameter.

Keyword arguments:
ParamName   -- the name of the parameter")


SET(DOCSTRINGRAW_GETMODELGLOBALPARAMS
"Returns all model global parameter.

Returns:
a list of parameter name.")


SET(DOCSTRINGRAW_ADDFUNCTION
"Adds a function.

Keyword arguments:
FuncID   -- the simulation function id")


SET(DOCSTRINGRAW_REMOVEFUNCTION
"Removes a function.

Keyword arguments:
FuncID   -- the simulation function id")


SET(DOCSTRINGRAW_CLEARMODEL
"Removes all functions.")


SET(DOCSTRINGRAW_GETFUNCTIONSINMODEL
"Gets all functions names.

Returns:
a list of function name")


SET(DOCSTRINGRAW_GETOBSERVERPARAM
"Returns an observer parameter value.

Keyword arguments:
ObsID      -- the observer id
ParamName  -- the name of the parameter

Returns:
the parameter value")


SET(DOCSTRINGRAW_SETOBSERVERPARAM
"Sets an observer parameter value.

Keyword arguments:
ObsID       -- the observer id
ParamName   -- the name of the parameter
ParamValue  -- the parameter value")


SET(DOCSTRINGRAW_REMOVEOBSERVERPARAM
"Removes an observer parameter.

Keyword arguments:
ObsID       -- the observer id
ParamName   -- the name of the parameter")


SET(DOCSTRINGRAW_GETOBSERVERPARAMS
"Gets all observer parameters name.

Keyword arguments:
ObsID       -- the observer id

Returns:
a list of observer parameters name.")


SET(DOCSTRINGRAW_ADDOBSERVER
"Adds an observer.

Keyword arguments:
ObsID       -- the observer id")


SET(DOCSTRINGRAW_REMOVEOBSERVER
"Removes an observer.

Keyword arguments:
ObsID       -- the observer id")


SET(DOCSTRINGRAW_CLEARMONITORING
"Removes all observers.")


SET(DOCSTRINGRAW_GETOBSERVERSINMONITORING
"Gets all observer name.

Returns:
a list of observer name")


SET(DOCSTRINGRAW_GETUNITSCLASSES
"Returns the existing units classes.

Returns:
a list of units classes")


SET(DOCSTRINGRAW_GETUNITSIDS
"Returns the existing units IDs for a given units class.

Keyword arguments:
UnitClass  -- the unit class

Returns:
a list of units IDs")


SET(DOCSTRINGRAW_ADDUNIT
"Adds an new unit.

Keyword arguments:
UnitClass  -- an unit class
UnitID     -- an new unit id for this unit class
PcsOrder   -- a process order")


SET(DOCSTRINGRAW_REMOVEUNIT
"Removes an unit.

Keyword arguments:
UnitClass  -- an unit class
UnitID     -- an unit id for this unit class")


SET(DOCSTRINGRAW_CLEARUNITCLASS
"Removes all units from an unit class.

Keyword arguments:
UnitClass  -- an unit class")


SET(DOCSTRINGRAW_SETUNITPROCESSORDER
"Sets the process order of an unit.

Keyword arguments:
UnitClass  -- an unit class
UnitID     -- an unit id for this unit class
PcsOrder   -- a process order")


SET(DOCSTRINGRAW_GETUNITPROCESSORDER
"Gets the process order of an unit.

Keyword arguments:
UnitClass  -- an unit class
UnitID  -- an unit id for this unit class

Returns:
the process order")


SET(DOCSTRINGRAW_GETUNITSCHILDREN
"Gets children units of an unit.

Keyword arguments:
UnitClass  -- an unit class
UnitID  -- an unit id for this unit class

Returns:
a list of tuple of units classes and units")


SET(DOCSTRINGRAW_GETUNITSPARENTS
"Gets parents units of an unit.

Keyword arguments:
UnitClass  -- an unit class
UnitID  -- an unit id for this unit class

Returns:
a list of tuple of units classes and units")


SET(DOCSTRINGRAW_ADDPARENTCHILDCONNECTION
"Adds a child on an unit.

Keyword arguments:
UnitClassParent  -- an unit class (parent)
UnitIDParent     -- an unit id (parent)
UnitClassChild   -- an unit class (child)
UnitIDChild      -- an unit id (child)")


SET(DOCSTRINGRAW_REMOVEPARENTCHILDCONNECTION
"Removes a child of an unit.

Keyword arguments:
UnitClassParent  -- an unit class (parent)
UnitIDParent     -- an unit id (parent)
UnitClassChild   -- an unit class (child)
UnitIDChild      -- an unit id (child)")


SET(DOCSTRINGRAW_CREATEINPUTDATA
"Creates an inputdata for alla spatial units of a class, initialized with a default value.

Keyword arguments:
UnitClass  -- the unit class
IDataName  -- the inputdata name
IDataVal   -- the default inputdata value for alla units")


SET(DOCSTRINGRAW_GETINPUTDATA
"Returns an inputdata value for a given spatial unit.

Keyword arguments:
UnitClass  -- the unit class
UnitID     -- the unit
IDataName  -- the name of the inputdata

Returns:
the inputdata value")


SET(DOCSTRINGRAW_SETINPUTDATA
"Sets an inputdata value for a given spatial unit.

Keyword arguments:
UnitClass  -- the unit class
UnitID     -- the unit ID
IDataName  -- the name of the inputdata
IDataVal   -- the value of the inputdata")


SET(DOCSTRINGRAW_REMOVEINPUTDATA
"Removes an inputdata value for a given spatial unit.

Keyword arguments:
UnitClass  -- the unit class
IDataName  -- the name of the inputdata")


SET(DOCSTRINGRAW_OPENDATASET
"Opens a dataset.

Keyword arguments:
Path  -- the full path of the dataset to open")


SET(DOCSTRINGRAW_OPENPROJECT
"Opens an existing project.

Keyword arguments:
Path  -- the full path of the project to open")


SET(DOCSTRINGRAW_SETCURRENTOUTPUTDIR
"Sets the current output directory for simulations.

Keyword arguments:
Path  -- the output directory path")


SET(DOCSTRINGRAW_GETCURRENTOUTPUTDIR
"Gets the current output directory for simulations.

Returns:
the output directory path")


SET(DOCSTRINGRAW_GETDEFAULTDELTAT
"Returns the simulation time step.

Returns:
the time step value in seconds")


SET(DOCSTRINGRAW_SETDEFAULTDELTAT
"Sets the simulation time step.

Keyword arguments:
DefaultDeltaT  -- the time step value in seconds")


SET(DOCSTRINGRAW_GETPERIODBEGINDATE
"Returns the simulation period begin date.

Returns:
the begin date as an ISO datetime string (%Y-%m-%d %H:%M:%S)")


SET(DOCSTRINGRAW_GETPERIODENDDATE
"Returns the simulation period end date.

Returns:
the end date as an ISO datetime string (%Y-%m-%d %H:%M:%S)")


SET(DOCSTRINGRAW_SETPERIODBEGINDATE
"Sets the simulation period begin date.

  Keyword arguments:
  BeginDate  -- the begin date as an ISO datetime string (%Y-%m-%d %H:%M:%S)")


SET(DOCSTRINGRAW_SETPERIODENDDATE
"Sets the simulation period end date.

Keyword arguments:
EndDate  -- the end date as an ISO datetime string (%Y-%m-%d %H:%M:%S)")


SET(DOCSTRINGRAW_RUNPROJECT
"Runs an existing project.

Keyword arguments:
Path  -- the full path of the project to open")


SET(DOCSTRINGRAW_RUNSIMULATION
"Runs a simulation from a simulation definition class (self).

Returns:
True if the simulation is runned without problems, False otherwise")


SET(DOCSTRINGRAW_GETSTR
"Return a description of the class.

Returns:
A string representation of the class.

Examples:
>>> obj = PyOpenFLUID()
>>> info = str(obj)")

SET(DOCSTRINGRAW_CONSTRUCTOR
"Create an OpenFLUID class.")


# list of function
SET(DOCSTRING_ALL_FUNCTION GETVERSION PRINTSIMULATIONINFO
ADDEXTRAFUNCTIONSPATHS GETEXTRAFUNCTIONSPATHS RESETEXTRAFUNCTIONSPATHS
ADDEXTRAOBSERVERSPATHS GETEXTRAOBSERVERSPATHS RESETEXTRAOBSERVERSPATHS
GETFUNCTIONPARAM SETFUNCTIONPARAM REMOVEFUNCTIONPARAM GETFUNCTIONPARAMS
GETGENERATORPARAM SETGENERATORPARAM
GETMODELGLOBALPARAM SETMODELGLOBALPARAM REMOVEMODELGLOBALPARAM GETMODELGLOBALPARAMS
ADDFUNCTION REMOVEFUNCTION CLEARMODEL GETFUNCTIONSINMODEL
GETOBSERVERPARAM SETOBSERVERPARAM REMOVEOBSERVERPARAM GETOBSERVERPARAMS
ADDOBSERVER REMOVEOBSERVER CLEARMONITORING GETOBSERVERSINMONITORING
GETUNITSCLASSES GETUNITSIDS ADDUNIT REMOVEUNIT CLEARUNITCLASS
GETUNITPROCESSORDER SETUNITPROCESSORDER GETUNITSCHILDREN GETUNITSPARENTS
ADDPARENTCHILDCONNECTION REMOVEPARENTCHILDCONNECTION
CREATEINPUTDATA GETINPUTDATA SETINPUTDATA REMOVEINPUTDATA
OPENDATASET OPENPROJECT SETCURRENTOUTPUTDIR GETCURRENTOUTPUTDIR
GETDEFAULTDELTAT SETDEFAULTDELTAT
GETPERIODBEGINDATE GETPERIODENDDATE SETPERIODBEGINDATE SETPERIODENDDATE
RUNPROJECT RUNSIMULATION GETSTR CONSTRUCTOR)
