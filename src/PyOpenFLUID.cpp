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
#include <openfluid/machine.hpp>
#include <openfluid/ware.hpp>

/* TODO delete when compilation runs perfectly */
#include <openfluid/machine/MonitoringInstance.hpp>
#include <openfluid/machine/ObserverPluginsManager.hpp>
#include <openfluid/fluidx/UnitDescriptor.hpp>
#include <openfluid/fluidx/FunctionDescriptor.hpp>
#include <openfluid/fluidx/ObserverDescriptor.hpp>
#include <openfluid/fluidx/GeneratorDescriptor.hpp>
#include <openfluid/fluidx/FluidXDescriptor.hpp>
#include <openfluid/fluidx/DomainDescriptor.hpp>
#include <openfluid/fluidx/DatastoreDescriptor.hpp>
#include <openfluid/fluidx/CoupledModelDescriptor.hpp>
#include <openfluid/fluidx/MonitoringDescriptor.hpp>
#include <openfluid/fluidx/RunDescriptor.hpp>
/* end todo */

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
}


// =====================================================================
/* ----------------------  GENERAL FUNCTIONS  ----------------------- */


boost::python::object PyOpenFLUID::getVersion ()
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


boost::python::object PyOpenFLUID::getExtraFunctionsPaths ()
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


boost::python::object PyOpenFLUID::getExtraObserversPaths ()
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

      else if (pGenDesc->getGeneratorMethod() == openfluid::fluidx::GeneratorDescriptor::Random)
        std::cout << "random";

      else if (pGenDesc->getGeneratorMethod() == openfluid::fluidx::GeneratorDescriptor::Interp)
        std::cout << "interp";

      else if (pGenDesc->getGeneratorMethod() == openfluid::fluidx::GeneratorDescriptor::Inject)
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


boost::python::object PyOpenFLUID::getFunctionParam (boost::python::str FuncID,
                                                   boost::python::str ParamName)
{
  std::string FuncIDStr = convert::boostStrToCString(FuncID);
  std::string ParamNameStr = convert::boostStrToCString(ParamName);

  openfluid::ware::WareParams_t Params;
  openfluid::ware::WareParams_t::iterator ItParam;

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator ItModelInfos = this->m_CoupledModelDescriptor.getItems().begin();

  while (ItModelInfos != this->m_CoupledModelDescriptor.getItems().end())
  {
    if ((*ItModelInfos)->isType(openfluid::fluidx::ModelItemDescriptor::PluggedFunction) &&
        ((openfluid::fluidx::FunctionDescriptor*)(*ItModelInfos))->getFileID() == FuncIDStr)
    {
      Params = (*ItModelInfos)->getParameters();
      ItParam = Params.begin();
      while (ItParam != Params.end() && (*ItParam).first != ParamNameStr)
        ++ItParam;

      if (ItParam != Params.end())
        return boost::python::str((*ItParam).second.data());
      break;
    }
    ++ItModelInfos;
  }

  return boost::python::object(); /* makes Python NONE */
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::setFunctionParam (boost::python::str FuncID,
                                    boost::python::str ParamName,
                                    boost::python::str ParamValue)
{
  std::string FuncIDStr = convert::boostStrToCString(FuncID);
  std::string ParamNameStr = convert::boostStrToCString(ParamName);
  std::string ParamValueStr = convert::boostStrToCString(ParamValue);

  openfluid::ware::WareParams_t Params;
  openfluid::ware::WareParams_t::iterator ItParam;

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t ModelInfos = this->m_CoupledModelDescriptor.getItems();
  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator ItModelInfos = ModelInfos.begin();

  while (ItModelInfos != ModelInfos.end())
  {
    if ((*ItModelInfos)->isType(openfluid::fluidx::ModelItemDescriptor::PluggedFunction) &&
        ((openfluid::fluidx::FunctionDescriptor*)(*ItModelInfos))->getFileID() == FuncIDStr)
    {
      (*ItModelInfos)->setParameter(ParamNameStr,ParamValueStr);
      break;
    }
    ++ItModelInfos;
  }
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getGeneratorParam (
                                                  boost::python::str UnitClass,
                                                  boost::python::str VarName,
                                                  boost::python::str ParamName)
{
  std::string UnitClassStr = convert::boostStrToCString(UnitClass);
  std::string VarNameStr = convert::boostStrToCString(VarName);
  std::string ParamNameStr = convert::boostStrToCString(ParamName);

  openfluid::ware::WareParams_t Params;
  openfluid::ware::WareParams_t::iterator ItParam;

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator ItModelInfos = this->m_CoupledModelDescriptor.getItems().begin();

  openfluid::fluidx::GeneratorDescriptor* GenDescp;

  while (ItModelInfos != this->m_CoupledModelDescriptor.getItems().end())
  {
    if ((*ItModelInfos)->isType(openfluid::fluidx::ModelItemDescriptor::Generator))
    {
      GenDescp = (openfluid::fluidx::GeneratorDescriptor*)(*ItModelInfos);
      if (GenDescp->getUnitClass() == UnitClassStr && GenDescp->getVariableName() == VarNameStr)
      {
        Params = GenDescp->getParameters();
        ItParam = Params.begin();

        while (ItParam != Params.end() && (*ItParam).first != ParamNameStr)
          ++ItParam;

        if (ItParam != Params.end())
          return boost::python::str((*ItParam).second.data());
        break;
      }
    }
    ++ItModelInfos;
  }

  return boost::python::object(); /* makes Python NONE */
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::setGeneratorParam (boost::python::str UnitClass,
                                     boost::python::str VarName,
                                     boost::python::str ParamName,
                                     boost::python::str ParamValue)
{
  std::string UnitClassStr = convert::boostStrToCString(UnitClass);
  std::string VarNameStr = convert::boostStrToCString(VarName);
  std::string ParamNameStr = convert::boostStrToCString(ParamName);
  std::string ParamValueStr = convert::boostStrToCString(ParamValue);

  openfluid::ware::WareParams_t Params;
  openfluid::ware::WareParams_t::iterator ItParam;

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator ItModelInfos = this->m_CoupledModelDescriptor.getItems().begin();

  openfluid::fluidx::GeneratorDescriptor* GenDescp;

  while (ItModelInfos != this->m_CoupledModelDescriptor.getItems().end())
  {
    if ((*ItModelInfos)->isType(openfluid::fluidx::ModelItemDescriptor::Generator))
    {
      GenDescp = (openfluid::fluidx::GeneratorDescriptor*)(*ItModelInfos);
      if (GenDescp->getUnitClass() == UnitClassStr && GenDescp->getVariableName() == VarNameStr)
      {
        GenDescp->setParameter(ParamNameStr, ParamValueStr);
        break;
      }
    }
    ++ItModelInfos;
  }
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getModelGlobalParam (
                                                  boost::python::str ParamName)
{
  std::string ParamNameStr = convert::boostStrToCString(ParamName);

  openfluid::ware::WareParams_t Params = this->m_CoupledModelDescriptor.getGlobalParameters();
  openfluid::ware::WareParams_t::iterator ItParam = Params.begin();

  boost::python::str ResValue; /* makes Python NONE */

  while (ItParam != Params.end() && (*ItParam).first != ParamNameStr)
    ++ItParam;

  if (ItParam != Params.end())
    return boost::python::str((*ItParam).second.data());

  return boost::python::object(); /* makes Python NONE */
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::setModelGlobalParam (boost::python::str ParamName,
                                       boost::python::str ParamValue)
{
  openfluid::ware::WareParamKey_t ParamNameStr =
      (openfluid::ware::WareParamKey_t) convert::boostStrToCString(ParamName);
  openfluid::ware::WareParamValue_t ParamValueStr =
      (openfluid::ware::WareParamValue_t) convert::boostStrToCString(ParamValue);

  this->m_CoupledModelDescriptor.setGlobalParameter(ParamNameStr,ParamValueStr);
}


// =====================================================================
/* ---------------------  MONITORING FUNCTIONS  --------------------- */


boost::python::object PyOpenFLUID::getObserverParam (boost::python::str ObsID,
                                                   boost::python::str ParamName)
{
  std::string ObsIDStr = convert::boostStrToCString(ObsID);
  std::string ParamNameStr = convert::boostStrToCString(ParamName);

  openfluid::ware::WareParams_t Params;
  openfluid::ware::WareParams_t::iterator ItParam;

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator ItModelInfos = this->m_CoupledModelDescriptor.getItems().begin();

  openfluid::fluidx::ObserverDescriptor* ObsDescp;

  while (ItModelInfos != this->m_CoupledModelDescriptor.getItems().end())
  {
    if ((*ItModelInfos)->isType(openfluid::fluidx::ModelItemDescriptor::PluggedObserver))
    {
      ObsDescp = (openfluid::fluidx::ObserverDescriptor*)(*ItModelInfos);
      if (ObsDescp->getID() == ObsIDStr)
      {
        Params = ObsDescp->getParameters();
        ItParam = Params.begin();

        while (ItParam != Params.end() && (*ItParam).first != ParamNameStr)
          ++ItParam;

        if (ItParam != Params.end())
          return boost::python::str((*ItParam).second.data());
        break;
      }
    }
    ++ItModelInfos;
  }

  return boost::python::object(); /* makes Python NONE */
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::setObserverParam (boost::python::str ObsID,
                                    boost::python::str ParamName,
                                    boost::python::str ParamValue)
{
  std::string ObsIDStr = convert::boostStrToCString(ObsID);
  std::string ParamNameStr = convert::boostStrToCString(ParamName);
  std::string ParamValueStr = convert::boostStrToCString(ParamValue);

  openfluid::ware::WareParams_t Params;
  openfluid::ware::WareParams_t::iterator ItParam;

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator ItModelInfos = this->m_CoupledModelDescriptor.getItems().begin();

  openfluid::fluidx::ObserverDescriptor* ObsDescp;

  while (ItModelInfos != this->m_CoupledModelDescriptor.getItems().end())
  {
    if ((*ItModelInfos)->isType(openfluid::fluidx::ModelItemDescriptor::PluggedObserver))
    {
      ObsDescp = (openfluid::fluidx::ObserverDescriptor*)(*ItModelInfos);
      if (ObsDescp->getID() == ObsIDStr)
      {
        ObsDescp->setParameter(ParamNameStr, ParamValueStr);
        break;
      }
    }
    ++ItModelInfos;
  }
}


// =====================================================================
/* -------------------  SPATIAL DOMAIN FUNCTIONS  ------------------- */


boost::python::object PyOpenFLUID::getUnitsClasses ()
{
  boost::python::list ListClasses = boost::python::list();
  std::list<openfluid::fluidx::UnitDescriptor> ListUnit =
    this->m_DomainDescriptor.getUnits();

  for (std::list<openfluid::fluidx::UnitDescriptor>::iterator IterUnit = ListUnit.begin();
       IterUnit != ListUnit.end(); ++IterUnit)
    ListClasses.append(boost::python::str((*IterUnit).getUnitClass()));

  return ListClasses;
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getUnitsIDs (boost::python::str UnitClass)
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


boost::python::object PyOpenFLUID::getInputData (boost::python::str UnitClass,
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
          return boost::python::str((*ItUnitData).second.at(IDataNameStr));
      }
    }
  }

  return boost::python::object(); /* makes Python NONE */
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
    openfluid::base::Init();

    openfluid::base::IOListener IOListen;
    openfluid::fluidx::FluidXDescriptor FXReader(&IOListen);

    openfluid::base::RuntimeEnvironment::getInstance()->setInputDir(std::string(StrPath));
    FXReader.loadFromDirectory(openfluid::base::RuntimeEnvironment::getInstance()->getInputDir());

    this->m_DomainDescriptor = FXReader.getDomainDescriptor();
    this->m_CoupledModelDescriptor = FXReader.getModelDescriptor();
    this->m_DatastoreDescriptor = FXReader.getDatastoreDescriptor();
    this->m_MonitoringDescriptor = FXReader.getMonitoringDescriptor();
    this->m_RunDescriptor = FXReader.getRunDescriptor();

    return ResClass;
  }
  catch (openfluid::base::OFException& E)
  {
    StrError = std::string(E.what());
  }
  catch (std::bad_alloc& E)
  {
    StrError = std::string("MEMORY ALLOCATION ERROR, ") + std::string(E.what()) + std::string(". Possibly not enough memory available");
  }
  catch (std::exception& E)
  {
    StrError = std::string("SYSTEM ERROR, ") + std::string(E.what());
  }
  catch (...)
  {
    StrError = std::string("UNKNOWN ERROR");
  }

  if (StrError.length() != 0)
  {
    throw PyOFException(StrError.c_str());
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
    openfluid::base::Init();

    openfluid::base::IOListener IOListen;

    if (openfluid::base::ProjectManager::getInstance()->open(StrPath))
    {
      openfluid::base::RuntimeEnvironment::getInstance()->linkToProject();
      openfluid::base::ProjectManager::getInstance()->updateOutputDir();
    }
    else
      throw openfluid::base::OFException("PyOpenFLUID", StrPath + " is not a correct project path");

    return this->openDataset(openfluid::base::RuntimeEnvironment::getInstance()->getInputDir().c_str());
  }
  catch (openfluid::base::OFException& E)
  {
    StrError = std::string(E.what());
  }
  catch (std::bad_alloc& E)
  {
    StrError = std::string("MEMORY ALLOCATION ERROR, ") + std::string(E.what()) + std::string(". Possibly not enough memory available");
  }
  catch (std::exception& E)
  {
    StrError = std::string("SYSTEM ERROR, ") + std::string(E.what());
  }
  catch (...)
  {
    StrError = std::string("UNKNOWN ERROR");
  }

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


boost::python::object PyOpenFLUID::getCurrentOutputDir ()
{
  return boost::python::str(openfluid::base::RuntimeEnvironment::getInstance()->getOutputDir());
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


boost::python::object PyOpenFLUID::getPeriodBeginDate ()
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


boost::python::object PyOpenFLUID::getPeriodEndDate ()
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
  PyOpenFLUID* project = this->openProject(Path);

  if (project != NULL)
  {
    project->runSimulation();
  }

  return project;
}


// =====================================================================
// =====================================================================


unsigned short int PyOpenFLUID::runSimulation ()
{
  std::string StrError("");
  try
  {
    openfluid::base::Init();

    this->updateOutputsConfig();

    openfluid::machine::FunctionPluginsManager::getInstance()->unloadAllWares();
    openfluid::machine::ObserverPluginsManager::getInstance()->unloadAllWares();

    openfluid::machine::Engine* Engine;
    openfluid::machine::SimulationBlob SBlob;
    openfluid::base::RuntimeEnvironment* RunEnv;
    openfluid::base::IOListener* IOListen = new openfluid::base::IOListener();
    openfluid::machine::MachineListener* MachineListen = new openfluid::machine::MachineListener();

    openfluid::machine::ModelInstance Model(SBlob,MachineListen);
    openfluid::machine::MonitoringInstance Monitoring(SBlob);
    openfluid::fluidx::FluidXDescriptor FXDesc(IOListen);

    FXDesc.getDomainDescriptor() = this->m_DomainDescriptor;
    FXDesc.getDatastoreDescriptor() = this->m_DatastoreDescriptor;
    FXDesc.getRunDescriptor() = this->m_RunDescriptor;
    FXDesc.getModelDescriptor() = this->m_CoupledModelDescriptor;
    FXDesc.getMonitoringDescriptor() = this->m_MonitoringDescriptor;

    openfluid::machine::Factory::buildSimulationBlobFromDescriptors(FXDesc,SBlob);

    openfluid::machine::Factory::buildModelInstanceFromDescriptor(this->m_CoupledModelDescriptor, Model);

    openfluid::machine::Factory::buildMonitoringInstanceFromDescriptor(this->m_MonitoringDescriptor, Monitoring);

    Engine = new openfluid::machine::Engine(SBlob, Model, Monitoring, MachineListen);

    Engine->initialize();

    Engine->initParams();
    Engine->prepareData();
    Engine->checkConsistency();
    Engine->run();

    Engine->finalize();

    delete Engine;

    return 1;
  }
  catch (openfluid::base::OFException& E)
  {
    StrError =  std::string(E.what());
  }
  catch (std::bad_alloc& E)
  {
    StrError = "MEMORY ALLOCATION ERROR, " + std::string(E.what()) + ". Possibly not enough memory available";
  }
  catch (std::exception& E)
  {
    StrError = "SYSTEM ERROR, " + std::string(E.what());
  }
  catch (...)
  {
    StrError = "UNKNOWN ERROR";
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


//PyOpenFLUID* PyOpenFLUID::loadResult (boost::python::str UnitClass,
//                                           int UnitID,
//                                           boost::python::str Suffix)
//{
//  PyOFException* error = new PyOFException("unavailable method");
//  throw *error;
//}


// =====================================================================
// =====================================================================


//PyOpenFLUID* PyOpenFLUID::loadResultFile (boost::python::str FilePath)
//{
//  PyOFException* error = new PyOFException("unavailable method");
//  throw *error;
//}


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


// =====================================================================
// =====================================================================


void PyOpenFLUID::updateOutputsConfig ()
{
//  std::vector<openfluid::base::OutputFilesDescriptor>::iterator DescIt;

//  for (DescIt = this->m_MonitoringDescriptor.getFileSets().begin();
//       DescIt != this->m_MonitoringDescriptor.getFileSets().end();
//       ++DescIt)
//  {
//    (*DescIt).setHeaderType(openfluid::base::OutputFilesDescriptor::ColnamesAsData);
//    (*DescIt).setDateFormat("%Y%m%d-%H%M%S");
//  }
}
