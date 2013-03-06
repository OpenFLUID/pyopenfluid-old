#include <boost/python.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <openfluid/config.hpp>
#include "PyOpenFLUID.hpp"
#include "PyOpenFLUIDError.hpp"

BOOST_PYTHON_MODULE(_pyopenfluid)
{

// =====================================================================
/* ------------------------- BOOST SETTINGS ------------------------- */

  // docstring perso - docstring boost(python) - docstring boost(c++)
  boost::python::docstring_options local_docstring_options(true, false, false);


// =====================================================================
/* ------------------------- MODULE CONSTANTS ----------------------- */

  boost::python::scope().attr("__version__") = boost::python::str(
      (const std::string) openfluid::config::FULL_VERSION);

  boost::python::scope().attr("__author__") = boost::python::str(
      "Bastien VAYSSE");

  boost::python::list AuthorsList = boost::python::list();
  AuthorsList.append(
      boost::python::str("Bastien VAYSSE <bastien.vaysse@supagro.inra.fr>"));
  AuthorsList.append(
      boost::python::str("Jean-Christophe FABRE <fabrejc@supagro.inra.fr>"));
  boost::python::scope().attr("__credits__") = AuthorsList;

  boost::python::scope().attr("__license__") = boost::python::str("GPLv3");

  boost::python::scope().attr("__date__") =
      boost::python::str("27-02-2013 GMT+0100");

  boost::python::scope().attr("__doc__") =
      boost::python::str("This module allows to load, parameterize, run and\
 analyse OpenFLUID simulations within the Python 2.x environment.");


// =====================================================================
/* ---------------------- OTHERS CLASS & METHODS -------------------- */

  boost::python::register_exception_translator<PyOFException>
                                              (&TranslatePyOFException);


// =====================================================================
/* ------------------------ PYOPENFLUID CLASS ----------------------- */


  boost::python::class_<PyOpenFLUID>("PyOpenFLUID",
                      boost::python::init<>("Create an OpenFLUID class.") )

    .def("addExtraFunctionsPaths",
      &PyOpenFLUID::addExtraFunctionsPaths,
      ( boost::python::arg("Paths") ),
      "Adds paths to search for simulation functions.\
\n\nKeyword arguments:\
\nPaths  -- the semicolon separated paths to add\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.addExtraFunctionsPaths(\"/first/path/to/add\")\
\n>>> obj.addExtraFunctionsPaths(\"/second/path/to/add:/third/path/to/add\")\
"
    )


// =====================================================================
// =====================================================================


    .def("getExtraFunctionsPaths",
      &PyOpenFLUID::getExtraFunctionsPaths,
      "Returns the added paths to search for simulation functions.\
\n\nReturns:\
\na list of Paths\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> paths = obj.getExtraFunctionsPaths()\
"
    )


// =====================================================================
// =====================================================================


    .def("resetExtraFunctionsPaths",
      &PyOpenFLUID::resetExtraFunctionsPaths,
      "Reset paths to search for simulation functions.\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.resetExtraFunctionsPaths()\
"
    )


// =====================================================================
// =====================================================================


    .def("addExtraObserversPaths",
      &PyOpenFLUID::addExtraObserversPaths,
      ( boost::python::arg("Paths") ),
      "Adds paths to search for observers.\
\n\nKeyword arguments:\
\nPaths  -- the semicolon separated paths to add\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.addExtraObserversPaths(\"/first/path/to/add\")\
\n>>> obj.addExtraObserversPaths(\"/second/path/to/add:/third/path/to/add\")\
"
    )


// =====================================================================
// =====================================================================


    .def("getExtraObserversPaths",
      &PyOpenFLUID::getExtraObserversPaths,
      "Returns the added paths to search for observers.\
\n\nReturns:\
\na list of Paths\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> paths = obj.getExtraObserversPaths()\
"
    )


// =====================================================================
// =====================================================================


    .def("resetExtraObserversPaths",
      &PyOpenFLUID::resetExtraObserversPaths,
      "Reset paths to search for observers.\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.resetExtraObserversPaths()\
"
    )


// =====================================================================
// =====================================================================


    .def("getVersion", &PyOpenFLUID::getVersion,
      "Returns the OpenFLUID version.\
\n\nReturns:\
\nthe OpenFLUID version number\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> v = obj.getVersion()\
"
    )


// =====================================================================
// =====================================================================


    .def("printSimulationInfo",
      &PyOpenFLUID::printSimulationInfo,
      "Prints informations to screen about simulation definition class (self).\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.printSimulationInfo()\
"
    )


// =====================================================================
/* ------------------------  MODEL FUNCTIONS  ----------------------- */


    .def("getFunctionParam",
      &PyOpenFLUID::getFunctionParam,
      ( boost::python::arg("FuncID"), boost::python::arg("ParamName") ),
      "Returns a function parameter value.\
\n\nKeyword arguments:\
\nFunID      -- the simulation function id\
\nParamName  -- the name of the parameter\
\n\nReturns:\
\nthe parameter value\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> val = obj.getFunctionParam(\"my_function\", \"coeff\")\
"
    )


// =====================================================================
// =====================================================================


    .def("setFunctionParam",
      &PyOpenFLUID::setFunctionParam,
      ( boost::python::arg("FuncID"), boost::python::arg("ParamName"),
        boost::python::arg("ParamValue") ),
      "Sets a function parameter value.\
\n\nKeyword arguments:\
\nFunID        -- the simulation function id\
\nParamName    -- the name of the parameter\
\nParamValue   -- the parameter value\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.setFunctionParam(\"my.function\",\"coeff\",\"3\")\
"
    )


// =====================================================================
// =====================================================================


    .def("removeFunctionParam",
      &PyOpenFLUID::removeFunctionParam,
      ( boost::python::arg("FuncID"), boost::python::arg("ParamName") ),
      "Removes a function parameter.\
\n\nKeyword arguments:\
\nFunID        -- the simulation function id\
\nParamName    -- the name of the parameter\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.removeFunctionParam(\"my.function\",\"coeff\")\
"
    )


// =====================================================================
// =====================================================================


    .def("getGeneratorParam", &PyOpenFLUID::getGeneratorParam,
      ( boost::python::arg("UnitClass"), boost::python::arg("VarName"),
        boost::python::arg("ParamName") ),
      "Returns a generator parameter value.\
\n\nKeyword arguments:\
\nUnitClass  -- the unit class to which the generator is applied\
\nVarName    -- the variable name to which the generator is applied\
\nParamName  -- the name of the parameter\
\n\nReturns:\
\nthe parameter value\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> val = obj.getGeneratorParam(\"SU\",\"var.flux\",\"fixedvalue\")\
"
    )


// =====================================================================
// =====================================================================


    .def("setGeneratorParam", &PyOpenFLUID::setGeneratorParam,
      ( boost::python::arg("UnitClass"), boost::python::arg("VarName"),
        boost::python::arg("ParamName"), boost::python::arg("ParamValue") ),
      "Sets a generator parameter value.\
\n\nKeyword arguments:\
\nUnitClass   -- the unit class to which the generator is applied\
\nVarName     -- the variable name to which the generator is applied\
\nParamName   -- the name of the parameter\
\nParamValue  -- the parameter value\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.setGeneratorParam(\"SU\",\"var.flux\",\"fixedvalue\",\"12.3\")\
"
    )


// =====================================================================
// =====================================================================


    .def("getModelGlobalParam",
      &PyOpenFLUID::getModelGlobalParam,
      ( boost::python::arg("ParamName") ),
      "Returns a model global parameter value.\
\n\nKeyword arguments:\
\nParamName  -- the name of the parameter\
\n\nReturns:\
\nthe parameter value\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> val = obj.getModelGlobalParam(\"gvalue\")\
"
    )


// =====================================================================
// =====================================================================


    .def("setModelGlobalParam",
      &PyOpenFLUID::setModelGlobalParam,
      ( boost::python::arg("ParamName"), boost::python::arg("ParamValue") ),
      "Sets a model global parameter value.\
\n\nKeyword arguments:\
\nParamName   -- the name of the parameter\
\nParamValue  -- the parameter value\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.setModelGlobalParam(\"gvalue\",\"37.2\")\
"
    )


// =====================================================================
// =====================================================================


    .def("removeModelGlobalParam",
      &PyOpenFLUID::removeModelGlobalParam,
      ( boost::python::arg("ParamName") ),
      "Removes a model global parameter value.\
\n\nKeyword arguments:\
\nParamName   -- the name of the parameter\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.removeModelGlobalParam(\"gvalue\")\
"
    )


// =====================================================================
// =====================================================================


    .def("addFunction",
      &PyOpenFLUID::addFunction,
      ( boost::python::arg("FuncID") ),
      "Adds a function.\
\n\nKeyword arguments:\
\nFunID        -- the simulation function id\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.addFunction(\"my.function\")\
"
    )


// =====================================================================
// =====================================================================


    .def("removeFunction",
      &PyOpenFLUID::removeFunction,
      ( boost::python::arg("FuncID") ),
      "Removes a function.\
\n\nKeyword arguments:\
\nFunID        -- the simulation function id\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.removeFunction(\"my.function\")\
"
    )


// =====================================================================
// =====================================================================


    .def("clearModel",
      &PyOpenFLUID::clearModel,
      "Removes all functions.\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.clearModel()\
"
    )


// =====================================================================
/* ---------------------  MONITORING FUNCTIONS  --------------------- */


    .def("getObserverParam", &PyOpenFLUID::getObserverParam,
      ( boost::python::arg("ObsID"), boost::python::arg("ParamName") ),
      "Returns an observer parameter value.\
\n\nKeyword arguments:\
\nObsID      -- the observer id\
\nParamName  -- the name of the parameter\
\n\nReturns:\
\nthe parameter value\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> param = obj.getObserverParam(\"export.fake.useless\", \"format.f1.header\")\
"
    )


// =====================================================================
// =====================================================================


    .def("setObserverParam", &PyOpenFLUID::setObserverParam,
      ( boost::python::arg("ObsID"), boost::python::arg("ParamName"),
        boost::python::arg("ParamValue") ),
      "Sets an observer parameter value.\
\n\nKeyword arguments:\
\nObsID       -- the observer id\
\nParamName   -- the name of the parameter\
\nParamValue  -- the parameter value\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.setObserverParam(\"export.fake.useless\", \"format.f1.header\", \"colsname\")\
"
    )


// =====================================================================
// =====================================================================


    .def("addObserver", &PyOpenFLUID::addObserver,
      ( boost::python::arg("ObsID") ),
      "Adds an observer.\
\n\nKeyword arguments:\
\nObsID       -- the observer id\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.addObserver(\"export.fake.useless\")\
"
    )


// =====================================================================
// =====================================================================


    .def("removeObserver", &PyOpenFLUID::removeObserver,
      ( boost::python::arg("ObsID") ),
      "Removes an observer.\
\n\nKeyword arguments:\
\nObsID       -- the observer id\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.removeObserver(\"export.fake.useless\")\
"
    )


// =====================================================================
// =====================================================================


    .def("clearMonitoring", &PyOpenFLUID::clearMonitoring,
      "Removes all observers.\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.clearMonitoring()\
"
    )


// =====================================================================
/* -------------------  SPATIAL DOMAIN FUNCTIONS  ------------------- */


    .def("getUnitsClasses", &PyOpenFLUID::getUnitsClasses,
      "Returns the existing units classes.\
\n\nReturns:\
\na list of units classes\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> lclass = obj.getUnitsClasses()\
"
    )


// =====================================================================
// =====================================================================


    .def("getUnitsIDs", &PyOpenFLUID::getUnitsIDs,
      ( boost::python::arg("UnitClass") ),
      "Returns the existing units IDs for a given units class.\
\n\nKeyword arguments:\
\nUnitClass  -- the unit class\
\n\nReturns:\
\na list of units IDs\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> lids = obj.getUnitsIDs(\"SU\")\
"
    )


// =====================================================================
// =====================================================================


    .def("createInputData", &PyOpenFLUID::createInputData,
      ( boost::python::arg("UnitClass"), boost::python::arg("IDataName"),
        boost::python::arg("IDataValue") ),
      "Creates an inputdata for alla spatial units of a class, initialized with\
a default value.\
\n\nKeyword arguments:\
\nUnitClass    -- the unit class\
\nIDataName    -- the inputdata name\
\nIDataValue   -- the default inputdata value for alla units\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.createInputData(\"SU\",\"area\",\"1.0\")\
\n>>> obj.createInputData(\"SU\",\"code\",\"NONE\")\
"
    )


// =====================================================================
// =====================================================================


    .def("getInputData", &PyOpenFLUID::getInputData,
      ( boost::python::arg("UnitClass"), boost::python::arg("UnitID"),
        boost::python::arg("IDataName") ),
      "Returns an inputdata value for a given spatial unit.\
\n\nKeyword arguments:\
\nUnitClass  -- the unit class\
\nUnitID     -- the unit ID\
\nIDataName  -- the name of the inputdata\
\n\nReturns:\
\nthe inputdata value\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> val = obj.getInputData(\"SU\",18,\"length\")\
"
    )


// =====================================================================
// =====================================================================


    .def("setInputData", &PyOpenFLUID::setInputData,
      ( boost::python::arg("UnitClass"), boost::python::arg("UnitID"),
        boost::python::arg("IDataName"), boost::python::arg("IDataValue") ),
      "Sets an inputdata value for a given spatial unit.\
\n\nKeyword arguments:\
\nUnitClass   -- the unit class\
\nUnitID      -- the unit ID\
\nIDataName   -- the name of the inputdata\
\nIDataValue  -- the value of the inputdata\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.setInputData(\"SU\",18,\"length\",\"12.3\")\
\n>>> obj.setInputData(\"SU\",18,\"CODE\",\"ABC\")\
"
    )


// =====================================================================
// =====================================================================


    .def("openDataset", &PyOpenFLUID::openDataset,
      ( boost::python::arg("Path") ),
      "Opens a dataset and returns a new simulation definition class\
 (PyOpenFLUID).\
\nKeyword arguments:\
\nPath  -- the full path of the dataset to open\
\n\nReturns:\
\na new simulation definition class (PyOpenFLUID)\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> otherClass = obj.openDataset(\"/path/to/dataset\")\
", boost::python::return_internal_reference<>()
    )


// =====================================================================
// =====================================================================


    .def("openProject", &PyOpenFLUID::openProject,
      ( boost::python::arg("Path") ),
      "Opens a project and returns a new simulation definition class\
 (PyOpenFLUID).\
\n\nKeyword arguments:\
\nPath  -- the full path of the project to open\
\n\nReturns:\
\na new simulation definition class (PyOpenFLUID)\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> otherClass = obj.openDataset(\"/path/to/project\")\
", boost::python::return_internal_reference<>()
    )


// =====================================================================
// =====================================================================


    .def("setCurrentOutputDir",
      &PyOpenFLUID::setCurrentOutputDir,
      ( boost::python::arg("Path") ),
      "Sets the current output directory for simulations.\
\n\nKeyword arguments:\
\nPath  -- the output directory path\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.setCurrentOutputDir(\"/path/to/output\")\
"
    )


// =====================================================================
// =====================================================================


    .def("getCurrentOutputDir",
      &PyOpenFLUID::getCurrentOutputDir,
      "Gets the current output directory for simulations.\
\n\nReturns:\
\nthe output directory path\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> path = obj.getCurrentOutputDir()\
"
    )


// =====================================================================
/* ---------------------  SIMULATION FUNCTIONS  --------------------- */


    .def("getDefaultDeltaT", &PyOpenFLUID::getDefaultDeltaT,
      "Returns the simulation time step.\
\n\nReturns:\
\nthe time step value in seconds\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> deltat = obj.getDefaultDeltaT()\
"
    )


// =====================================================================
// =====================================================================


    .def("setDefaultDeltaT", &PyOpenFLUID::setDefaultDeltaT,
      ( boost::python::arg("DeltaT") ),
      "Sets the simulation time step.\
\n\nKeyword arguments:\
\nDefaultDeltaT  -- the time step value in seconds\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.setDefaultDeltaT(60)\
\n>>> obj.setDefaultDeltaT(86400)\
"
    )


// =====================================================================
// =====================================================================


    .def("getPeriodBeginDate",
      &PyOpenFLUID::getPeriodBeginDate,
      "Returns the simulation period begin date.\
\n\nReturns:\
\nthe begin date as an ISO datetime string (%Y-%m-%d %H:%M:%S)\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> bdate = obj.getPeriodBeginDate()\
"
    )


// =====================================================================
// =====================================================================


    .def("getPeriodEndDate", &PyOpenFLUID::getPeriodEndDate,
      "Returns the simulation period end date.\
\n\nReturns:\
\nthe end date as an ISO datetime string (%Y-%m-%d %H:%M:%S)\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> edate = obj.getPeriodEndDate()\
"
    )


// =====================================================================
// =====================================================================


    .def("setPeriodBeginDate", &PyOpenFLUID::setPeriodBeginDate,
      ( boost::python::arg("BeginDate") ),
      "Sets the simulation period begin date.\
\n\nKeyword arguments:\
\nBeginDate  -- the begin date as an ISO datetime string (%Y-%m-%d %H:%M:%S)\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.setPeriodBeginDate(\"1997-06-05 04:00:00\")\
"
    )


// =====================================================================
// =====================================================================


    .def("setPeriodEndDate", &PyOpenFLUID::setPeriodEndDate,
      ( boost::python::arg("EndDate") ),
      "Sets the simulation period end date.\
\n\nKeyword arguments:\
\nEndDate  -- the end date as an ISO datetime string\
 (%Y-%m-%d %H:%M:%S)\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.setPeriodEndDate(\"1997-06-05 16:07:17\")\
"
    )


// =====================================================================
// =====================================================================


    .def("runProject", &PyOpenFLUID::runProject,
      ( boost::python::arg("Path") ),
      "Runs a project and returns a simulation definition class (PyOpenFLUID).\
\n\nKeyword arguments:\
\nPath  -- the full path of the project to open\
\n\nReturns:\
\na simulation definition class (PyOpenFLUID)\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> ofsim = obj.runProject(\"/path/to/dataset\")\
", boost::python::return_internal_reference<>()
    )


// =====================================================================
// =====================================================================


    .def("runSimulation", &PyOpenFLUID::runSimulation,
      "Runs a simulation from a simulation definition class (self).\
\n\nReturns:\
\nTrue if the simulation is runned without problems, False otherwise\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.runSimulation()\
"
    )


// =====================================================================
// =====================================================================


//    .def("loadResult", &PyOpenFLUID::loadResult,
//      ( boost::python::arg("UnitClass"), boost::python::arg("UnitID"),
//        boost::python::arg("Suffix") ),
//      "Loads results as a dataframe, giving output dataset informations.\
//\n\nKeyword arguments:\
//\nUnitClass  -- the unit class\
//\nUnitID     -- the unit ID\
//\nSuffix     -- the output dataset suffix\
//\n\nReturns:\
//\na dataframe containing the simulation results\
//\n\nExamples:\
//\n>>> obj = PyOpenFLUID()\
//\n>>> resSU18 = obj.loadResult(self, \"SU\",18,\"full\")\
//\n>>> resRS1 = obj.loadResult(self, \"RS\",1,\"waterlevel\")\
//", boost::python::return_internal_reference<>()
//    )


// =====================================================================
// =====================================================================


//    .def("loadResultFile", &PyOpenFLUID::loadResultFile,
//      ( boost::python::arg("FilePath") ),
//      "Loads results as a dataframe, giving output file name.\
//\n\nKeyword arguments:\
//\nFilePath  -- the full path of the file to load\
//\n\nReturns:\
//\na dataframe containing the simulation results\
//\n\nExamples:\
//\n>>> obj = PyOpenFLUID()\
//\n>>> resSU18 = obj.loadResultFile(\"/path/to/output/SU18_full.out\")\
//\n>>> resRS1 = obj.loadResultFile(\
//\"/path/to/output/RS1_waterlevel.out\")\
//", boost::python::return_internal_reference<>()
//    )


// =====================================================================
/* ------------------------ OTHER FUNCTIONS  ------------------------ */


    .def("_copy", &PyOpenFLUID::copy,
      ( boost::python::arg("InputClass") ),
      "Copy all attributs from the parameter in self.\
\n\nKeyword arguments:\
\nInputClass  -- the PyOpenFLUID class to copy\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj._copy(otherClass)\
"
    )


// =====================================================================
// =====================================================================


    .def("__str__", &PyOpenFLUID::getStr,
      "Return a description of the class.\
\n\nReturns:\
\nA string representation of the class.\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> info = str(obj)\
"
    )

; /* end of PyOpenFLUID class definition */

}
