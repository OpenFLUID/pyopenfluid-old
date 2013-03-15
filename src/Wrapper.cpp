#include <boost/python/def.hpp>
#include <boost/python/scope.hpp>
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/raw_function.hpp>
#include <boost/python/docstring_options.hpp>
#include <boost/python/exception_translator.hpp>
#include <boost/python/return_internal_reference.hpp>

#include <boost/python/str.hpp>
#include <boost/python/dict.hpp>
#include <boost/python/list.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/object.hpp>

#include <openfluid/config.hpp>

#include "Wrapper.hpp"
#include "PyOpenFLUID.hpp"
#include "PyOpenFLUIDError.hpp"
#include "PythonUtilities.hpp"



BOOST_PYTHON_MODULE(_pyopenfluid)
{

// =====================================================================
/* ------------------------- BOOST SETTINGS ------------------------- */

  // docstring perso - docstring boost(python) - docstring boost(c++)
  boost::python::docstring_options local_docstring_options(true, true, false);


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


// =====================================================================
// =====================================================================


    .def("addExtraFunctionsPaths",
      &PyOpenFLUID::addExtraFunctionsPaths,
      ( boost::python::arg("self"), boost::python::arg("Paths") ),
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
      ( boost::python::arg("self") ),
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
      ( boost::python::arg("self") ),
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
      ( boost::python::arg("self"), boost::python::arg("Paths") ),
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
      ( boost::python::arg("self") ),
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
      ( boost::python::arg("self") ),
      "Reset paths to search for observers.\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.resetExtraObserversPaths()\
"
    )


// =====================================================================
// =====================================================================


    .def("getVersion",
        boost::python::raw_function<RawFunctionPyOpenFLUID>(
            RawFunctionPyOpenFLUID(&PyOpenFLUID::getVersion)),
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
      ( boost::python::arg("self") ),
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
      ( boost::python::arg("self"), boost::python::arg("FuncID"),
        boost::python::arg("ParamName") ),
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
      ( boost::python::arg("self"), boost::python::arg("FuncID"),
        boost::python::arg("ParamName"), boost::python::arg("ParamValue") ),
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
      ( boost::python::arg("self"), boost::python::arg("FuncID"),
        boost::python::arg("ParamName") ),
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


    .def("getFunctionParams",
      &PyOpenFLUID::getFunctionParams,
      ( boost::python::arg("self"), boost::python::arg("FuncID") ),
      "Gets all parameter of a function.\
\n\nKeyword arguments:\
\nFunID        -- the simulation function id\
\nReturns:\
\na list of parameter name\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> listparam = obj.getFunctionParams(\"my.function\")\
"
    )


// =====================================================================
// =====================================================================


    .def("getGeneratorParam", &PyOpenFLUID::getGeneratorParam,
      ( boost::python::arg("self"), boost::python::arg("UnitClass"),
        boost::python::arg("VarName"), boost::python::arg("ParamName") ),
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
      ( boost::python::arg("self"), boost::python::arg("UnitClass"),
        boost::python::arg("VarName"), boost::python::arg("ParamName"),
        boost::python::arg("ParamValue") ),
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
      ( boost::python::arg("self"), boost::python::arg("ParamName") ),
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
      ( boost::python::arg("self"), boost::python::arg("ParamName"),
        boost::python::arg("ParamValue") ),
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


    .def("getModelGlobalParams",
      &PyOpenFLUID::getModelGlobalParams,
      ( boost::python::arg("self") ),
      "Returns all model global parameter.\
\n\nReturns:\
\na list of parameter name.\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> listparam = obj.getModelGlobalParams()\
"
    )


// =====================================================================
// =====================================================================


    .def("removeModelGlobalParam",
      &PyOpenFLUID::removeModelGlobalParam,
      ( boost::python::arg("self"), boost::python::arg("ParamName") ),
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
      ( boost::python::arg("self"), boost::python::arg("FuncID") ),
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
      ( boost::python::arg("self"), boost::python::arg("FuncID") ),
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
      ( boost::python::arg("self") ),
      "Removes all functions.\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.clearModel()\
"
    )


// =====================================================================
// =====================================================================


    .def("getFunctionsInModel",
      &PyOpenFLUID::getFunctionsInModel,
      ( boost::python::arg("self") ),
      "Gets all functions names.\
\n\nReturns:\
\na list of function name.\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> funclist = obj.getFunctionsInModel()\
"
    )


// =====================================================================
/* ---------------------  MONITORING FUNCTIONS  --------------------- */


    .def("getObserverParam", &PyOpenFLUID::getObserverParam,
      ( boost::python::arg("self"), boost::python::arg("ObsID"),
        boost::python::arg("ParamName") ),
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
      ( boost::python::arg("self"), boost::python::arg("ObsID"),
        boost::python::arg("ParamName"), boost::python::arg("ParamValue") ),
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


    .def("removeObserverParam",
      &PyOpenFLUID::removeObserverParam,
      ( boost::python::arg("self"), boost::python::arg("ObsID"),
        boost::python::arg("ParamName") ),
      "Removes an observer parameter.\
\n\nKeyword arguments:\
\nFunID        -- the simulation function id\
\nParamName    -- the name of the parameter\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.removeObserverParam(\"my.function\",\"coeff\")\
"
    )


// =====================================================================
// =====================================================================


    .def("getObserverParams",
      &PyOpenFLUID::getObserverParams,
      ( boost::python::arg("self"), boost::python::arg("ObsID") ),
      "Gets all observer parameters name.\
\n\nKeyword arguments:\
\nFunID        -- the simulation function id\
\nReturns\
\na list of parameters name\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.removeObserverParam(\"my.function\",\"coeff\")\
"
    )


// =====================================================================
// =====================================================================


    .def("addObserver", &PyOpenFLUID::addObserver,
      ( boost::python::arg("self"), boost::python::arg("ObsID") ),
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
      ( boost::python::arg("self"), boost::python::arg("ObsID") ),
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
      ( boost::python::arg("self") ),
      "Removes all observers.\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.clearMonitoring()\
"
    )


// =====================================================================
// =====================================================================


    .def("getObserversInMonitoring", &PyOpenFLUID::getObserversInMonitoring,
      ( boost::python::arg("self") ),
      "Gets all observer name.\
\n\nReturns:\
\na list of observer name\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> listobs = obj.getObserversInMonitoring()\
"
    )


// =====================================================================
/* -------------------  SPATIAL DOMAIN FUNCTIONS  ------------------- */


    .def("getUnitsClasses", &PyOpenFLUID::getUnitsClasses,
      ( boost::python::arg("self") ),
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
      ( boost::python::arg("self"), boost::python::arg("UnitClass") ),
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


    .def("addUnit", &PyOpenFLUID::addUnit,
      ( boost::python::arg("self"), boost::python::arg("UnitClass"),
        boost::python::arg("UnitID"), boost::python::arg("PcsOrder") ),
      "Adds an new unit.\
\n\nKeyword arguments:\
\nUnitClass  -- an unit class\
\nUnitID     -- an new unit id for this unit class\
\nPcsOrder   -- a process order\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.addUnit(\"SU\", 3, 1)\
"
    )


// =====================================================================
// =====================================================================


    .def("removeUnit", &PyOpenFLUID::removeUnit,
      ( boost::python::arg("self"), boost::python::arg("UnitClass"),
        boost::python::arg("UnitID") ),
      "Removes an unit.\
\n\nKeyword arguments:\
\nUnitClass  -- an unit class\
\nUnitID     -- an new unit id for this unit class\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.removeUnit(\"SU\", 3)\
"
    )


// =====================================================================
// =====================================================================


    .def("clearUnitClass", &PyOpenFLUID::clearUnitClass,
      ( boost::python::arg("self"), boost::python::arg("UnitClass") ),
      "Removes all units from an unit class.\
\n\nKeyword arguments:\
\nUnitClass  -- an unit class\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.clearUnitClass(\"SU\")\
"
    )


// =====================================================================
// =====================================================================


    .def("setUnitProcessOrder", &PyOpenFLUID::setUnitProcessOrder,
      ( boost::python::arg("self"), boost::python::arg("UnitClass"),
        boost::python::arg("UnitID"), boost::python::arg("PcsOrder") ),
      "Sets the process order of an unit.\
\n\nKeyword arguments:\
\nUnitClass  -- an unit class\
\nUnitID     -- an unit id for this unit class\
\nPcsOrder   -- a process order\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.setUnitProcessOrder(\"SU\", 3, 1)\
"
    )


// =====================================================================
// =====================================================================


    .def("getUnitProcessOrder", &PyOpenFLUID::getUnitProcessOrder,
      ( boost::python::arg("self"), boost::python::arg("UnitClass"),
        boost::python::arg("UnitID") ),
      "Gets the process order of an unit.\
\n\nKeyword arguments:\
\nUnitClass  -- an unit class\
\nUnitID     -- an unit id for this unit class\
\nReturns:\
\nthe process order\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> ProcOrder = obj.getUnitProcessOrder(\"SU\", 3)\
"
    )


// =====================================================================
// =====================================================================


    .def("getUnitsChildren", &PyOpenFLUID::getUnitsChildren,
      ( boost::python::arg("self"), boost::python::arg("UnitClass"),
        boost::python::arg("UnitID") ),
      "Gets children units of an unit.\
\n\nKeyword arguments:\
\nUnitClass  -- an unit class\
\nUnitID     -- an unit id for this unit class\
\nReturns:\
\na list of tuple of units classes and units\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> Children = obj.getUnitsChildren(\"SU\", 3)\
"
    )


// =====================================================================
// =====================================================================


    .def("getUnitsParents", &PyOpenFLUID::getUnitsParents,
      ( boost::python::arg("self"), boost::python::arg("UnitClass"),
        boost::python::arg("UnitID") ),
      "Gets parents units of an unit.\
\n\nKeyword arguments:\
\nUnitClass  -- an unit class\
\nUnitID     -- an unit id for this unit class\
\nReturns:\
\na list of tuple of units classes and units\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> Parents = obj.getUnitsParents(\"SU\", 3)\
"
    )


// =====================================================================
// =====================================================================


    .def("addUnitChild", &PyOpenFLUID::addUnitChild,
      ( boost::python::arg("self"), boost::python::arg("UnitClassFrom"),
        boost::python::arg("UnitIDFrom"), boost::python::arg("UnitClassTo"),
        boost::python::arg("UnitIDTo") ),
      "Adds a child on an unit.\
\n\nKeyword arguments:\
\nUnitClassFrom  -- an unit class (parent)\
\nUnitIDFrom     -- an unit id (parent)\
\nUnitClassTo    -- an unit class (child)\
\nUnitIDTo       -- an unit id (child)\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.addUnitChild(\"SU\", 3, \"SU\", 5)\
"
    )


// =====================================================================
// =====================================================================


    .def("removeUnitChild", &PyOpenFLUID::removeUnitChild,
      ( boost::python::arg("self"), boost::python::arg("UnitClassFrom"),
        boost::python::arg("UnitIDFrom"), boost::python::arg("UnitClassTo"),
        boost::python::arg("UnitIDTo") ),
      "Removes a child of an unit.\
\n\nKeyword arguments:\
\nUnitClassFrom  -- an unit class (parent)\
\nUnitIDFrom     -- an unit id (parent)\
\nUnitClassTo    -- an unit class (child)\
\nUnitIDTo       -- an unit id (child)\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.removeUnitChild(\"SU\", 3, \"SU\", 5)\
"
    )


// =====================================================================
// =====================================================================


    .def("createInputData", &PyOpenFLUID::createInputData,
      ( boost::python::arg("self"), boost::python::arg("UnitClass"),
        boost::python::arg("IDataName"), boost::python::arg("IDataValue") ),
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
      ( boost::python::arg("self"), boost::python::arg("UnitClass"),
        boost::python::arg("UnitID"), boost::python::arg("IDataName") ),
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
      ( boost::python::arg("self"), boost::python::arg("UnitClass"),
        boost::python::arg("UnitID"), boost::python::arg("IDataName"),
        boost::python::arg("IDataValue") ),
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


    .def("removeInputData", &PyOpenFLUID::removeInputData,
      ( boost::python::arg("self"), boost::python::arg("UnitClass"),
        boost::python::arg("IDataName") ),
      "Removes an inputdata value for a given spatial unit.\
\n\nKeyword arguments:\
\nUnitClass   -- the unit class\
\nIDataName   -- the name of the inputdata\
\n\nExamples:\
\n>>> obj = PyOpenFLUID()\
\n>>> obj.removeInputData(\"SU\",\"length\")\
\n>>> obj.removeInputData(\"SU\",\"CODE\")\
"
    )


// =====================================================================
// =====================================================================


    .def("openDataset", &PyOpenFLUID::openDataset,
      ( boost::python::arg("self"), boost::python::arg("Path") ),
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
      ( boost::python::arg("self"), boost::python::arg("Path") ),
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
      ( boost::python::arg("self"), boost::python::arg("Path") ),
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
      ( boost::python::arg("self") ),
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
      ( boost::python::arg("self") ),
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
      ( boost::python::arg("self"), boost::python::arg("DeltaT") ),
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
      ( boost::python::arg("self") ),
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
      ( boost::python::arg("self") ),
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
      ( boost::python::arg("self"), boost::python::arg("BeginDate") ),
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
      ( boost::python::arg("self"), boost::python::arg("EndDate") ),
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
      ( boost::python::arg("self"), boost::python::arg("Path") ),
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
      ( boost::python::arg("self") ),
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
      ( boost::python::arg("self"), boost::python::arg("InputClass") ),
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
      ( boost::python::arg("self") ),
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
