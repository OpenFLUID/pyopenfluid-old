#include <Python.h>
#include <boost/python.hpp>
#include <boost/exception/all.hpp>

#include <vector>
#include <string>
#include <exception>

#include <openfluid/config.hpp>

#include "PyOpenFLUID.hpp"
#include "PyOpenFLUIDError.hpp"
#include "Convert.hpp"


// =====================================================================
// =====================================================================



PyOpenFLUID::PyOpenFLUID ()
{
}


// =====================================================================
// =====================================================================


PyOpenFLUID::~PyOpenFLUID ()
{
}


// =====================================================================
/* ----------------------  GENERAL FUNCTIONS  ----------------------- */


boost::python::str* PyOpenFLUID::getVersion ()
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::addExtraFunctionsPaths (boost::python::str BoostPaths)
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::resetExtraFunctionsPaths ()
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
// =====================================================================


boost::python::list* PyOpenFLUID::getExtraFunctionsPaths ()
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::addExtraObserversPaths (boost::python::str BoostPaths)
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::resetExtraObserversPaths ()
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}


// =====================================================================
// =====================================================================


boost::python::list* PyOpenFLUID::getExtraObserversPaths ()
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::printSimulationInfo ()
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
/* ------------------------  MODEL FUNCTIONS  ----------------------- */


boost::python::str* PyOpenFLUID::getFunctionParam (boost::python::str FuncID,
                                                   boost::python::str ParamName)
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::setFunctionParam (boost::python::str FuncID,
                                    boost::python::str ParamName,
                                    boost::python::str ParamValue)
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
// =====================================================================


boost::python::str* PyOpenFLUID::getGeneratorParam (
                                                  boost::python::str UnitClass,
                                                  boost::python::str VarName,
                                                  boost::python::str ParamName)
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::setGeneratorParam (boost::python::str UnitClass,
                                     boost::python::str VarName,
                                     boost::python::str ParamName,
                                     boost::python::str ParamValue)
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
// =====================================================================


boost::python::str* PyOpenFLUID::getModelGlobalParam (
                                                  boost::python::str ParamName)
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::setModelGlobalParam (boost::python::str ParamName,
                                       boost::python::str ParamValue)
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
/* ---------------------  MONITORING FUNCTIONS  --------------------- */


boost::python::str* PyOpenFLUID::getObserverParam (boost::python::str ObsID,
                                                   boost::python::str ParamName)
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::setObserverParam (boost::python::str ObsID,
                                    boost::python::str ParamName,
                                    boost::python::str ParamValue)
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
/* -------------------  SPATIAL DOMAIN FUNCTIONS  ------------------- */


boost::python::list* PyOpenFLUID::getUnitsClasses ()
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
// =====================================================================


boost::python::list* PyOpenFLUID::getUnitsIDs (boost::python::str UnitClass)
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::createInputData (boost::python::str UnitClass,
                                   boost::python::str IDataName,
                                   boost::python::str IDataVal)
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
// =====================================================================


boost::python::str* PyOpenFLUID::getInputData (boost::python::str UnitClass,
                                               int UnitID,
                                               boost::python::str IDataName)
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::setInputData (boost::python::str UnitClass, int UnitID,
                                boost::python::str IDataName,
                                boost::python::str IDataValue)
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
/* --------------------  INPUT OUTPUT FUNCTIONS  -------------------- */


PyOpenFLUID* PyOpenFLUID::openDataset (boost::python::str Path)
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
// =====================================================================


PyOpenFLUID* PyOpenFLUID::openProject (boost::python::str Path)
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::setCurrentOutputDir (boost::python::str Path)
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
/* ---------------------  SIMULATION FUNCTIONS  --------------------- */


int PyOpenFLUID::getDefaultDeltaT ()
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::setDefaultDeltaT (int DeltaT)
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}


// =====================================================================
// =====================================================================


boost::python::str* PyOpenFLUID::getPeriodBeginDate ()
{
  throw new PyOFException("unavailable method");
}

// =====================================================================
// =====================================================================


boost::python::str* PyOpenFLUID::getPeriodEndDate ()
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::setPeriodBeginDate (boost::python::str BeginDate)
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::setPeriodEndDate (boost::python::str EndDate)
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
// =====================================================================


PyOpenFLUID* PyOpenFLUID::runProject (boost::python::str Path)
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::runSimulation ()
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
// =====================================================================


PyOpenFLUID* PyOpenFLUID::loadResult (boost::python::str UnitClass,
                                           int UnitID,
                                           boost::python::str Suffix)
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}

// =====================================================================
// =====================================================================


PyOpenFLUID* PyOpenFLUID::loadResultFile (boost::python::str FilePath)
{
  PyOFException* error = new PyOFException("unavailable method");
  throw *error;
}
