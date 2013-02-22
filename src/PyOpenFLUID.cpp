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
#include <openfluid/ware/PluggableWare.hpp>
#include <openfluid/fluidx/UnitDescriptor.hpp>
#include <openfluid/fluidx/FunctionDescriptor.hpp>
#include <openfluid/fluidx/GeneratorDescriptor.hpp>

#include <openfluid/fluidx/DomainDescriptor.hpp>
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
  this->m_CoupledModelDescriptor = openfluid::fluidx::CoupledModelDescriptor();
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
//  delete this->m_CoupledModelDescriptor;
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
  std::string Paths = convert::boostStrToCString(BoostPaths);
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
  std::vector<std::string> VectPath = openfluid::base::RuntimeEnvironment::getInstance()->
    getExtraFunctionsPluginsPaths();
  boost::python::list ListPath = boost::python::list();
  for (std::vector<std::string>::iterator IterVectPath = VectPath.begin();
       IterVectPath != VectPath.end(); ++IterVectPath)
    ListPath.append( boost::python::str(*IterVectPath) );
  return ListPath;
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::addExtraObserversPaths (boost::python::str BoostPaths)
{
  std::string Paths = convert::boostStrToCString(BoostPaths);
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
  std::vector<std::string> VectPath = openfluid::base::RuntimeEnvironment::getInstance()->
    getExtraObserversPluginsPaths();
  boost::python::list ListPath = boost::python::list();
  for (std::vector<std::string>::iterator IterVectPath = VectPath.begin();
       IterVectPath != VectPath.end(); ++IterVectPath)
    ListPath.append( boost::python::str(*IterVectPath) );
  return ListPath;
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::printSimulationInfo ()
{
  // Spatial domain
  openfluid::core::UnitClass_t ClassName;

  std::map<openfluid::core::UnitClass_t,unsigned int> UnitsInfos;

  std::list<openfluid::fluidx::UnitDescriptor>::iterator bItUnits = this->m_DomainDescriptor.getUnits().begin();
  std::list<openfluid::fluidx::UnitDescriptor>::iterator eItUnits = this->m_DomainDescriptor.getUnits().end();

  for (std::list<openfluid::fluidx::UnitDescriptor>::iterator ItUnits = bItUnits; ItUnits != eItUnits; ++ItUnits)
  {
    ClassName = (*ItUnits).getUnitClass();

    if (UnitsInfos.find(ClassName) == UnitsInfos.end()) UnitsInfos[ClassName] = 0;
      UnitsInfos[ClassName]++;
  }

  std::cout << "Spatial domain is made of " << this->m_DomainDescriptor.getUnits().size() << " spatial units" << std::endl;

  for (std::map<openfluid::core::UnitClass_t,unsigned int>::iterator ItUnitsInfos = UnitsInfos.begin(); ItUnitsInfos != UnitsInfos.end(); ++ItUnitsInfos)
    std::cout << " - " << (*ItUnitsInfos).second << " units of class " << (*ItUnitsInfos).first.c_str() << std::endl;


  // Model
  openfluid::fluidx::GeneratorDescriptor* pGenDesc;

  std::cout << "Model is made of " << this->m_CoupledModelDescriptor.getItems().size() << " simulation items" << std::endl;

  for (openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator ItModelInfos = this->m_CoupledModelDescriptor.getItems().begin(); ItModelInfos != this->m_CoupledModelDescriptor.getItems().end(); ++ItModelInfos)
  {
    fprintf(stdout, " - ");

    if ((*ItModelInfos)->isType(openfluid::fluidx::ModelItemDescriptor::PluggedFunction))
    {
      std::cout << ((openfluid::fluidx::FunctionDescriptor*)(*ItModelInfos))->getFileID().c_str() << " simulation function" << std::endl;
    }

    if ((*ItModelInfos)->isType(openfluid::fluidx::ModelItemDescriptor::Generator))
    {
      pGenDesc = ((openfluid::fluidx::GeneratorDescriptor*)(*ItModelInfos));

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
  std::string FuncIDStr = convert::boostStrToCString(FuncID);
  std::string ParamNameStr = convert::boostStrToCString(ParamName);

  openfluid::ware::WareParams_t Params;
  openfluid::ware::WareParams_t::iterator ItParam;

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator ItModelInfos = this->m_CoupledModelDescriptor.getItems().begin();

  boost::python::str* ResValue = NULL; /* makes Python NONE */

  while (ResValue == NULL && ItModelInfos != this->m_CoupledModelDescriptor.getItems().end())
  {
    if ((*ItModelInfos)->isType(openfluid::fluidx::ModelItemDescriptor::PluggedFunction) &&
        ((openfluid::fluidx::FunctionDescriptor*)(*ItModelInfos))->getFileID() == FuncIDStr)
    {
      Params = (*ItModelInfos)->getParameters();
      ItParam = Params.begin();
      while (ItParam != Params.end() && (*ItParam).first != ParamNameStr)
        ++ItParam;

      if (ItParam != Params.end())
        ResValue = new boost::python::str((*ItParam).second.data());
      break;
    }
    ++ItModelInfos;
  }

  return ResValue;
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::setFunctionParam (boost::python::str FuncID,
                                    boost::python::str ParamName,
                                    boost::python::str ParamValue)
{
  std::string FuncIDStr = convert::boostStrToCString(FuncID);
  std::string ParamNameStr = convert::boostStrToCString(ParamName);
  std::string ParamValStr = convert::boostStrToCString(ParamValue);

  openfluid::ware::WareParams_t Params;
  openfluid::ware::WareParams_t::iterator ItParam;

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator ItModelInfos = this->m_CoupledModelDescriptor.getItems().begin();

  boost::python::str* ResValue = NULL; /* makes Python NONE */

  while (ResValue == NULL && ItModelInfos != this->m_CoupledModelDescriptor.getItems().end())
  {
    if ((*ItModelInfos)->isType(openfluid::fluidx::ModelItemDescriptor::PluggedFunction) &&
        ((openfluid::fluidx::FunctionDescriptor*)(*ItModelInfos))->getFileID() == FuncIDStr)
    {
      (*ItModelInfos)->setParameter(ParamNameStr,ParamValStr);
      break;
    }
    ++ItModelInfos;
  }
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


boost::python::str PyOpenFLUID::getModelGlobalParam (
                                                  boost::python::str ParamName)
{
//  std::string ParamNameStr = convert::boostStrToCString(ParamName);
//  std::string ValueStr = this->m_CoupledModelDescriptor.getParameters(ParamNameStr);
//  return boost::python::str(ValueStr.c_str());
    return boost::python::str("");
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::setModelGlobalParam (boost::python::str ParamName,
                                       boost::python::str ParamValue)
{
//  std::string ParamNameStr = convert::boostStrToCString(ParamName));
//  std::string ParamValStr = convert::boostStrToCString(ParamValue);

//  this->m_CoupledModelDescriptor.setParameter(ParamNameStr,ParamValStr);
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


boost::python::list PyOpenFLUID::getUnitsClasses ()
{
  boost::python::list ListClasses = boost::python::list();
  std::list<openfluid::fluidx::UnitDescriptor> ListUnit =
    this->m_DomainDescriptor.getUnits();

  for (std::list<openfluid::fluidx::UnitDescriptor>::iterator IterUnit = ListUnit.begin();
       IterUnit != ListUnit.end(); ++IterUnit)
    ListClasses.append( boost::python::str( (*IterUnit).getUnitClass().c_str() ) );

  return ListClasses;
}

// =====================================================================
// =====================================================================


boost::python::list PyOpenFLUID::getUnitsIDs (boost::python::str UnitClass)
{
  std::string UnitClassRef = convert::boostStrToCString(UnitClass);
  boost::python::list ListID = boost::python::list();
  std::list<openfluid::fluidx::UnitDescriptor> ListUnit =
    this->m_DomainDescriptor.getUnits();

  for (std::list<openfluid::fluidx::UnitDescriptor>::iterator IterUnit = ListUnit.begin();
       IterUnit != ListUnit.end(); ++IterUnit)
    if ((*IterUnit).getUnitClass() == UnitClassRef )
      ListID.append( (*IterUnit).getUnitID() );

  return ListID;
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::createInputData (boost::python::str UnitClass,
                                   boost::python::str IDataName,
                                   boost::python::str IDataVal)
{
  std::string UnitClassStr = convert::boostStrToCString(UnitClass);
  std::string IDataNameStr = convert::boostStrToCString(IDataName);
  std::string IDataValStr = convert::boostStrToCString(IDataVal);

  std::list<openfluid::fluidx::InputDataDescriptor>& IData = this->m_DomainDescriptor.getInputData();

  for (std::list<openfluid::fluidx::InputDataDescriptor>::iterator ItIData = IData.begin();ItIData != IData.end();++ItIData)
  {
    if ((*ItIData).getUnitsClass() == UnitClassStr)
    {
      openfluid::fluidx::InputDataDescriptor::UnitIDInputData_t::iterator ItUnitData = (*ItIData).getData().begin();

      for (ItUnitData;ItUnitData!=(*ItIData).getData().end();++ItUnitData)
        (*ItUnitData).second[IDataNameStr] = IDataValStr;
    }
  }
}

// =====================================================================
// =====================================================================


boost::python::str* PyOpenFLUID::getInputData (boost::python::str UnitClass,
                                               int UnitID,
                                               boost::python::str IDataName)
{
  std::string UnitClassStr = convert::boostStrToCString(UnitClass);
  std::string IDataNameStr = convert::boostStrToCString(IDataName);

  std::list<openfluid::fluidx::InputDataDescriptor>& IData = this->m_DomainDescriptor.getInputData();

  for (std::list<openfluid::fluidx::InputDataDescriptor>::iterator ItIData = IData.begin();ItIData != IData.end();++ItIData)
  {
    if ((*ItIData).getUnitsClass() == UnitClassStr)
    {
      openfluid::fluidx::InputDataDescriptor::UnitIDInputData_t::const_iterator ItUnitData = (*ItIData).getData().find(UnitID);
      if (ItUnitData != (*ItIData).getData().end())
      {
        if ((*ItUnitData).second.find(IDataNameStr) != (*ItUnitData).second.end())
          return new boost::python::str((*ItUnitData).second.at(IDataNameStr).c_str());
      }
    }
  }

  return NULL; /* return python None */
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::setInputData (boost::python::str UnitClass, int UnitID,
                                boost::python::str IDataName,
                                boost::python::str IDataValue)
{
  std::string UnitClassStr = convert::boostStrToCString(UnitClass);
  std::string IDataNameStr = convert::boostStrToCString(IDataName);
  std::string IDataValStr = convert::boostStrToCString(IDataValue);

  std::list<openfluid::fluidx::InputDataDescriptor>& IData = this->m_DomainDescriptor.getInputData();

  for (std::list<openfluid::fluidx::InputDataDescriptor>::iterator ItIData = IData.begin();ItIData != IData.end();++ItIData)
  {
    if ((*ItIData).getUnitsClass() == UnitClassStr)
    {
      openfluid::fluidx::InputDataDescriptor::UnitIDInputData_t::iterator ItUnitData = (*ItIData).getData().find(UnitID);
      if (ItUnitData != (*ItIData).getData().end())
      {
        if ((*ItUnitData).second.find(IDataNameStr) != (*ItUnitData).second.end())
          (*ItUnitData).second[IDataNameStr] = IDataValStr;
      }
    }
  }
}

// =====================================================================
/* --------------------  INPUT OUTPUT FUNCTIONS  -------------------- */


PyOpenFLUID* PyOpenFLUID::openDataset (boost::python::str Path)
{
  std::string StrError = std::string("");
  std::string StrPath = convert::boostStrToCString(Path);
  PyOpenFLUID* ResClass = new PyOpenFLUID();

  try
  {
//    openfluid::base::Init();

//    openfluid::io::IOListener IOListen;
//    openfluid::io::FluidXReader FXReader(&IOListen);


//    openfluid::base::RuntimeEnvironment::getInstance()->setInputDir(std::string(StrPath));
//    FXReader.loadFromDirectory(openfluid::base::RuntimeEnvironment::getInstance()->getInputDir());

//    this->m_IsSimulationRun = false;

//    this->m_DomainDescriptor = FXReader.getDomainDescriptor();
//    this->m_CoupledModelDescriptor = FXReader.getModelDescriptor();
//    this->m_DatastoreDescriptor = FXReader.getDatstoreDescriptor();
//    this->m_MonitoringDescriptor = FXReader.getOutputDescriptor();
//    this->m_RunDescr = FXReader.getRunDescriptor();

//    if (!this->IsProject)
//    {
//      this->IsDataset = true;
//      this->SourcePath = openfluid::base::RuntimeEnvironment::getInstance()->getInputDir();
//    }

    return ResClass;
  }
  catch (openfluid::base::OFException& E)
  {
    StrError = std::string("PyOpenFLUID ERROR: ") + std::string(E.what());
  }
  catch (std::bad_alloc& E)
  {
    StrError = std::string("MEMORY ALLOCATION ERROR: ") + std::string(E.what()) + std::string(". Possibly not enough memory available");
  }
  catch (std::exception& E)
  {
    StrError = std::string("SYSTEM ERROR: ") + std::string(E.what());
  }
  catch (...)
  {
    StrError = std::string("UNKNOWN ERROR");
  }
//  this->IsProject = false;
//  this->IsDataset = false;
//  this->SourcePath = "";

  if (StrError.length() != 0)
  {
    PyOFException* error = new PyOFException(StrError.c_str());
    throw *error;
  }

  return NULL;
}

// =====================================================================
// =====================================================================


PyOpenFLUID* PyOpenFLUID::openProject (boost::python::str Path)
{
  std::string StrError = std::string("");
  std::string StrPath = convert::boostStrToCString(Path);

  try
  {
//    openfluid::base::Init();

//    openfluid::io::IOListener IOListen;

//    if (openfluid::base::ProjectManager::getInstance()->open(StrPath))
//    {
//      openfluid::base::RuntimeEnvironment::getInstance()->linkToProject();
//      openfluid::base::ProjectManager::getInstance()->updateOutputDir();
//    }
//    else
//      throw openfluid::base::OFException("PyOpenFLUID", StrPath + " is not a correct project path");

//    this->IsProject = true;
//    this->SourcePath = openfluid::base::ProjectManager::getInstance()->getPath();

    return this->openDataset(openfluid::base::RuntimeEnvironment::getInstance()->getInputDir().c_str());
  }
  catch (openfluid::base::OFException& E)
  {
    StrError = std::string("PyOpenFLUID ERROR: ") + std::string(E.what());
  }
  catch (std::bad_alloc& E)
  {
    StrError = std::string("MEMORY ALLOCATION ERROR: ") + std::string(E.what()) + std::string(". Possibly not enough memory available");
  }
  catch (std::exception& E)
  {
    StrError = std::string("SYSTEM ERROR: ") + std::string(E.what());
  }
  catch (...)
  {
    StrError = std::string("UNKNOWN ERROR");
  }
//  this->IsProject = false;
//  this->IsDataset = false;
//  this->SourcePath = "";

  if (StrError.length() != 0)
  {
    PyOFException* error = new PyOFException(StrError.c_str());
    throw *error;
  }

  return NULL;
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::setCurrentOutputDir (boost::python::str Path)
{
  openfluid::base::RuntimeEnvironment::getInstance()->setOutputDir(
     convert::boostStrToCString(Path));
}

// =====================================================================
// =====================================================================


boost::python::str PyOpenFLUID::getCurrentOutputDir ()
{
  boost::python::str Path = boost::python::str(openfluid::base::RuntimeEnvironment::getInstance()->getOutputDir());
  return Path;
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


unsigned short int PyOpenFLUID::runSimulation ()
{
  std::string StrError("");
  try
  {
//    openfluid::base::Init();

//    openfluid::machine::Engine* Engine;

//    UpdateOutputsConfig(BlobHandle);

//    openfluid::io::IOListener IOListen;
//    openfluid::machine::SimulationBlob SimBlob;

//    openfluid::machine::PluginManager::getInstance()->unloadAllPlugins();


//    openfluid::machine::Factory::buildSimulationBlobFromDescriptors(
//        this->m_DomainDescriptor,
//        this->m_RunDescriptor,
//        this->m_OutDesc,
//        this->m_DataStoreDesc,
//        SimBlob);


//    openfluid::machine::MachineListener MachineListen;
//    openfluid::machine::ModelInstance Model(SimBlob, &MachineListen);

//    openfluid::machine::Factory::buildModelInstanceFromDescriptor(this->m_ModelDescriptor,
//        Model);

//    this->m_OutputDir = openfluid::base::RuntimeEnvironment::getInstance()->getOutputDir();

//    Engine = new openfluid::machine::Engine(SimBlob, Model, &MachineListen, &IOListen);

//    Engine->initialize();

//    Engine->initParams();
//    Engine->prepareData();
//    Engine->checkConsistency();
//    Engine->run();
//    Engine->saveReports();

//    Engine->finalize();

//    delete Engine;

//    this->m_IsSimulationRun = true;

    return 1;
  }
  catch (openfluid::base::OFException& E)
  {
    StrError = "OpenFLUID ERROR: " + std::string(E.what()) +"\n";
  }
  catch (std::bad_alloc& E)
  {
    StrError = "MEMORY ALLOCATION ERROR: " + std::string(E.what()) + ". Possibly not enough memory available\n";
  }
  catch (std::exception& E)
  {
    StrError = "SYSTEM ERROR: " + std::string(E.what()) +"\n";
  }
  catch (...)
  {
    StrError = "UNKNOWN ERROR\n";
  }

  if (StrError.length() != 0)
  {
    PyOFException* error = new PyOFException(StrError.c_str());
    throw *error;
  }

  return 0;
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


// =====================================================================
/* ------------------------ OTHER FUNCTIONS  ------------------------ */


void PyOpenFLUID::copy (PyOpenFLUID InputClass)
{
  this->m_DomainDescriptor = InputClass.m_DomainDescriptor;
  this->m_DatastoreDescriptor = InputClass.m_DatastoreDescriptor;
  this->m_CoupledModelDescriptor = InputClass.m_CoupledModelDescriptor;
  this->m_MonitoringDescriptor = InputClass.m_MonitoringDescriptor;
  this->m_RunDescriptor = InputClass.m_RunDescriptor;
}
