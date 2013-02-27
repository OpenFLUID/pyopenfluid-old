#include <Python.h>
#include <boost/python.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/exception/all.hpp>

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <exception>
#include <cstdlib>

#include <openfluid/config.hpp>

#include <openfluid/base/Init.hpp>
#include <openfluid/base/IOListener.hpp>
#include <openfluid/base/RuntimeEnv.hpp>
#include <openfluid/base/OFException.hpp>
#include <openfluid/base/ProjectManager.hpp>

#include <openfluid/core/TypeDefs.hpp>
#include <openfluid/core/DateTime.hpp>

#include <openfluid/ware/PluggableWare.hpp>

#include <openfluid/machine/Engine.hpp>
#include <openfluid/machine/Factory.hpp>
#include <openfluid/machine/ModelInstance.hpp>
#include <openfluid/machine/SimulationBlob.hpp>
#include <openfluid/machine/MachineListener.hpp>
#include <openfluid/machine/MonitoringInstance.hpp>
#include <openfluid/machine/FunctionPluginsManager.hpp>
#include <openfluid/machine/ObserverPluginsManager.hpp>

#include <openfluid/fluidx/RunDescriptor.hpp>
#include <openfluid/fluidx/UnitDescriptor.hpp>
#include <openfluid/fluidx/FluidXDescriptor.hpp>
#include <openfluid/fluidx/DomainDescriptor.hpp>
#include <openfluid/fluidx/FunctionDescriptor.hpp>
#include <openfluid/fluidx/ObserverDescriptor.hpp>
#include <openfluid/fluidx/GeneratorDescriptor.hpp>
#include <openfluid/fluidx/DatastoreDescriptor.hpp>
#include <openfluid/fluidx/MonitoringDescriptor.hpp>
#include <openfluid/fluidx/CoupledModelDescriptor.hpp>

#include "PyOpenFLUID.hpp"
#include "PyOpenFLUIDError.hpp"
#include "Utilities.hpp"


// =====================================================================
// =====================================================================



PyOpenFLUID::PyOpenFLUID () : m_FXDesc(NULL)
{
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


void PyOpenFLUID::addExtraFunctionsPaths (boost::python::object Paths)
{
  boost::python::extract<std::string> getStringPaths(Paths);
  if (!getStringPaths.check())
    throw PyOFException("needed string for extra functions paths");

  openfluid::base::RuntimeEnvironment::getInstance()->
    addExtraFunctionsPluginsPaths(getStringPaths());
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


void PyOpenFLUID::addExtraObserversPaths (boost::python::object Paths)
{
  boost::python::extract<std::string> getStringPaths(Paths);
  if (!getStringPaths.check())
    throw PyOFException("needed string for extra observers paths");

  openfluid::base::RuntimeEnvironment::getInstance()->
    addExtraObserversPluginsPaths(getStringPaths());
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
  // output stream
  std::stringstream SStream(std::stringstream::in | std::stringstream::out);

  // Spatial domain
  openfluid::core::UnitClass_t ClassName;

  std::map<openfluid::core::UnitClass_t, unsigned int> UnitsInfos;

  std::list<openfluid::fluidx::UnitDescriptor>::iterator bItUnits = this->m_FXDesc.getDomainDescriptor().getUnits().begin();
  std::list<openfluid::fluidx::UnitDescriptor>::iterator eItUnits = this->m_FXDesc.getDomainDescriptor().getUnits().end();

  for (std::list<openfluid::fluidx::UnitDescriptor>::iterator ItUnits = bItUnits; ItUnits != eItUnits; ++ItUnits)
  {
    ClassName = (*ItUnits).getUnitClass();

    if (UnitsInfos.find(ClassName) == UnitsInfos.end())
      UnitsInfos[ClassName] = 0;
    UnitsInfos[ClassName]++;
  }

  SStream << "Spatial domain is made of " << this->m_FXDesc.getDomainDescriptor().getUnits().size() << " spatial units" << std::endl;

  for (std::map<openfluid::core::UnitClass_t,unsigned int>::iterator ItUnitsInfos = UnitsInfos.begin(); ItUnitsInfos != UnitsInfos.end(); ++ItUnitsInfos)
    SStream << " - " << (*ItUnitsInfos).second << " units of class " << (*ItUnitsInfos).first.c_str() << std::endl;


  // Model
  openfluid::fluidx::GeneratorDescriptor* pGenDesc;

  SStream << "Model is made of " << this->m_FXDesc.getModelDescriptor().getItems().size() << " simulation items" << std::endl;

  for (openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator ItModelInfos = this->m_FXDesc.getModelDescriptor().getItems().begin(); ItModelInfos != this->m_FXDesc.getModelDescriptor().getItems().end(); ++ItModelInfos)
  {
    SStream << " - ";

    if ((*ItModelInfos)->isType(openfluid::fluidx::ModelItemDescriptor::PluggedFunction))
    {
      SStream << ((openfluid::fluidx::FunctionDescriptor*)(*ItModelInfos))->getFileID().c_str() << " simulation function" << std::endl;
    }

    if ((*ItModelInfos)->isType(openfluid::fluidx::ModelItemDescriptor::Generator))
    {
      pGenDesc = ((openfluid::fluidx::GeneratorDescriptor*)(*ItModelInfos));

      if (pGenDesc->getGeneratorMethod() == openfluid::fluidx::GeneratorDescriptor::Fixed)
        SStream << "fixed";

      else if (pGenDesc->getGeneratorMethod() == openfluid::fluidx::GeneratorDescriptor::Random)
        SStream << "random";

      else if (pGenDesc->getGeneratorMethod() == openfluid::fluidx::GeneratorDescriptor::Interp)
        SStream << "interp";

      else if (pGenDesc->getGeneratorMethod() == openfluid::fluidx::GeneratorDescriptor::Inject)
        SStream << "inject";

      SStream << " generator for variable " << pGenDesc->getVariableName().c_str() << " on units " << pGenDesc->getUnitClass().c_str() << std::endl;
    }
  }

  // Time period

  SStream << "Simulation period from " << this->m_FXDesc.getRunDescriptor().getBeginDate().getAsISOString().c_str() << " to " << this->m_FXDesc.getRunDescriptor().getEndDate().getAsISOString().c_str() << std::endl;

  // Time step

  SStream << "Simulation time step : " << this->m_FXDesc.getRunDescriptor().getDeltaT() << std::endl;

  // Printing
  topython::printStdOut(SStream);
}


// =====================================================================
/* ------------------------  MODEL FUNCTIONS  ----------------------- */


boost::python::object PyOpenFLUID::getFunctionParam (boost::python::object FuncID,
                                                   boost::python::object ParamName)
{
  boost::python::extract<std::string> getStringFuncID(FuncID);
  if (!getStringFuncID.check())
    throw PyOFException("needed string for function id");
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyOFException("needed string for parameter name");

  std::string FuncIDStr = getStringFuncID();
  std::string ParamNameStr = getStringParamName();

  openfluid::ware::WareParams_t Params;
  openfluid::ware::WareParams_t::iterator ItParam;

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator ItModelInfos = this->m_FXDesc.getModelDescriptor().getItems().begin();

  while (ItModelInfos != this->m_FXDesc.getModelDescriptor().getItems().end())
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


void PyOpenFLUID::setFunctionParam (boost::python::object FuncID,
                                    boost::python::object ParamName,
                                    boost::python::object ParamValue)
{
  boost::python::extract<std::string> getStringFuncID(FuncID);
  if (!getStringFuncID.check())
    throw PyOFException("needed string for function id");
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyOFException("needed string for parameter name");
  boost::python::extract<std::string> getStringParamValue(ParamValue);
  if (!getStringParamValue.check())
    throw PyOFException("needed string for parameter value");

  std::string FuncIDStr = getStringFuncID();
  std::string ParamNameStr = getStringParamName();
  std::string ParamValueStr = getStringParamValue();

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t ModelInfos = this->m_FXDesc.getModelDescriptor().getItems();
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
                                                  boost::python::object UnitClass,
                                                  boost::python::object VarName,
                                                  boost::python::object ParamName)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyOFException("needed string for unit class");
  boost::python::extract<std::string> getStringVarName(VarName);
  if (!getStringVarName.check())
    throw PyOFException("needed string for variable name");
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyOFException("needed string for parameter name");

  std::string UnitClassStr = getStringUnitClass();
  std::string VarNameStr = getStringVarName();
  std::string ParamNameStr = getStringParamName();

  openfluid::ware::WareParams_t Params;
  openfluid::ware::WareParams_t::iterator ItParam;

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator ItModelInfos = this->m_FXDesc.getModelDescriptor().getItems().begin();

  openfluid::fluidx::GeneratorDescriptor* GenDescp;

  while (ItModelInfos != this->m_FXDesc.getModelDescriptor().getItems().end())
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


void PyOpenFLUID::setGeneratorParam (boost::python::object UnitClass,
                                     boost::python::object VarName,
                                     boost::python::object ParamName,
                                     boost::python::object ParamValue)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyOFException("needed string for unit class");
  boost::python::extract<std::string> getStringVarName(VarName);
  if (!getStringVarName.check())
    throw PyOFException("needed string for variable name");
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyOFException("needed string for parameter name");
  boost::python::extract<std::string> getStringParamValue(ParamValue);
  if (!getStringParamValue.check())
    throw PyOFException("needed string for parameter value");

  std::string UnitClassStr = getStringUnitClass();
  std::string VarNameStr = getStringVarName();
  std::string ParamNameStr = getStringParamName();
  std::string ParamValueStr = getStringParamValue();

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator ItModelInfos = this->m_FXDesc.getModelDescriptor().getItems().begin();

  openfluid::fluidx::GeneratorDescriptor* GenDescp;

  while (ItModelInfos != this->m_FXDesc.getModelDescriptor().getItems().end())
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
                                                  boost::python::object ParamName)
{
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyOFException("needed string for parameter name");

  std::string ParamNameStr = getStringParamName();

  openfluid::ware::WareParams_t Params = this->m_FXDesc.getModelDescriptor().getGlobalParameters();
  openfluid::ware::WareParams_t::iterator ItParam = Params.begin();

  boost::python::str ResValue;

  while (ItParam != Params.end() && (*ItParam).first != ParamNameStr)
    ++ItParam;

  if (ItParam != Params.end())
    return boost::python::str((*ItParam).second.data());

  return boost::python::object(); /* makes Python NONE */
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::setModelGlobalParam (boost::python::object ParamName,
                                       boost::python::object ParamValue)
{
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyOFException("needed string for parameter name");
  boost::python::extract<std::string> getStringParamValue(ParamValue);
  if (!getStringParamValue.check())
    throw PyOFException("needed string for parameter value");

  openfluid::ware::WareParamKey_t ParamNameStr =
      (openfluid::ware::WareParamKey_t) getStringParamName();
  openfluid::ware::WareParamValue_t ParamValueStr =
      (openfluid::ware::WareParamValue_t) getStringParamValue();

  this->m_FXDesc.getModelDescriptor().setGlobalParameter(ParamNameStr,ParamValueStr);
}


// =====================================================================
/* ---------------------  MONITORING FUNCTIONS  --------------------- */


boost::python::object PyOpenFLUID::getObserverParam (boost::python::object ObsID,
                                                   boost::python::object ParamName)
{
  boost::python::extract<std::string> getStringObsID(ObsID);
  if (!getStringObsID.check())
    throw PyOFException("needed string for observer id");
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyOFException("needed string for parameter name");

  std::string ObsIDStr = getStringObsID();
  std::string ParamNameStr = getStringParamName();

  openfluid::ware::WareParams_t Params;
  openfluid::ware::WareParams_t::iterator ItParam;

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator ItModelInfos = this->m_FXDesc.getModelDescriptor().getItems().begin();

  openfluid::fluidx::ObserverDescriptor* ObsDescp;

  while (ItModelInfos != this->m_FXDesc.getModelDescriptor().getItems().end())
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


void PyOpenFLUID::setObserverParam (boost::python::object ObsID,
                                    boost::python::object ParamName,
                                    boost::python::object ParamValue)
{
  boost::python::extract<std::string> getStringObsID(ObsID);
  if (!getStringObsID.check())
    throw PyOFException("needed string for observer id");
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyOFException("needed string for parameter name");
  boost::python::extract<std::string> getStringParamValue(ParamValue);
  if (!getStringParamValue.check())
    throw PyOFException("needed string for parameter value");

  std::string ObsIDStr = getStringObsID();
  std::string ParamNameStr = getStringParamName();
  std::string ParamValueStr = getStringParamValue();

  openfluid::ware::WareParams_t Params;
  openfluid::ware::WareParams_t::iterator ItParam;

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator ItModelInfos = this->m_FXDesc.getModelDescriptor().getItems().begin();

  openfluid::fluidx::ObserverDescriptor* ObsDescp;

  while (ItModelInfos != this->m_FXDesc.getModelDescriptor().getItems().end())
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
    this->m_FXDesc.getDomainDescriptor().getUnits();
  boost::python::str UnitClassStr;

  for (std::list<openfluid::fluidx::UnitDescriptor>::iterator IterUnit = ListUnit.begin();
       IterUnit != ListUnit.end(); ++IterUnit)
  {
    UnitClassStr = boost::python::str((*IterUnit).getUnitClass());
    if (!ListClasses.contains(UnitClassStr))
      ListClasses.append(UnitClassStr);
  }

  return ListClasses;
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getUnitsIDs (boost::python::object UnitClass)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyOFException("needed string for unit class");

  std::string UnitClassRef = getStringUnitClass();

  boost::python::list ListID = boost::python::list();
  std::list<openfluid::fluidx::UnitDescriptor> ListUnit =
    this->m_FXDesc.getDomainDescriptor().getUnits();

  for (std::list<openfluid::fluidx::UnitDescriptor>::iterator IterUnit = ListUnit.begin();
       IterUnit != ListUnit.end(); ++IterUnit)
    if ((*IterUnit).getUnitClass() == UnitClassRef )
      ListID.append( (*IterUnit).getUnitID() );

  return ListID;
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::createInputData (boost::python::object UnitClass,
                                   boost::python::object IDataName,
                                   boost::python::object IDataVal)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyOFException("needed string for unit class");
  boost::python::extract<std::string> getStringIDataName(IDataName);
  if (!getStringIDataName.check())
    throw PyOFException("needed string for data name");
  boost::python::extract<std::string> getStringIDataValue(IDataVal);
  if (!getStringIDataValue.check())
    throw PyOFException("needed string for data value");

  std::string UnitClassStr = getStringUnitClass();
  std::string IDataNameStr = getStringIDataName();
  std::string IDataValStr = getStringIDataValue();

  std::list<openfluid::fluidx::InputDataDescriptor>& IData = this->m_FXDesc.getDomainDescriptor().getInputData();

  for (std::list<openfluid::fluidx::InputDataDescriptor>::iterator ItIData = IData.begin();ItIData != IData.end();++ItIData)
  {
    if ((*ItIData).getUnitsClass() == UnitClassStr)
    {
      openfluid::fluidx::InputDataDescriptor::UnitIDInputData_t::iterator ItUnitData = (*ItIData).getData().begin();

      for (ItUnitData; ItUnitData!=(*ItIData).getData().end(); ++ItUnitData)
      {
        (*ItUnitData).second[IDataNameStr] = IDataValStr;
      }
    }
  }
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getInputData (boost::python::object UnitClass,
                                               boost::python::object UnitID,
                                               boost::python::object IDataName)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyOFException("needed string for unit class");
  boost::python::extract<int> getUnitID(UnitID);
  if (!getUnitID.check())
    throw PyOFException("needed integer for unit id");
  boost::python::extract<std::string> getStringIDataName(IDataName);
  if (!getStringIDataName.check())
    throw PyOFException("needed string for data name");

  std::string UnitClassStr = getStringUnitClass();
  std::string IDataNameStr = getStringIDataName();
  int UnitIDInt = getUnitID();

  std::list<openfluid::fluidx::InputDataDescriptor>& IData = this->m_FXDesc.getDomainDescriptor().getInputData();

  for (std::list<openfluid::fluidx::InputDataDescriptor>::iterator ItIData = IData.begin();ItIData != IData.end();++ItIData)
  {
    if ((*ItIData).getUnitsClass() == UnitClassStr)
    {
      openfluid::fluidx::InputDataDescriptor::UnitIDInputData_t::const_iterator ItUnitData = (*ItIData).getData().find(UnitIDInt);
      if (ItUnitData != (*ItIData).getData().end())
      {
        if ((*ItUnitData).second.find(IDataNameStr) != (*ItUnitData).second.end())
        {
          return boost::python::str((*ItUnitData).second.at(IDataNameStr));
        }
      }
    }
  }

  return boost::python::object(); /* makes Python NONE */
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::setInputData (boost::python::object UnitClass,
                                boost::python::object UnitID,
                                boost::python::object IDataName,
                                boost::python::object IDataValue)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyOFException("needed string for unit class");
  boost::python::extract<int> getUnitID(UnitID);
  if (!getUnitID.check())
    throw PyOFException("needed integer for unit id");
  boost::python::extract<std::string> getStringIDataName(IDataName);
  if (!getStringIDataName.check())
    throw PyOFException("needed string for data name");
  boost::python::extract<std::string> getStringIDataValue(IDataValue);
  if (!getStringIDataValue.check())
    throw PyOFException("needed string for data value");

  std::string UnitClassStr = getStringUnitClass();
  std::string IDataNameStr = getStringIDataName();
  std::string IDataValStr = getStringIDataValue();
  int UnitIDInt = getUnitID();

  std::list<openfluid::fluidx::InputDataDescriptor>& IData = this->m_FXDesc.getDomainDescriptor().getInputData();

  for (std::list<openfluid::fluidx::InputDataDescriptor>::iterator ItIData = IData.begin();ItIData != IData.end();++ItIData)
  {
    if ((*ItIData).getUnitsClass() == UnitClassStr)
    {
      openfluid::fluidx::InputDataDescriptor::UnitIDInputData_t::iterator ItUnitData = (*ItIData).getData().find(UnitIDInt);
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


PyOpenFLUID* PyOpenFLUID::openDataset (boost::python::object Path)
{
  boost::python::extract<std::string> getStringPath(Path);
  if (!getStringPath.check())
    throw PyOFException("needed string");

  std::string StrError = std::string("");
  std::string StrPath = getStringPath();
  PyOpenFLUID* ResClass = new PyOpenFLUID();

  try
  {
    openfluid::base::Init();

    openfluid::base::IOListener IOListen;
    openfluid::fluidx::FluidXDescriptor FXReader(&IOListen);

    openfluid::base::RuntimeEnvironment::getInstance()->setInputDir(std::string(StrPath));
    FXReader.loadFromDirectory(openfluid::base::RuntimeEnvironment::getInstance()->getInputDir());

    this->m_FXDesc = FXReader;

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


PyOpenFLUID* PyOpenFLUID::openProject (boost::python::object Path)
{
  boost::python::extract<std::string> getStringPath(Path);
  if (!getStringPath.check())
    throw PyOFException("needed string");

  std::string StrError = std::string("");
  std::string StrPath = getStringPath();

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

    return this->openDataset(Path);
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


void PyOpenFLUID::setCurrentOutputDir (boost::python::object Path)
{
  boost::python::extract<std::string> getStringPath(Path);
  if (!getStringPath.check())
    throw PyOFException("needed string");

  openfluid::base::RuntimeEnvironment::getInstance()->setOutputDir(getStringPath());
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getCurrentOutputDir ()
{
  return boost::python::str(openfluid::base::RuntimeEnvironment::getInstance()->getOutputDir());
}


// =====================================================================
/* ---------------------  SIMULATION FUNCTIONS  --------------------- */


boost::python::object PyOpenFLUID::getDefaultDeltaT ()
{
  return boost::python::object(this->m_FXDesc.getRunDescriptor().getDeltaT());
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::setDefaultDeltaT (boost::python::object DefaultDeltaT)
{
  boost::python::extract<int> getDefaultDeltaT(DefaultDeltaT);
  if (!getDefaultDeltaT.check())
    throw PyOFException("needed integer");

  const int DefaultDeltaTInt = getDefaultDeltaT();
  if (DefaultDeltaTInt <= 0)
    throw PyOFException("DefaultDeltaT cann't be negative or null.");
  this->m_FXDesc.getRunDescriptor().setDeltaT(DefaultDeltaTInt);
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getPeriodBeginDate ()
{
  openfluid::core::DateTime BrutDate = this->m_FXDesc.getRunDescriptor().getBeginDate();
  std::stringstream StreamRes(std::stringstream::in | std::stringstream::out);
  StreamRes << tools::zeroFill(boost::lexical_cast<std::string>(BrutDate.getYear()), 1) << "-";
  StreamRes << tools::zeroFill(boost::lexical_cast<std::string>(BrutDate.getMonth()), 2) << "-";
  StreamRes << tools::zeroFill(boost::lexical_cast<std::string>(BrutDate.getDay()), 2) << " ";
  StreamRes << tools::zeroFill(boost::lexical_cast<std::string>(BrutDate.getHour()), 2) << ":";
  StreamRes << tools::zeroFill(boost::lexical_cast<std::string>(BrutDate.getMinute()), 2) << ":";
  StreamRes << tools::zeroFill(boost::lexical_cast<std::string>(BrutDate.getSecond()), 2);
  return boost::python::str(StreamRes.str().c_str());
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getPeriodEndDate ()
{
  openfluid::core::DateTime BrutDate = this->m_FXDesc.getRunDescriptor().getEndDate();
  std::stringstream StreamRes(std::stringstream::in | std::stringstream::out);
  StreamRes << tools::zeroFill(boost::lexical_cast<std::string>(BrutDate.getYear()), 1) << "-";
  StreamRes << tools::zeroFill(boost::lexical_cast<std::string>(BrutDate.getMonth()), 2) << "-";
  StreamRes << tools::zeroFill(boost::lexical_cast<std::string>(BrutDate.getDay()), 2) << " ";
  StreamRes << tools::zeroFill(boost::lexical_cast<std::string>(BrutDate.getHour()), 2) << ":";
  StreamRes << tools::zeroFill(boost::lexical_cast<std::string>(BrutDate.getMinute()), 2) << ":";
  StreamRes << tools::zeroFill(boost::lexical_cast<std::string>(BrutDate.getSecond()), 2);
  return boost::python::str(StreamRes.str().c_str());
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::setPeriodBeginDate (boost::python::object BDate)
{
  boost::python::extract<std::string> getStringBDate(BDate);
  if (!getStringBDate.check())
    throw PyOFException("needed string");

  std::string Pattern = std::string("^(\\d{1,4})-(\\d{2})-(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2})$");
  std::string Target = getStringBDate();

  boost::regex RegexPattern = boost::regex(Pattern, boost::regex::extended);
  boost::smatch ResMatch;

  bool isMatchFound = boost::regex_match(Target, ResMatch, RegexPattern);

  if (isMatchFound && ResMatch.size() == 7)
  {
    int TabRes[6];
    int i;
    std::string TmpStr;
    for (i=0; i<6; i++)
    {
      TmpStr = ResMatch[i+1];
      TabRes[i] = std::atoi(TmpStr.c_str());
    }

  openfluid::core::DateTime BDate = openfluid::core::DateTime(TabRes[0], TabRes[1], TabRes[2], TabRes[3], TabRes[4], TabRes[5]);
  this->m_FXDesc.getRunDescriptor().setBeginDate(BDate);
  }
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::setPeriodEndDate (boost::python::object EDate)
{
  boost::python::extract<std::string> getStringEDate(EDate);
  if (!getStringEDate.check())
    throw PyOFException("needed string");

  std::string Pattern = std::string("^(\\d{1,4})-(\\d{2})-(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2})$");
   std::string Target = getStringEDate();

  boost::regex RegexPattern = boost::regex(Pattern, boost::regex::extended);
  boost::smatch ResMatch;

  bool isMatchFound = boost::regex_match(Target, ResMatch, RegexPattern);

  if (isMatchFound && ResMatch.size() == 7)
  {
    int TabRes[6];
    int i;
    std::string TmpStr;
    for (i=0; i<6; i++)
    {
      TmpStr = ResMatch[i+1];
      TabRes[i] = std::atoi(TmpStr.c_str());
    }

  openfluid::core::DateTime BDate = openfluid::core::DateTime(TabRes[0], TabRes[1], TabRes[2], TabRes[3], TabRes[4], TabRes[5]);
  this->m_FXDesc.getRunDescriptor().setEndDate(BDate);
  }
}


// =====================================================================
// =====================================================================


PyOpenFLUID* PyOpenFLUID::runProject (boost::python::object Path)
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


boost::python::object PyOpenFLUID::runSimulation ()
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
    openfluid::machine::MachineListener* MachineListen = new openfluid::machine::MachineListener();

    openfluid::machine::ModelInstance Model(SBlob,MachineListen);
    openfluid::machine::MonitoringInstance Monitoring(SBlob);

    openfluid::machine::Factory::buildSimulationBlobFromDescriptors(this->m_FXDesc,SBlob);

    openfluid::machine::Factory::buildModelInstanceFromDescriptor(this->m_FXDesc.getModelDescriptor(), Model);

    openfluid::machine::Factory::buildMonitoringInstanceFromDescriptor(this->m_FXDesc.getMonitoringDescriptor(), Monitoring);

    Engine = new openfluid::machine::Engine(SBlob, Model, Monitoring, MachineListen);

    Engine->initialize();

    Engine->initParams();
    Engine->prepareData();
    Engine->checkConsistency();
    Engine->run();

    Engine->finalize();

    delete Engine;

    return boost::python::object(true);
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
    throw PyOFException(StrError.c_str());
  }

  return boost::python::object(false);
}


// =====================================================================
// =====================================================================


//PyOpenFLUID* PyOpenFLUID::loadResult (boost::python::object UnitClass,
//                                           boost::python::object UnitID,
//                                           boost::python::object Suffix)
//{
//  PyOFException* error = new PyOFException("unavailable method");
//  throw *error;
//}


// =====================================================================
// =====================================================================


//PyOpenFLUID* PyOpenFLUID::loadResultFile (boost::python::object FilePath)
//{
//  PyOFException* error = new PyOFException("unavailable method");
//  throw *error;
//}


// =====================================================================
// =====================================================================


void PyOpenFLUID::updateOutputsConfig ()
{
//  std::vector<openfluid::base::OutputFilesDescriptor>::iterator DescIt;

//  for (DescIt = this->m_FXDesc.getMonitoringDescriptor().getFileSets().begin();
//       DescIt != this->m_FXDesc.getMonitoringDescriptor().getFileSets().end();
//       ++DescIt)
//  {
//    (*DescIt).setHeaderType(openfluid::base::OutputFilesDescriptor::ColnamesAsData);
//    (*DescIt).setDateFormat("%Y%m%d-%H%M%S");
//  }
}


// =====================================================================
/* ------------------------ OTHER FUNCTIONS  ------------------------ */


void PyOpenFLUID::copy (PyOpenFLUID InputClass)
{
  this->m_FXDesc = InputClass.getFluidXDescriptor();
}


// =====================================================================
// =====================================================================


openfluid::fluidx::FluidXDescriptor& PyOpenFLUID::getFluidXDescriptor ()
{
  return this->m_FXDesc;
}
