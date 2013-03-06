#include <Python.h>
#include <boost/python.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/exception/all.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/optional.hpp>

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
#include "PythonUtilities.hpp"


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
    throw PyOFException("needed string for extra functions paths",
        PyExc_TypeError);

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
  std::vector<std::string> VectPath = openfluid::base::RuntimeEnvironment
      ::getInstance()->getExtraFunctionsPluginsPaths();
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
    throw PyOFException("needed string for extra observers paths",
        PyExc_TypeError);

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
  std::vector<std::string> VectPath = openfluid::base::RuntimeEnvironment
      ::getInstance()->getExtraObserversPluginsPaths();
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

  std::list<openfluid::fluidx::UnitDescriptor>::iterator bItUnits =
      this->m_FXDesc.getDomainDescriptor().getUnits().begin();
  std::list<openfluid::fluidx::UnitDescriptor>::iterator eItUnits =
      this->m_FXDesc.getDomainDescriptor().getUnits().end();

  std::list<openfluid::fluidx::UnitDescriptor>::iterator ItUnits;
  for (ItUnits = bItUnits; ItUnits != eItUnits; ++ItUnits)
  {
    ClassName = (*ItUnits).getUnitClass();

    if (UnitsInfos.find(ClassName) == UnitsInfos.end())
      UnitsInfos[ClassName] = 0;
    UnitsInfos[ClassName]++;
  }

  SStream << "Spatial domain is made of "
      << this->m_FXDesc.getDomainDescriptor().getUnits().size()
      << " spatial units" << std::endl;

  std::map<openfluid::core::UnitClass_t,unsigned int>::iterator ItUnitsInfos;
  for (ItUnitsInfos = UnitsInfos.begin(); ItUnitsInfos != UnitsInfos.end();
      ++ItUnitsInfos)
    SStream << " - " << (*ItUnitsInfos).second << " units of class "
        << (*ItUnitsInfos).first.c_str() << std::endl;


  // Model
  openfluid::fluidx::GeneratorDescriptor* pGenDesc;

  SStream << "Model is made of "
      << this->m_FXDesc.getModelDescriptor().getItems().size()
      << " simulation items" << std::endl;

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator
      ItModelInfos;
  for (ItModelInfos = this->m_FXDesc.getModelDescriptor().getItems().begin();
       ItModelInfos != this->m_FXDesc.getModelDescriptor().getItems().end();
       ++ItModelInfos)
  {
    SStream << " - ";

    if ((*ItModelInfos)->isType(
        openfluid::fluidx::ModelItemDescriptor::PluggedFunction))
    {
      SStream << ((openfluid::fluidx::FunctionDescriptor*)(*ItModelInfos))->
          getFileID().c_str() << " simulation function" << std::endl;
    }

    if ((*ItModelInfos)->isType(openfluid::fluidx::ModelItemDescriptor::
        Generator))
    {
      pGenDesc = ((openfluid::fluidx::GeneratorDescriptor*)(*ItModelInfos));

      if (pGenDesc->getGeneratorMethod() == openfluid::fluidx::
          GeneratorDescriptor::Fixed)
        SStream << "fixed";

      else if (pGenDesc->getGeneratorMethod() == openfluid::fluidx::
          GeneratorDescriptor::Random)
        SStream << "random";

      else if (pGenDesc->getGeneratorMethod() == openfluid::fluidx::
          GeneratorDescriptor::Interp)
        SStream << "interp";

      else if (pGenDesc->getGeneratorMethod() == openfluid::fluidx::
          GeneratorDescriptor::Inject)
        SStream << "inject";

      SStream << " generator for variable "
          << pGenDesc->getVariableName().c_str() << " on units "
          << pGenDesc->getUnitClass().c_str() << std::endl;
    }
  }

  // Time period

  SStream << "Simulation period from " <<
      this->m_FXDesc.getRunDescriptor().getBeginDate().getAsISOString().c_str()
      << " to "
      << this->m_FXDesc.getRunDescriptor().getEndDate().getAsISOString().c_str()
      << std::endl;

  // Time step

  SStream << "Simulation time step : "
      << this->m_FXDesc.getRunDescriptor().getDeltaT() << std::endl;

  // Printing
  topython::printStdOut(SStream);
}


// =====================================================================
/* ------------------------  MODEL FUNCTIONS  ----------------------- */


boost::python::object PyOpenFLUID::getFunctionParam (
    boost::python::object FuncID, boost::python::object ParamName)
{
  boost::python::extract<std::string> getStringFuncID(FuncID);
  if (!getStringFuncID.check())
    throw PyOFException("needed string for function id", PyExc_TypeError);
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyOFException("needed string for parameter name", PyExc_TypeError);

  std::string FuncIDStr = getStringFuncID();
  std::string ParamNameStr = getStringParamName();

  openfluid::ware::WareParams_t Params;
  openfluid::ware::WareParams_t::iterator ItParam;

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t
      ModelInfos = this->m_FXDesc.getModelDescriptor().getItems();

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator
      ItModelInfos = ModelInfos.begin();

  openfluid::fluidx::FunctionDescriptor* FuncDescp;

  while (ItModelInfos != ModelInfos.end())
  {
    if ((*ItModelInfos)->isType(
          openfluid::fluidx::FunctionDescriptor::PluggedFunction))
    {
      FuncDescp = (openfluid::fluidx::FunctionDescriptor*) *ItModelInfos;
      if (FuncDescp->getFileID() == FuncIDStr)
      {
        boost::optional<std::string> Res =
            FuncDescp->getParameters().get_optional<std::string>(ParamNameStr);

        if (Res)
          return boost::python::str(*Res);

        break;
      }
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
    throw PyOFException("needed string for function id", PyExc_TypeError);
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyOFException("needed string for parameter name", PyExc_TypeError);
  boost::python::extract<std::string> getStringParamValue(ParamValue);
  if (!getStringParamValue.check())
    throw PyOFException("needed string for parameter value", PyExc_TypeError);

  std::string FuncIDStr = getStringFuncID();
  std::string ParamNameStr = getStringParamName();
  std::string ParamValueStr = getStringParamValue();

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t
      ModelInfos = this->m_FXDesc.getModelDescriptor().getItems();
  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator
      ItModelInfos = ModelInfos.begin();

  while (ItModelInfos != ModelInfos.end())
  {
    if ((*ItModelInfos)->isType(
          openfluid::fluidx::ModelItemDescriptor::PluggedFunction) &&
        ((openfluid::fluidx::FunctionDescriptor*)(*ItModelInfos))->getFileID()
          == FuncIDStr)
    {
      (*ItModelInfos)->setParameter(ParamNameStr,ParamValueStr);
      break;
    }
    ++ItModelInfos;
  }
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::removeFunctionParam (boost::python::object FuncID,
                                       boost::python::object ParamName)
{
  boost::python::extract<std::string> getStringFuncID(FuncID);
  if (!getStringFuncID.check())
    throw PyOFException("needed string for function id", PyExc_TypeError);
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyOFException("needed string for parameter name", PyExc_TypeError);

  std::string FuncIDStr = getStringFuncID();
  std::string ParamNameStr = getStringParamName();

  openfluid::fluidx::FunctionDescriptor* Function;

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t
      ModelInfos = this->m_FXDesc.getModelDescriptor().getItems();

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator
      ItModelInfos = ModelInfos.begin();

  while (ItModelInfos != ModelInfos.end())
  {
    if ((*ItModelInfos)->isType(
        openfluid::fluidx::ModelItemDescriptor::PluggedFunction))
    {
      Function = (openfluid::fluidx::FunctionDescriptor*)(*ItModelInfos);
      if (Function->getFileID() == FuncIDStr)
      {
        Function->eraseParameter(ParamNameStr);
        break;
      }
    }
    ++ItModelInfos;
  }
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getGeneratorParam (
    boost::python::object UnitClass, boost::python::object VarName,
    boost::python::object ParamName)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyOFException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<std::string> getStringVarName(VarName);
  if (!getStringVarName.check())
    throw PyOFException("needed string for variable name", PyExc_TypeError);
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyOFException("needed string for parameter name", PyExc_TypeError);

  std::string UnitClassStr = getStringUnitClass();
  std::string VarNameStr = getStringVarName();
  std::string ParamNameStr = getStringParamName();

  openfluid::ware::WareParams_t Params;
  openfluid::ware::WareParams_t::iterator ItParam;

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t
      ModelInfos = this->m_FXDesc.getModelDescriptor().getItems();

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator
      ItModelInfos = ModelInfos.begin();

  openfluid::fluidx::GeneratorDescriptor* GenDescp;

  while (ItModelInfos != ModelInfos.end())
  {
    if ((*ItModelInfos)->isType(
          openfluid::fluidx::GeneratorDescriptor::Generator))
    {
      GenDescp = (openfluid::fluidx::GeneratorDescriptor*) *ItModelInfos;
      if (GenDescp->getUnitClass() == UnitClassStr &&
          GenDescp->getVariableName() == VarNameStr)
      {
        boost::optional<std::string> Res =
            GenDescp->getParameters().get_optional<std::string>(ParamNameStr);

        if (Res)
          return boost::python::str(*Res);

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
    throw PyOFException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<std::string> getStringVarName(VarName);
  if (!getStringVarName.check())
    throw PyOFException("needed string for variable name", PyExc_TypeError);
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyOFException("needed string for parameter name", PyExc_TypeError);
  boost::python::extract<std::string> getStringParamValue(ParamValue);
  if (!getStringParamValue.check())
    throw PyOFException("needed string for parameter value", PyExc_TypeError);

  std::string UnitClassStr = getStringUnitClass();
  std::string VarNameStr = getStringVarName();
  std::string ParamNameStr = getStringParamName();
  std::string ParamValueStr = getStringParamValue();

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator
      ItModelInfos = this->m_FXDesc.getModelDescriptor().getItems().begin();

  openfluid::fluidx::GeneratorDescriptor* GenDescp;

  while (ItModelInfos != this->m_FXDesc.getModelDescriptor().getItems().end())
  {
    if ((*ItModelInfos)->isType(
        openfluid::fluidx::ModelItemDescriptor::Generator))
    {
      GenDescp = (openfluid::fluidx::GeneratorDescriptor*)(*ItModelInfos);
      if (GenDescp->getUnitClass() == UnitClassStr &&
          GenDescp->getVariableName() == VarNameStr)
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
    throw PyOFException("needed string for parameter name", PyExc_TypeError);

  std::string ParamNameStr = getStringParamName();

  openfluid::ware::WareParams_t Params = this->m_FXDesc.getModelDescriptor()
      .getGlobalParameters();
  openfluid::ware::WareParams_t::iterator ItParam = Params.begin();

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
    throw PyOFException("needed string for parameter name", PyExc_TypeError);
  boost::python::extract<std::string> getStringParamValue(ParamValue);
  if (!getStringParamValue.check())
    throw PyOFException("needed string for parameter value", PyExc_TypeError);

  openfluid::ware::WareParamKey_t ParamNameStr =
      (openfluid::ware::WareParamKey_t) getStringParamName();
  openfluid::ware::WareParamValue_t ParamValueStr =
      (openfluid::ware::WareParamValue_t) getStringParamValue();

  this->m_FXDesc.getModelDescriptor()
      .setGlobalParameter(ParamNameStr,ParamValueStr);
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::removeModelGlobalParam (boost::python::object ParamName)
{
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyOFException("needed string for parameter name", PyExc_TypeError);

  std::string ParamNameStr = getStringParamName();

  this->m_FXDesc.getModelDescriptor().eraseGlobalParameter(ParamNameStr);
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::addFunction (boost::python::object FuncID)
{
  boost::python::extract<std::string> getStringFuncID(FuncID);
  if (!getStringFuncID.check())
    throw PyOFException("needed string for function id", PyExc_TypeError);

  std::string FuncIDStr = getStringFuncID();

  openfluid::fluidx::FunctionDescriptor* NewFunction =
      new openfluid::fluidx::FunctionDescriptor(FuncIDStr);

  this->m_FXDesc.getModelDescriptor().appendItem(NewFunction);
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::removeFunction (boost::python::object FuncID)
{
  boost::python::extract<std::string> getStringFuncID(FuncID);
  if (!getStringFuncID.check())
    throw PyOFException("needed string for observer id", PyExc_TypeError);

  std::string FuncIDStr = getStringFuncID();

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t&
      ModelInfos = this->m_FXDesc.getModelDescriptor().getItems();

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator
      ItModelInfos = ModelInfos.begin();

  openfluid::fluidx::FunctionDescriptor* FuncDescp;

  while (ItModelInfos != ModelInfos.end())
  {
    if ((*ItModelInfos)->isType(
        openfluid::fluidx::ModelItemDescriptor::PluggedFunction))
    {
      FuncDescp = (openfluid::fluidx::FunctionDescriptor*)(*ItModelInfos);
      if (FuncDescp->getFileID() == FuncIDStr)
      {
        ModelInfos.erase(ItModelInfos);
        break;
      }
    }
    ++ItModelInfos;
  }
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::clearModel ()
{
  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t&
      ModelInfos = this->m_FXDesc.getModelDescriptor().getItems();

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator
      ItModelInfos = ModelInfos.begin();

  while (ItModelInfos != ModelInfos.end())
  {
    if ((*ItModelInfos)->isType(
        openfluid::fluidx::ModelItemDescriptor::PluggedFunction))
      ItModelInfos = ModelInfos.erase(ItModelInfos);
    else
      ++ItModelInfos;
  }
}


// =====================================================================
/* ---------------------  MONITORING FUNCTIONS  --------------------- */


boost::python::object PyOpenFLUID::getObserverParam (
    boost::python::object ObsID, boost::python::object ParamName)
{
  boost::python::extract<std::string> getStringObsID(ObsID);
  if (!getStringObsID.check())
    throw PyOFException("needed string for observer id", PyExc_TypeError);
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyOFException("needed string for parameter name", PyExc_TypeError);

  std::string ObsIDStr = getStringObsID();
  std::string ParamNameStr = getStringParamName();

  openfluid::fluidx::MonitoringDescriptor::SetDescription_t
      ModelInfos = this->m_FXDesc.getMonitoringDescriptor().getItems();

  openfluid::fluidx::MonitoringDescriptor::SetDescription_t::iterator
      ItModelInfos = ModelInfos.begin();

  openfluid::fluidx::ObserverDescriptor* ObsDescp;

  while (ItModelInfos != ModelInfos.end())
  {
    if ((*ItModelInfos)->isType(
          openfluid::fluidx::ObserverDescriptor::PluggedObserver))
    {
      ObsDescp = *ItModelInfos;
      if (ObsDescp->getID() == ObsIDStr)
      {
        boost::optional<std::string> Res =
            ObsDescp->getParameters().get_optional<std::string>(ParamNameStr);

        if (Res)
          return boost::python::str(*Res);

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
    throw PyOFException("needed string for observer id", PyExc_TypeError);
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyOFException("needed string for parameter name", PyExc_TypeError);
  boost::python::extract<std::string> getStringParamValue(ParamValue);
  if (!getStringParamValue.check())
    throw PyOFException("needed string for parameter value", PyExc_TypeError);

  std::string ObsIDStr = getStringObsID();
  std::string ParamNameStr = getStringParamName();
  std::string ParamValueStr = getStringParamValue();

  openfluid::fluidx::MonitoringDescriptor::SetDescription_t
      ModelInfos = this->m_FXDesc.getMonitoringDescriptor().getItems();

  openfluid::fluidx::MonitoringDescriptor::SetDescription_t::iterator
      ItModelInfos = ModelInfos.begin();

  openfluid::fluidx::ObserverDescriptor* ObsDescp;

  while (ItModelInfos != ModelInfos.end())
  {
    if ((*ItModelInfos)->isType(
        openfluid::fluidx::ModelItemDescriptor::PluggedObserver))
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
// =====================================================================


void PyOpenFLUID::removeObserverParam (boost::python::object ObsID,
                                       boost::python::object ParamName)
{
  boost::python::extract<std::string> getStringObsID(ObsID);
  if (!getStringObsID.check())
    throw PyOFException("needed string for observer id", PyExc_TypeError);
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyOFException("needed string for parameter name", PyExc_TypeError);

  std::string ObsIDStr = getStringObsID();
  std::string ParamNameStr = getStringParamName();

  openfluid::fluidx::MonitoringDescriptor::SetDescription_t
      ModelInfos = this->m_FXDesc.getMonitoringDescriptor().getItems();

  openfluid::fluidx::MonitoringDescriptor::SetDescription_t::iterator
      ItModelInfos = ModelInfos.begin();

  openfluid::fluidx::ObserverDescriptor* ObsDescp;

  while (ItModelInfos != ModelInfos.end())
  {
    if ((*ItModelInfos)->isType(
        openfluid::fluidx::ModelItemDescriptor::PluggedObserver))
    {
      ObsDescp = (openfluid::fluidx::ObserverDescriptor*)(*ItModelInfos);
      if (ObsDescp->getID() == ObsIDStr)
      {
        ObsDescp->eraseParameter(ParamNameStr);
        break;
      }
    }
    ++ItModelInfos;
  }
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::addObserver (boost::python::object ObsID)
{
  boost::python::extract<std::string> getStringObsID(ObsID);
  if (!getStringObsID.check())
    throw PyOFException("needed string for observer id", PyExc_TypeError);

  std::string ObsIDStr = getStringObsID();

  openfluid::fluidx::ObserverDescriptor* NewObserver =
      new openfluid::fluidx::ObserverDescriptor(ObsIDStr);

  this->m_FXDesc.getMonitoringDescriptor().appendItem(NewObserver);
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::removeObserver (boost::python::object ObsID)
{
  boost::python::extract<std::string> getStringObsID(ObsID);
  if (!getStringObsID.check())
    throw PyOFException("needed string for observer id", PyExc_TypeError);

  std::string ObsIDStr = getStringObsID();

  openfluid::fluidx::MonitoringDescriptor::SetDescription_t&
      ModelInfos = this->m_FXDesc.getMonitoringDescriptor().getItems();

  openfluid::fluidx::MonitoringDescriptor::SetDescription_t::iterator
      ItModelInfos = ModelInfos.begin();

  openfluid::fluidx::ObserverDescriptor* ObsDescp;

  while (ItModelInfos != ModelInfos.end())
  {
    if ((*ItModelInfos)->isType(
        openfluid::fluidx::ModelItemDescriptor::PluggedObserver))
    {
      ObsDescp = (openfluid::fluidx::ObserverDescriptor*)(*ItModelInfos);
      if (ObsDescp->getID() == ObsIDStr)
      {
        ModelInfos.erase(ItModelInfos);
        break;
      }
    }
    ++ItModelInfos;
  }
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::clearMonitoring ()
{
  openfluid::fluidx::MonitoringDescriptor::SetDescription_t&
      ModelInfos = this->m_FXDesc.getMonitoringDescriptor().getItems();

  openfluid::fluidx::MonitoringDescriptor::SetDescription_t::iterator
      ItModelInfos = ModelInfos.begin();

  while (ItModelInfos != ModelInfos.end())
  {
    if ((*ItModelInfos)->isType(
        openfluid::fluidx::ModelItemDescriptor::PluggedObserver))
      ItModelInfos = ModelInfos.erase(ItModelInfos);
    else
      ++ItModelInfos;
  }
}


// =====================================================================
/* -------------------  SPATIAL DOMAIN FUNCTIONS  ------------------- */


boost::python::object PyOpenFLUID::getUnitsClasses ()
{
  boost::python::list ListClasses = boost::python::list();
  boost::python::str UnitClassStr;

  std::list<openfluid::fluidx::UnitDescriptor> ListUnit =
    this->m_FXDesc.getDomainDescriptor().getUnits();

  std::list<openfluid::fluidx::UnitDescriptor>::iterator
      IterUnit;

  for (IterUnit = ListUnit.begin(); IterUnit != ListUnit.end(); ++IterUnit)
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
    throw PyOFException("needed string for unit class", PyExc_TypeError);

  std::string UnitClassRef = getStringUnitClass();

  boost::python::list ListID = boost::python::list();

  std::list<openfluid::fluidx::UnitDescriptor>
      ListUnit = this->m_FXDesc.getDomainDescriptor().getUnits();

  std::list<openfluid::fluidx::UnitDescriptor>::iterator
      IterUnit;

  for (IterUnit = ListUnit.begin(); IterUnit != ListUnit.end(); ++IterUnit)
    if ((*IterUnit).getUnitClass() == UnitClassRef )
      ListID.append( (*IterUnit).getUnitID() );

  return ListID;
}


// =====================================================================
// =====================================================================

// TODO check and update it
void PyOpenFLUID::createInputData (boost::python::object UnitClass,
                                   boost::python::object IDataName,
                                   boost::python::object IDataVal)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyOFException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<std::string> getStringIDataName(IDataName);
  if (!getStringIDataName.check())
    throw PyOFException("needed string for data name", PyExc_TypeError);
  boost::python::extract<std::string> getStringIDataValue(IDataVal);
  if (!getStringIDataValue.check())
    throw PyOFException("needed string for data value", PyExc_TypeError);

  std::string UnitClassStr = getStringUnitClass();
  std::string IDataNameStr = getStringIDataName();
  std::string IDataValStr = getStringIDataValue();

  std::list<openfluid::fluidx::InputDataDescriptor>&
      IData = this->m_FXDesc.getDomainDescriptor().getInputData();

  std::list<openfluid::fluidx::InputDataDescriptor>::iterator
      ItIData;

  openfluid::fluidx::InputDataDescriptor::UnitIDInputData_t::iterator
      ItUnitData;

  for (ItIData = IData.begin(); ItIData != IData.end(); ++ItIData)
  {
    if ((*ItIData).getUnitsClass() == UnitClassStr)
    {
      ItUnitData = (*ItIData).getData().begin();

      for (ItUnitData; ItUnitData!=(*ItIData).getData().end(); ++ItUnitData)
      {
        (*ItUnitData).second[IDataNameStr] = IDataValStr;
      }
    }
  }
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getInputData (
    boost::python::object UnitClass, boost::python::object UnitID,
    boost::python::object IDataName)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyOFException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getUnitID(UnitID);
  if (!getUnitID.check())
    throw PyOFException("needed integer for unit id", PyExc_TypeError);
  boost::python::extract<std::string> getStringIDataName(IDataName);
  if (!getStringIDataName.check())
    throw PyOFException("needed string for data name", PyExc_TypeError);

  std::string UnitClassStr = getStringUnitClass();
  std::string IDataNameStr = getStringIDataName();
  int UnitIDInt = getUnitID();

  std::list<openfluid::fluidx::InputDataDescriptor>&
      IData = this->m_FXDesc.getDomainDescriptor().getInputData();

  std::list<openfluid::fluidx::InputDataDescriptor>::iterator
      ItIData;

  openfluid::fluidx::InputDataDescriptor::UnitIDInputData_t::iterator
      ItUnitData;

  for (ItIData = IData.begin(); ItIData != IData.end(); ++ItIData)
  {
    if ((*ItIData).getUnitsClass() == UnitClassStr)
    {
      ItUnitData = (*ItIData).getData().find(UnitIDInt);
      if (ItUnitData != (*ItIData).getData().end())
      {
        if ((*ItUnitData).second.find(IDataNameStr) !=
            (*ItUnitData).second.end())
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
    throw PyOFException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getUnitID(UnitID);
  if (!getUnitID.check())
    throw PyOFException("needed integer for unit id", PyExc_TypeError);
  boost::python::extract<std::string> getStringIDataName(IDataName);
  if (!getStringIDataName.check())
    throw PyOFException("needed string for data name", PyExc_TypeError);
  boost::python::extract<std::string> getStringIDataValue(IDataValue);
  if (!getStringIDataValue.check())
    throw PyOFException("needed string for data value", PyExc_TypeError);

  std::string UnitClassStr = getStringUnitClass();
  std::string IDataNameStr = getStringIDataName();
  std::string IDataValStr = getStringIDataValue();
  int UnitIDInt = getUnitID();

  std::list<openfluid::fluidx::InputDataDescriptor>&
      IData = this->m_FXDesc.getDomainDescriptor().getInputData();

  std::list<openfluid::fluidx::InputDataDescriptor>::iterator ItIData;

  openfluid::fluidx::InputDataDescriptor::UnitIDInputData_t::iterator
      ItUnitData;

  for (ItIData = IData.begin(); ItIData != IData.end();++ItIData)
  {
    if ((*ItIData).getUnitsClass() == UnitClassStr)
    {
      ItUnitData = (*ItIData).getData().find(UnitIDInt);
      if (ItUnitData != (*ItIData).getData().end())
      {
        if ((*ItUnitData).second.find(IDataNameStr) !=
            (*ItUnitData).second.end())
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
    throw PyOFException("needed string", PyExc_TypeError);

  std::string StrError = std::string("");
  std::string StrPath = getStringPath();

  try
  {
    openfluid::base::Init();

    openfluid::base::IOListener IOListen;
    openfluid::fluidx::FluidXDescriptor FXReader(&IOListen);

    openfluid::base::RuntimeEnvironment::getInstance()->
        setInputDir(std::string(StrPath));
    FXReader.loadFromDirectory(openfluid::base::RuntimeEnvironment::
        getInstance()->getInputDir());

    PyOpenFLUID* ResClass = new PyOpenFLUID();
    ResClass->setFluidXDescriptor(FXReader);

    return ResClass;
  }
  catch (openfluid::base::OFException& E)
  {
    throw PyOFException(E.what());
  }
  catch (std::bad_alloc& E)
  {
    StrError = std::string("MEMORY ALLOCATION ERROR, ") + std::string(E.what())
        + std::string(". Possibly not enough memory available");
    throw PyOFException(StrError, PyExc_MemoryError);
  }
  catch (std::exception& E)
  {
    StrError = std::string("SYSTEM ERROR, ") + std::string(E.what());
    throw PyOFException(StrError, PyExc_SystemError);
  }
  catch (...)
  {
    throw PyOFException("UNKNOWN ERROR", PyExc_RuntimeError);
  }

  return NULL;
}


// =====================================================================
// =====================================================================


PyOpenFLUID* PyOpenFLUID::openProject (boost::python::object Path)
{
  boost::python::extract<std::string> getStringPath(Path);
  if (!getStringPath.check())
    throw PyOFException("needed string", PyExc_TypeError);

  std::string StrError = std::string("");
  std::string StrPath = getStringPath();

  try
  {
    openfluid::base::Init();

    if (openfluid::base::ProjectManager::getInstance()->open(StrPath))
    {
      openfluid::base::RuntimeEnvironment::getInstance()->linkToProject();
      openfluid::base::ProjectManager::getInstance()->updateOutputDir();
    }
    else
      throw openfluid::base::OFException("PyOpenFLUID", StrPath +
          " is not a correct project path");

    boost::python::str BoostPath = boost::python::str(
        openfluid::base::RuntimeEnvironment::getInstance()->getInputDir());
    return this->openDataset(BoostPath);
  }
  catch (openfluid::base::OFException& E)
  {
    throw PyOFException(E.what());
  }
  catch (std::bad_alloc& E)
  {
    StrError = std::string("MEMORY ALLOCATION ERROR, ") + std::string(E.what())
        + std::string(". Possibly not enough memory available");
    throw PyOFException(StrError, PyExc_MemoryError);
  }
  catch (std::exception& E)
  {
    StrError = std::string("SYSTEM ERROR, ") + std::string(E.what());
    throw PyOFException(StrError, PyExc_SystemError);
  }
  catch (...)
  {
    throw PyOFException("UNKNOWN ERROR", PyExc_RuntimeError);
  }

  return NULL;
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::setCurrentOutputDir (boost::python::object Path)
{
  boost::python::extract<std::string> getStringPath(Path);
  if (!getStringPath.check())
    throw PyOFException("needed string", PyExc_TypeError);

  openfluid::base::RuntimeEnvironment::getInstance()->
      setOutputDir(getStringPath());
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getCurrentOutputDir ()
{
  return boost::python::str(openfluid::base::RuntimeEnvironment::
      getInstance()->getOutputDir());
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
    throw PyOFException("needed integer", PyExc_TypeError);

  const int DefaultDeltaTInt = getDefaultDeltaT();
  if (DefaultDeltaTInt <= 0)
    throw PyOFException("DefaultDeltaT cann't be negative or null.",
        PyExc_ValueError);
  this->m_FXDesc.getRunDescriptor().setDeltaT(DefaultDeltaTInt);
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getPeriodBeginDate ()
{
  openfluid::core::DateTime BrutDate = this->m_FXDesc.getRunDescriptor()
      .getBeginDate();
  std::stringstream StreamRes(std::stringstream::in | std::stringstream::out);
  StreamRes << tools::zeroFill(boost::lexical_cast<std::string>(
      BrutDate.getYear()), 1) << "-";
  StreamRes << tools::zeroFill(boost::lexical_cast<std::string>(
      BrutDate.getMonth()), 2) << "-";
  StreamRes << tools::zeroFill(boost::lexical_cast<std::string>(
      BrutDate.getDay()), 2) << " ";
  StreamRes << tools::zeroFill(boost::lexical_cast<std::string>(
      BrutDate.getHour()), 2) << ":";
  StreamRes << tools::zeroFill(boost::lexical_cast<std::string>(
      BrutDate.getMinute()), 2) << ":";
  StreamRes << tools::zeroFill(boost::lexical_cast<std::string>(
      BrutDate.getSecond()), 2);
  return boost::python::str(StreamRes.str().c_str());
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getPeriodEndDate ()
{
  openfluid::core::DateTime BrutDate = this->m_FXDesc.getRunDescriptor()
      .getEndDate();
  std::stringstream StreamRes(std::stringstream::in | std::stringstream::out);
  StreamRes << tools::zeroFill(boost::lexical_cast<std::string>(
      BrutDate.getYear()), 1) << "-";
  StreamRes << tools::zeroFill(boost::lexical_cast<std::string>(
      BrutDate.getMonth()), 2) << "-";
  StreamRes << tools::zeroFill(boost::lexical_cast<std::string>(
      BrutDate.getDay()), 2) << " ";
  StreamRes << tools::zeroFill(boost::lexical_cast<std::string>(
      BrutDate.getHour()), 2) << ":";
  StreamRes << tools::zeroFill(boost::lexical_cast<std::string>(
      BrutDate.getMinute()), 2) << ":";
  StreamRes << tools::zeroFill(boost::lexical_cast<std::string>(
      BrutDate.getSecond()), 2);
  return boost::python::str(StreamRes.str().c_str());
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::setPeriodBeginDate (boost::python::object BDate)
{
  boost::python::extract<std::string> getStringBDate(BDate);
  if (!getStringBDate.check())
    throw PyOFException("needed string", PyExc_TypeError);

  std::string Pattern = std::string(
      "^(\\d{1,4})-(\\d{2})-(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2})$");
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

  openfluid::core::DateTime BDate = openfluid::core::DateTime(TabRes[0],
      TabRes[1], TabRes[2], TabRes[3], TabRes[4], TabRes[5]);
  this->m_FXDesc.getRunDescriptor().setBeginDate(BDate);
  }
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::setPeriodEndDate (boost::python::object EDate)
{
  boost::python::extract<std::string> getStringEDate(EDate);
  if (!getStringEDate.check())
    throw PyOFException("needed string", PyExc_TypeError);

  std::string Pattern = std::string(
      "^(\\d{1,4})-(\\d{2})-(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2})$");
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

  openfluid::core::DateTime BDate = openfluid::core::DateTime(TabRes[0],
      TabRes[1], TabRes[2], TabRes[3], TabRes[4], TabRes[5]);
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

    openfluid::machine::FunctionPluginsManager::getInstance()
        ->unloadAllWares();
    openfluid::machine::ObserverPluginsManager::getInstance()
        ->unloadAllWares();

    openfluid::machine::Engine* Engine;
    openfluid::machine::SimulationBlob SBlob;
    openfluid::base::RuntimeEnvironment* RunEnv;
    openfluid::machine::MachineListener* MachineListen =
        new openfluid::machine::MachineListener();

    openfluid::machine::ModelInstance Model(SBlob,MachineListen);
    openfluid::machine::MonitoringInstance Monitoring(SBlob);

    openfluid::machine::Factory::buildSimulationBlobFromDescriptors(
        this->m_FXDesc,SBlob);

    openfluid::machine::Factory::buildModelInstanceFromDescriptor(
        this->m_FXDesc.getModelDescriptor(), Model);

    openfluid::machine::Factory::buildMonitoringInstanceFromDescriptor(
        this->m_FXDesc.getMonitoringDescriptor(), Monitoring);

    Engine = new openfluid::machine::Engine(SBlob, Model, Monitoring,
        MachineListen);

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
    throw PyOFException(E.what());
  }
  catch (std::bad_alloc& E)
  {
    StrError = "MEMORY ALLOCATION ERROR, " + std::string(E.what()) +
        ". Possibly not enough memory available";
    throw PyOFException(StrError, PyExc_MemoryError);
  }
  catch (std::exception& E)
  {
    StrError = "SYSTEM ERROR, " + std::string(E.what());
    throw PyOFException(StrError, PyExc_SystemError);
  }
  catch (...)
  {
    throw PyOFException("UNKNOWN ERROR", PyExc_RuntimeError);
  }

  return boost::python::object(false);
}


// =====================================================================
// =====================================================================


//PyOpenFLUID* PyOpenFLUID::loadResult (boost::python::object UnitClass,
//                                           boost::python::object UnitID,
//                                           boost::python::object Suffix)
//{
//  throw PyOFException("unavailable method");
//}


// =====================================================================
// =====================================================================


//PyOpenFLUID* PyOpenFLUID::loadResultFile (boost::python::object FilePath)
//{
//  throw PyOFException("unavailable method");
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
//    (*DescIt).setHeaderType(openfluid::base::OutputFilesDescriptor::
//        ColnamesAsData);
//    (*DescIt).setDateFormat("%Y%m%d-%H%M%S");
//  }
}


// =====================================================================
/* ------------------------ PYTHON FUNCTIONS  ----------------------- */


boost::python::object PyOpenFLUID::getStr ()
{
  std::stringstream SStream(std::stringstream::in | std::stringstream::out);

  SStream << "PyOpenFLUID(" << openfluid::config::FULL_VERSION.c_str();
  SStream << ")";

  return boost::python::object(SStream.str());
}


// =====================================================================
/* ------------------------ OTHER FUNCTIONS  ------------------------ */


void PyOpenFLUID::setFluidXDescriptor (
    openfluid::fluidx::FluidXDescriptor& InputFXD)
{
  this->m_FXDesc = InputFXD;
}


// =====================================================================
// =====================================================================


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
