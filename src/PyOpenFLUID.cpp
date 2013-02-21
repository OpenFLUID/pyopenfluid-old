#include <Python.h>
#include <boost/python.hpp>
#include <boost/exception/all.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <exception>

#include <stdio.h>

#include <openfluid/config.hpp>
#include <openfluid/base.hpp>
#include <openfluid/core.hpp>
//#include <openfluid/fluidx.hpp>
#include <openfluid/fluidx/UnitDescriptor.hpp>
#include <openfluid/fluidx/FunctionDescriptor.hpp>
#include <openfluid/fluidx/GeneratorDescriptor.hpp>

#include <openfluid/fluidx/DatastoreDescriptor.hpp>
#include <openfluid/fluidx/CoupledModelDescriptor.hpp>
#include <openfluid/fluidx/MonitoringDescriptor.hpp>
#include <openfluid/fluidx/RunDescriptor.hpp>

#include "PyOpenFLUID.hpp"
#include "PyOpenFLUIDError.hpp"
#include "Convert.hpp"


// =====================================================================
// =====================================================================



PyOpenFLUID::PyOpenFLUID ()
{
//  std::cout << "Création de l'objet OpenFLUID." << std::endl;
  this->m_DomainDescriptor = openfluid::fluidx::DomainDescriptor();
  this->m_DatastoreDescriptor = openfluid::fluidx::DatastoreDescriptor();
  this->m_ModelDescriptor = openfluid::fluidx::CoupledModelDescriptor();
  this->m_MonitoringDescriptor = openfluid::fluidx::MonitoringDescriptor();
  this->m_RunDescriptor = openfluid::fluidx::RunDescriptor();
}


// =====================================================================
// =====================================================================


PyOpenFLUID::~PyOpenFLUID ()
{
//  std::cout << "Destruction de l'objet OpenFLUID." << std::endl;
//  delete this->m_DomainDescriptor;
//  delete this->m_DatastoreDescriptor;
//  delete this->m_ModelDescriptor;
//  delete this->m_MonitoringDescriptor;
//  delete this->m_RunDescriptor;
}


// =====================================================================
/* ----------------------  GENERAL FUNCTIONS  ----------------------- */


boost::python::str PyOpenFLUID::getVersion ()
{
  boost::python::str StrVersion = boost::python::str((const char*)
    openfluid::config::FULL_VERSION.c_str());
  return StrVersion;
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::addExtraFunctionsPaths (boost::python::str BoostPaths)
{
  std::string Paths = *convert::boostStrToCString(&BoostPaths);
  openfluid::base::RuntimeEnvironment::getInstance()->
    addExtraFunctionsPluginsPaths(Paths);
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::resetExtraFunctionsPaths ()
{
  openfluid::base::RuntimeEnvironment::getInstance()->
    resetExtraFunctionsPluginsPaths();
}

// =====================================================================
// =====================================================================


boost::python::list PyOpenFLUID::getExtraFunctionsPaths ()
{
  std::vector<std::string> Paths = openfluid::base::RuntimeEnvironment::getInstance()->
    getExtraFunctionsPluginsPaths();
  return *convert::cVectorToBoostListOfString(&Paths);
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::addExtraObserversPaths (boost::python::str BoostPaths)
{
  std::string Paths = *convert::boostStrToCString(&BoostPaths);
  openfluid::base::RuntimeEnvironment::getInstance()->
    addExtraObserversPluginsPaths(Paths);
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::resetExtraObserversPaths ()
{
  openfluid::base::RuntimeEnvironment::getInstance()->
    resetExtraObserversPluginsPaths();
}


// =====================================================================
// =====================================================================


boost::python::list PyOpenFLUID::getExtraObserversPaths ()
{
  std::vector<std::string> Paths = openfluid::base::RuntimeEnvironment::getInstance()->
    getExtraObserversPluginsPaths();
  return *convert::cVectorToBoostListOfString(&Paths);
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::printSimulationInfo ()
{
  // Spatial domain

  std::map<openfluid::core::UnitClass_t,unsigned int> UnitsInfos;

  std::list<openfluid::fluidx::UnitDescriptor>::iterator bItUnits = this->m_DomainDescriptor.getUnits().begin();
  std::list<openfluid::fluidx::UnitDescriptor>::iterator eItUnits = this->m_DomainDescriptor.getUnits().end();

  for (std::list<openfluid::fluidx::UnitDescriptor>::iterator ItUnits = bItUnits; ItUnits != eItUnits; ++ItUnits)
  {
    openfluid::core::UnitClass_t ClassName = (*ItUnits).getUnitClass();

    if (UnitsInfos.find(ClassName) == UnitsInfos.end()) UnitsInfos[ClassName] = 0;
      UnitsInfos[ClassName]++;
  }

  std::cout << "Spatial domain is made of " << this->m_DomainDescriptor.getUnits().size() << " spatial units" << std::endl;

  for (std::map<openfluid::core::UnitClass_t,unsigned int>::iterator ItUnitsInfos = UnitsInfos.begin();
       ItUnitsInfos != UnitsInfos.end(); ++ItUnitsInfos)
    std::cout << " - " << (*ItUnitsInfos).second << " units of class " << (*ItUnitsInfos).first.c_str() << std::endl;


  // Model

  std::cout << "Model is made of " << this->m_ModelDescriptor.getItems().size() << " simulation items" << std::endl;

  for (openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator ItModelInfos = this->m_ModelDescriptor.getItems().begin(); ItModelInfos != this->m_ModelDescriptor.getItems().end(); ++ItModelInfos)
  {
    fprintf(stdout, " - ");

    if ((*ItModelInfos)->isType(openfluid::fluidx::ModelItemDescriptor::PluggedFunction))
    {
      std::cout << ((openfluid::fluidx::FunctionDescriptor*)(*ItModelInfos))->getFileID().c_str() << " simulation function" << std::endl;
    }

    if ((*ItModelInfos)->isType(openfluid::fluidx::ModelItemDescriptor::Generator))
    {
      openfluid::fluidx::GeneratorDescriptor* pGenDesc = ((openfluid::fluidx::GeneratorDescriptor*)(*ItModelInfos));

      if (pGenDesc->getGeneratorMethod() == openfluid::fluidx::GeneratorDescriptor::Fixed)
        std::cout << "fixed";

      if (pGenDesc->getGeneratorMethod() == openfluid::fluidx::GeneratorDescriptor::Random)
        std::cout << "random";

      if (pGenDesc->getGeneratorMethod() == openfluid::fluidx::GeneratorDescriptor::Interp)
        std::cout << "interp";

      if (pGenDesc->getGeneratorMethod() == openfluid::fluidx::GeneratorDescriptor::Inject)
        std::cout << "inject";

      std::cout << " generator for variable " << pGenDesc->getVariableName().c_str() << " on units " << pGenDesc->getUnitClass().c_str() << std::endl;
    }
  }

  // Time period

  std::cout << "Simulation period from " << this->m_RunDescriptor.getBeginDate().getAsISOString().c_str() << " to " << this->m_RunDescriptor.getEndDate().getAsISOString().c_str() << std::endl;

  // Time step

  std::cout << "Simulation time step : " << this->m_RunDescriptor.getDeltaT() << std::endl;
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
  int DefaultDeltaT = this->m_RunDescriptor.getDeltaT();
  return DefaultDeltaT;
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::setDefaultDeltaT (int DefaultDeltaT)
{
  this->m_RunDescriptor.setDeltaT((const int)DefaultDeltaT);
}


// =====================================================================
// =====================================================================


boost::python::dict PyOpenFLUID::getPeriodBeginDate ()
{
  openfluid::core::DateTime BrutDate = this->m_RunDescriptor.getBeginDate();
  boost::python::dict DictDate = boost::python::dict();
  DictDate["year"] = BrutDate.getYear();
  DictDate["month"] = BrutDate.getMonth();
  DictDate["day"] = BrutDate.getDay();
  DictDate["hour"] = BrutDate.getHour();
  DictDate["minute"] = BrutDate.getMinute();
  DictDate["second"] = BrutDate.getSecond();
  return DictDate;
}

// =====================================================================
// =====================================================================


boost::python::dict PyOpenFLUID::getPeriodEndDate ()
{
  openfluid::core::DateTime BrutDate = this->m_RunDescriptor.getEndDate();
  boost::python::dict DictDate = boost::python::dict();
  DictDate["year"] = BrutDate.getYear();
  DictDate["month"] = BrutDate.getMonth();
  DictDate["day"] = BrutDate.getDay();
  DictDate["hour"] = BrutDate.getHour();
  DictDate["minute"] = BrutDate.getMinute();
  DictDate["second"] = BrutDate.getSecond();
  return DictDate;
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::setPeriodBeginDate (int BYear, int BMonth, int BDay,
                                      int BHour, int BMinute, int BSecond)
{
  openfluid::core::DateTime BDate = openfluid::core::DateTime(BYear, BMonth,
                                      BDay, BHour, BMinute, BSecond);
  this->m_RunDescriptor.setBeginDate(BDate);
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::setPeriodEndDate (int EYear, int EMonth, int EDay,
                                    int EHour, int EMinute, int ESecond)
{
  openfluid::core::DateTime EDate = openfluid::core::DateTime(EYear, EMonth,
                                      EDay, EHour, EMinute, ESecond);
  this->m_RunDescriptor.setEndDate(EDate);
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
