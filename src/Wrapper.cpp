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
  boost::python::docstring_options local_docstring_options(true, true, false);


// =====================================================================
/* ------------------------- MODULE CONSTANTS ----------------------- */

  boost::python::scope().attr("__version__") = boost::python::str(
      (const std::string) openfluid::config::FULL_VERSION);

  boost::python::list AuthorsList = boost::python::list();
  AuthorsList.append(boost::python::str("Bastien Vaysse <bastien.vaysse@supagro.inra.fr>"));
  AuthorsList.append(boost::python::str("Jean-Christophe Fabre <fabrejc@supagro.inra.fr>"));
  boost::python::scope().attr("__authors__") = AuthorsList;

  boost::python::scope().attr("__license__") = boost::python::str("GPLv3");

  boost::python::scope().attr("__date__") = boost::python::str("wen 27 févr. 2013 14:45:23 +0100 ");


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
\n - Paths    : the semicolon separated paths to add\
\n\nExamples:\
\n\tPyOpenFLUID.addExtraFunctionsPaths(\"/first/path/to/add\")\
\n\tPyOpenFLUID.addExtraFunctionsPaths(\"/second/path/to/add\
:/third/path/to/add\")\
"
    )


// =====================================================================
// =====================================================================


    .def("getExtraFunctionsPaths",
      &PyOpenFLUID::getExtraFunctionsPaths,
      "Returns the added paths to search for simulation functions.\
\n\nExamples:\
\n\tPaths = PyOpenFLUID.getExtraFunctionsPaths()\
"
    )


// =====================================================================
// =====================================================================


    .def("resetExtraFunctionsPaths",
      &PyOpenFLUID::resetExtraFunctionsPaths,
      "Reset the added paths to search for simulation functions.\
\n\nExamples:\
\n\tPyOpenFLUID.resetExtraFunctionsPaths()\
"
    )


// =====================================================================
// =====================================================================


    .def("addExtraObserversPaths",
      &PyOpenFLUID::addExtraObserversPaths,
      ( boost::python::arg("Paths") ),
      "Adds paths to search for observers.\
\n - Paths    : the semicolon separated paths to add\
\n\nExamples:\
\n\tPyOpenFLUID.addExtraObserversPaths(\"/first/path/to/add\")\
\n\tPyOpenFLUID.addExtraObserversPaths(\"/second/path/to/add\
:/third/path/to/add\")\
"
    )


// =====================================================================
// =====================================================================


    .def("getExtraObserversPaths",
      &PyOpenFLUID::getExtraObserversPaths,
      "Returns the added paths to search for observers.\
\n\nExamples:\
\n\tPaths = PyOpenFLUID.getExtraObserversPaths()\
"
    )


// =====================================================================
// =====================================================================


    .def("resetExtraObserversPaths",
      &PyOpenFLUID::resetExtraObserversPaths,
      "Reset the added paths to search for observers.\
\n\nExamples:\
\n\tPyOpenFLUID.resetExtraObserversPaths()\
"
    )


// =====================================================================
// =====================================================================


    .def("getVersion", &PyOpenFLUID::getVersion,
      "Returns the OpenFLUID version.\
\n\nExamples:\
\n\tV = PyOpenFLUID.getVersion()\
"
    )


// =====================================================================
// =====================================================================


    .def("printSimulationInfo",
      &PyOpenFLUID::printSimulationInfo,
      "Prints informations to screen about simulation definition class (self).\
\n\nExamples:\
\n\tPyOpenFLUID.printSimulationInfo()\
"
    )


// =====================================================================
/* ------------------------  MODEL FUNCTIONS  ----------------------- */


    .def("getFunctionParam",
      &PyOpenFLUID::getFunctionParam,
      ( boost::python::arg("FuncID"), boost::python::arg("ParamName") ),
      "Returns a function parameter value.\
\n - FuncID     : the simulation function id\
\n - ParamName  : the name of the parameter\
\n\nExamples:\
\n\tVal = PyOpenFLUID.getFunctionParam(\"my_function\", \"coeff\")\
"
    )


// =====================================================================
// =====================================================================


    .def("setFunctionParam",
      &PyOpenFLUID::setFunctionParam,
      ( boost::python::arg("FuncID"), boost::python::arg("ParamName"),
        boost::python::arg("ParamValue") ),
      "Sets a function parameter value.\
\n - FuncID      : the simulation function id\
\n - ParamName   : the name of the parameter\
\n - ParamValue  : the parameter value\
\n\nExamples:\
\n\tPyOpenFLUID.setFunctionParam(\"my.function\",\"coeff\",\"3\")\
"
    )


// =====================================================================
// =====================================================================


    .def("getGeneratorParam", &PyOpenFLUID::getGeneratorParam,
      ( boost::python::arg("UnitClass"), boost::python::arg("VarName"),
        boost::python::arg("ParamName") ),
      "Returns a generator parameter value.\
\n - UnitClass  : the unit class to which the generator is applied\
\n - VarName    : the variable name to which the generator is applied\
\n - ParamName  : the name of the parameter\
\n\nExamples:\
\n\tVal = PyOpenFLUID.getGeneratorParam(\"SU\", \"var.flux\", \"fixedvalue\")\
"
    )


// =====================================================================
// =====================================================================


    .def("setGeneratorParam", &PyOpenFLUID::setGeneratorParam,
      ( boost::python::arg("UnitClass"), boost::python::arg("VarName"),
        boost::python::arg("ParamName"), boost::python::arg("ParamValue") ),
      "Sets a generator parameter value.\
\n - UnitClass   : the unit class to which the generator is applied\
\n - VarName     : the variable name to which the generator is applied\
\n - ParamName   : the name of the parameter\
\n - ParamValue  : the parameter value\
\n\nExamples:\
\n\tPyOpenFLUID.setGeneratorParam(\"SU\",\"var.flux\",\"fixedvalue\",\"12.3\")\
"
    )


// =====================================================================
// =====================================================================


    .def("getModelGlobalParam",
      &PyOpenFLUID::getModelGlobalParam,
      ( boost::python::arg("ParamName") ),
      "Returns a model global parameter value.\
\n - ParamName    : the name of the parameter\
\n\nExamples:\
\n\tVal = PyOpenFLUID.getModelGlobalParam(\"gvalue\")\
"
    )


// =====================================================================
// =====================================================================


    .def("setModelGlobalParam",
      &PyOpenFLUID::setModelGlobalParam,
      ( boost::python::arg("ParamName"), boost::python::arg("ParamValue") ),
      "Sets a model global parameter value.\
\n - ParamName   : the name of the parameter\
\n - ParamValue  : the parameter value\
\n\nExamples:\
\n\tPyOpenFLUID.setModelGlobalParam(\"gvalue\",\"37.2\")\
"
    )


// =====================================================================
/* ---------------------  MONITORING FUNCTIONS  --------------------- */


    .def("getObserverParam", &PyOpenFLUID::getObserverParam,
      ( boost::python::arg("ObsID"), boost::python::arg("ParamName") ),
      "Returns an observer parameter value.\
\n - ObsID      : the simulation function ID\
\n - ParamName  : the name of the parameter\
\n\nExamples:\
\n\tParam = PyOpenFLUID.getObserverParam\
"
    )


// =====================================================================
// =====================================================================


    .def("setObserverParam", &PyOpenFLUID::setObserverParam,
      ( boost::python::arg("ObsID"), boost::python::arg("ParamName"),
        boost::python::arg("ParamValue") ),
      "Sets an observer parameter value.\
\n - ObsID      : the simulation function ID\
\n - ParamName  : the name of the parameter\
\n - ParamName  : the parameter value\
\n\nExamples:\
\n\tParam = PyOpenFLUID.setObserverParam\
"
    )


// =====================================================================
// =====================================================================


    .def("getUnitsClasses", &PyOpenFLUID::getUnitsClasses,
      "Returns the existing units classes.\
\n\nExamples:\
\n\tCls = PyOpenFLUID.getUnitsClasses()\
"
    )


// =====================================================================
// =====================================================================


    .def("getUnitsIDs", &PyOpenFLUID::getUnitsIDs,
      ( boost::python::arg("UnitClass") ),
      "Returns the existing units IDs for a given units class.\
\n - UnitClass    : the unit class\
\n\nExamples:\
\n\tIds = PyOpenFLUID.getUnitsIDs(\"SU\")\
"
    )


// =====================================================================
// =====================================================================


    .def("createInputData", &PyOpenFLUID::createInputData,
      ( boost::python::arg("UnitClass"), boost::python::arg("IDataName"),
        boost::python::arg("IDataValue") ),
      "Creates an inputdata for alla spatial units of a class, initialized with\
a default value.\
\n - UnitClass    : the unit class\
\n - IDataName    : the inputdata name\
\n - IDataValue   : the default inputdata value for alla units\
\n\nExamples:\
\n\tPyOpenFLUID.createInputData(\"SU\",\"area\",\"1.0\")\
\n\tPyOpenFLUID.createInputData(\"SU\",\"code\",\"NONE\")\
"
    )


// =====================================================================
// =====================================================================


    .def("getInputData", &PyOpenFLUID::getInputData,
      ( boost::python::arg("UnitClass"), boost::python::arg("UnitID"),
        boost::python::arg("IDataName") ),
      "Returns an inputdata value for a given spatial unit.\
\n - UnitClass  : the unit class\
\n - UnitID     : the unit ID\
\n - IDataName  : the name of the inputdata\
\n\nExamples:\
\n\tVal = PyOpenFLUID.getInputData(\"SU\",18,\"length\")\
"
    )


// =====================================================================
// =====================================================================


    .def("setInputData", &PyOpenFLUID::setInputData,
      ( boost::python::arg("UnitClass"), boost::python::arg("UnitID"),
        boost::python::arg("IDataName"), boost::python::arg("IDataValue") ),
      "Sets an inputdata value for a given spatial unit.\
\n - UnitClass   : the unit class\
\n - UnitID      : the unit ID\
\n - IDataName   : the name of the inputdata\
\n - IDataValue  : the value of the inputdata\
\n\nExamples:\
\n\tPyOpenFLUID.setInputData(\"SU\",18,\"length\",\"12.3\")\
\n\tPyOpenFLUID.setInputData(\"SU\",18,\"CODE\",\"ABC\")\
"
    )


// =====================================================================
// =====================================================================


    .def("openDataset", &PyOpenFLUID::openDataset,
      ( boost::python::arg("Path") ),
      "Opens a dataset and returns a simulation definition class (self).\
\n - Path    : the full path of the dataset to open\
\n\nExamples:\
\n\tOfsim = PyOpenFLUID.openDataset(\"/path/to/dataset\")\
", boost::python::return_internal_reference<>()
    )


// =====================================================================
// =====================================================================


    .def("openProject", &PyOpenFLUID::openProject,
      ( boost::python::arg("Path") ),
      "Opens a project and returns a simulation definition class (PyOpenFLUID).\
\n - Path    : the full path of the project to open\
\n\nExamples:\
\n\tOfsim = PyOpenFLUID.openDataset(\"/path/to/project\")\
", boost::python::return_internal_reference<>()
    )


// =====================================================================
// =====================================================================


    .def("setCurrentOutputDir",
      &PyOpenFLUID::setCurrentOutputDir,
      ( boost::python::arg("Path") ),
      "Sets the current output directory for simulations.\
\n - Path    : the output directory path\
\n\nExamples:\
\n\tPyOpenFLUID.setCurrentOutputDir(\"/path/to/output\")\
"
    )


// =====================================================================
// =====================================================================


    .def("getCurrentOutputDir",
      &PyOpenFLUID::getCurrentOutputDir,
      "Gets the current output directory for simulations.\
\n\nExamples:\
\n\tPath = PyOpenFLUID.getCurrentOutputDir()\
"
    )


// =====================================================================
/* ---------------------  SIMULATION FUNCTIONS  --------------------- */


    .def("getDefaultDeltaT", &PyOpenFLUID::getDefaultDeltaT,
      "Returns the simulation time step.\
\n\nExamples:\
\n\tDeltaT = PyOpenFLUID.getDefaultDeltaT()\
"
    )


// =====================================================================
// =====================================================================


    .def("setDefaultDeltaT", &PyOpenFLUID::setDefaultDeltaT,
      ( boost::python::arg("DeltaT") ),
      "Sets the simulation time step.\
\n - DeltaT    : the time step value in seconds\
\n\nExamples:\
\n\tPyOpenFLUID.setDefaultDeltaT(60)\
\n\tPyOpenFLUID.setDefaultDeltaT(86400)\
"
    )


// =====================================================================
// =====================================================================


    .def("getPeriodBeginDate",
      &PyOpenFLUID::getPeriodBeginDate,
      "Returns the simulation period begin date.\
\n\nExamples:\
\n\tBDate = PyOpenFLUID.getPeriodBeginDate()\
"
    )


// =====================================================================
// =====================================================================


    .def("getPeriodEndDate", &PyOpenFLUID::getPeriodEndDate,
      "Returns the simulation period end date.\
\n\nExamples:\
\n\tEDate = PyOpenFLUID.getPeriodEndDate()\
"
    )


// =====================================================================
// =====================================================================


    .def("setPeriodBeginDate", &PyOpenFLUID::setPeriodBeginDate,
      ( boost::python::arg("BeginDate") ),
      "Sets the simulation period begin date.\
\n - BeginDate    : the begin date as an ISO datetime string\
 (%Y-%m-%d %H:%M:%S)\
\n\nExamples:\
\n\tPyOpenFLUID.setPeriodBeginDate(\"1997-06-05 04:00:00\")\
"
    )


// =====================================================================
// =====================================================================


    .def("setPeriodEndDate", &PyOpenFLUID::setPeriodEndDate,
      ( boost::python::arg("EndDate") ),
      "Sets the simulation period end date.\
\n - EndDate    : the end date as an ISO datetime string\
 (%Y-%m-%d %H:%M:%S)\
\n\nExamples:\
\n\tPyOpenFLUID.setPeriodEndDate(\"1997-06-05 16:07:17\")\
"
    )


// =====================================================================
// =====================================================================


    .def("runProject", &PyOpenFLUID::runProject,
      ( boost::python::arg("Path") ),
      "Runs a project and returns a simulation definition class (PyOpenFLUID).\
\n - Path    : the full path of the dataset to open\
\n\nExamples:\
\n\tOfsim = PyOpenFLUID.runProject(\"/path/to/dataset\")\
", boost::python::return_internal_reference<>()
    )


// =====================================================================
// =====================================================================


    .def("runSimulation", &PyOpenFLUID::runSimulation,
      "Runs a simulation from a simulation definition class (self).\
\n\nExamples:\
\n\tPyOpenFLUID.runSimulation()\
"
    )


// =====================================================================
// =====================================================================


//    .def("loadResult", &PyOpenFLUID::loadResult,
//      ( boost::python::arg("UnitClass"), boost::python::arg("UnitID"),
//        boost::python::arg("Suffix") ),
//      "Loads results as a dataframe, giving output dataset informations.\
//\n - UnitClass  : the unit class\
//\n - UnitID     : the unid ID\
//\n - Suffix     : the output dataset suffix\
//\n\nExamples:\
//\n\tResSU18 = PyOpenFLUID.loadResult(\"SU\",18,\"full\")\
//\n\tResRS1 = PyOpenFLUID.loadResult(\"RS\",1,\"waterlevel\")\
//", boost::python::return_internal_reference<>()
//    )


// =====================================================================
// =====================================================================


//    .def("loadResultFile", &PyOpenFLUID::loadResultFile,
//      ( boost::python::arg("FilePath") ),
//      "Loads results as a dataframe, giving output file name.\
//\n - FilePath    : the full path of the file to load\
//\n\nExamples:\
//\n\tResSU18 = PyOpenFLUID.loadResultFile(\"/path/to/output/SU18_full.out\")\
//\n\tResRS1 = PyOpenFLUID.loadResultFile(\"/path/to/output/RS1_waterlevel.out\")\
//", boost::python::return_internal_reference<>()
//    )


// =====================================================================
/* ------------------------ OTHER FUNCTIONS  ------------------------ */


    .def("_copy", &PyOpenFLUID::copy,
      ( boost::python::arg("InputClass") ),
      "Copy all attributs from the parameter in self.\
\n - InputClass    : the PyOpenFLUID class to copy\
"
    )

; /* end of PyOpenFLUID class definition */

}
