#include <Python.h>
#include <boost/python/str.hpp>
#include <boost/python/dict.hpp>
#include <boost/python/list.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/object.hpp>

#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/exception/all.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/optional.hpp>

#include <map>
#include <list>
#include <vector>
#include <string>
#include <utility>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <exception>

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
#include <openfluid/fluidx/WareDescriptor.hpp>
#include <openfluid/fluidx/UnitDescriptor.hpp>
#include <openfluid/fluidx/IDataDescriptor.hpp>
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

PyObject* PyOpenFLUID::raw_getVersion (PyObject* InTuple, PyObject* InDict)
{
  return PyString_FromString((const char*)
      openfluid::config::FULL_VERSION.c_str());
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
    ListPath.append(boost::python::str(*IterVectPath));

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
    ListPath.append(boost::python::str(*IterVectPath));

  return ListPath;
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::printSimulationInfo ()
{
  /* output stream */
  std::stringstream SStream(std::stringstream::in | std::stringstream::out);

  /* Spatial domain */
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


  /* Model */
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

  /* Time period */
  SStream << "Simulation period from " <<
      this->m_FXDesc.getRunDescriptor().getBeginDate().getAsISOString().c_str()
      << " to "
      << this->m_FXDesc.getRunDescriptor().getEndDate().getAsISOString().c_str()
      << std::endl;

  /* Time step */
  SStream << "Simulation time step : "
      << this->m_FXDesc.getRunDescriptor().getDeltaT() << std::endl;

  /* Printing */
  pyopenfluid::topython::printStdOut(SStream);
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

  /* looking for position of the function */
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
        break;
    }
    ++ItModelInfos;
  }

  /* if exists (=> by position), gets (if possible) */
  if (ItModelInfos != ModelInfos.end())
  {
    boost::optional<std::string> Res =
        FuncDescp->getParameters().get_optional<std::string>(ParamNameStr);

    if (Res)
      return boost::python::str(*Res);
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

  /* looking for position of the function */
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
      break;
    ++ItModelInfos;
  }

  /* if exists (=> by position), sets */
  if (ItModelInfos != ModelInfos.end())
  {
    (*ItModelInfos)->setParameter(ParamNameStr,ParamValueStr);
  }
  else
    pyopenfluid::topython::printWarning("function doesn't exists");
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

  /* looking for position of the function */
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
        break;
    }
    ++ItModelInfos;
  }

  /* if exists (=> by position), erase */
  if (ItModelInfos != ModelInfos.end())
    Function->eraseParameter(ParamNameStr);
  else
    pyopenfluid::topython::printWarning("function doesn't exists");
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getFunctionParams(
    boost::python::object FuncID)
{
  boost::python::extract<std::string> getStringFuncID(FuncID);
  if (!getStringFuncID.check())
    throw PyOFException("needed string for function id", PyExc_TypeError);

  std::string FuncIDStr = getStringFuncID();

  boost::python::list ListRes = boost::python::list();

  /* looking for position of the generator */
  openfluid::ware::WareParams_t Params;

  openfluid::ware::WareParams_t::iterator ItParam;

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t
      ModelInfos = this->m_FXDesc.getModelDescriptor().getItems();

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator
      ItModelInfos;

  for (ItModelInfos = ModelInfos.begin(); ItModelInfos != ModelInfos.end();
      ++ItModelInfos)
  {
    if ((*ItModelInfos)->isType(
          openfluid::fluidx::ModelItemDescriptor::PluggedFunction) &&
        ((openfluid::fluidx::FunctionDescriptor*)(*ItModelInfos))->getFileID()
          == FuncIDStr)
      break;
  }

  /* if exists (=> by position), gets */
  if (ItModelInfos != ModelInfos.end())
  {
    Params = (*ItModelInfos)->getParameters();
    for (ItParam = Params.begin(); ItParam != Params.end(); ++ItParam)
      ListRes.append(boost::python::str((*ItParam).first));
  }

  return ListRes;
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

  /* looking for position of the generator */
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
        break;
    }
    ++ItModelInfos;
  }

  /* if exists (=> by position), returns */
  if (ItModelInfos != ModelInfos.end())
  {
    boost::optional<std::string> Res =
        GenDescp->getParameters().get_optional<std::string>(ParamNameStr);

    if (Res)
      return boost::python::str(*Res);
  }
  else
    pyopenfluid::topython::printWarning("generator doesn't exists");

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

  /* looking for position of the parameter */
  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t
      ModelInfos = this->m_FXDesc.getModelDescriptor().getItems();

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator
      ItModelInfos = ModelInfos.begin();

  openfluid::fluidx::GeneratorDescriptor* GenDescp;

  while (ItModelInfos != ModelInfos.end())
  {
    if ((*ItModelInfos)->isType(
        openfluid::fluidx::ModelItemDescriptor::Generator))
    {
      GenDescp = (openfluid::fluidx::GeneratorDescriptor*)(*ItModelInfos);
      if (GenDescp->getUnitClass() == UnitClassStr &&
          GenDescp->getVariableName() == VarNameStr)
        break;
    }
    ++ItModelInfos;
  }

  /* if exists (=> by position), sets */
  if (ItModelInfos != ModelInfos.end())
    GenDescp->setParameter(ParamNameStr, ParamValueStr);
  else
    pyopenfluid::topython::printWarning("generator doesn't exists");
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

  /* looking for position of the parameter */
  openfluid::ware::WareParams_t Params = this->m_FXDesc.getModelDescriptor()
      .getGlobalParameters();
  openfluid::ware::WareParams_t::iterator ItParam = Params.begin();

  while (ItParam != Params.end() && (*ItParam).first != ParamNameStr)
    ++ItParam;

  /* if found, or else return NONE */
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


boost::python::object PyOpenFLUID::getModelGlobalParams ()
{
  boost::python::list ListRes = boost::python::list();

  openfluid::ware::WareParams_t Params = this->m_FXDesc.getModelDescriptor()
      .getGlobalParameters();
  openfluid::ware::WareParams_t::iterator ItParam;

  for (ItParam = Params.begin(); ItParam != Params.end(); ++ItParam)
    ListRes.append(boost::python::str((*ItParam).first));

  return ListRes;
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

  /* looking for position of the function in list */
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
        break;
    }
    ++ItModelInfos;
  }

  /* raising exception if exists, or else adds */
  if (ItModelInfos != ModelInfos.end())
    throw PyOFException("function id already exists");
  else
  {
    openfluid::fluidx::FunctionDescriptor* NewFunction =
        new openfluid::fluidx::FunctionDescriptor(FuncIDStr);

    this->m_FXDesc.getModelDescriptor().appendItem(NewFunction);
  }
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::removeFunction (boost::python::object FuncID)
{
  boost::python::extract<std::string> getStringFuncID(FuncID);
  if (!getStringFuncID.check())
    throw PyOFException("needed string for observer id", PyExc_TypeError);

  std::string FuncIDStr = getStringFuncID();

  /* looking for position of the function in list */
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
        break;
    }
    ++ItModelInfos;
  }

  /* if exists (=> by position), remove */
  if (ItModelInfos != ModelInfos.end())
    ModelInfos.erase(ItModelInfos);
  else
    pyopenfluid::topython::printWarning("function doesn't exist");
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
// =====================================================================


boost::python::object PyOpenFLUID::getFunctionsInModel ()
{
  boost::python::list ListRes = boost::python::list();

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t&
      ModelInfos = this->m_FXDesc.getModelDescriptor().getItems();

  openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator
      ItModelInfos;

  for (ItModelInfos = ModelInfos.begin(); ItModelInfos != ModelInfos.end();
      ++ItModelInfos)
    if ((*ItModelInfos)->isType(
        openfluid::fluidx::ModelItemDescriptor::PluggedFunction))
      ListRes.append(boost::python::str((
        (openfluid::fluidx::FunctionDescriptor*)(*ItModelInfos)
        )->getFileID()));

  return ListRes;
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

  /* looking for position of the observer */
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
        break;
    }
    ++ItModelInfos;
  }

  /* if exists (=> by position), returns if possible */
  if (ItModelInfos != ModelInfos.end())
  {
    boost::optional<std::string> Res =
        ObsDescp->getParameters().get_optional<std::string>(ParamNameStr);

    if (Res)
      return boost::python::str(*Res);
  }
  else
    pyopenfluid::topython::printWarning("observer doesn't exist");

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

  /* looking for position of the observer */
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
        break;
    }
    ++ItModelInfos;
  }

  /* if exists (=> by position), sets (possible new) parameter */
  if (ItModelInfos != ModelInfos.end())
    ObsDescp->setParameter(ParamNameStr, ParamValueStr);
  else
    pyopenfluid::topython::printWarning("observer doesn't exist");
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

  /* looking for position of the observer */
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
        break;
    }
    ++ItModelInfos;
  }

  /* if exists (=> by position), removes (possible new) parameter */
  if (ItModelInfos != ModelInfos.end())
    ObsDescp->eraseParameter(ParamNameStr);
  else
    pyopenfluid::topython::printWarning("observer doesn't exist");
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getObserverParams (
    boost::python::object ObsID)
{
  boost::python::extract<std::string> getStringObsID(ObsID);
  if (!getStringObsID.check())
    throw PyOFException("needed string for observer id", PyExc_TypeError);

  std::string ObsIDStr = getStringObsID();

  boost::python::list ListRes = boost::python::list();

  /* looking for position of the observer */
  openfluid::ware::WareParams_t Params;

  openfluid::ware::WareParams_t::iterator ItParam;

  openfluid::fluidx::MonitoringDescriptor::SetDescription_t
      ModelInfos = this->m_FXDesc.getMonitoringDescriptor().getItems();

  openfluid::fluidx::MonitoringDescriptor::SetDescription_t::iterator
      ItModelInfos;

  for (ItModelInfos = ModelInfos.begin(); ItModelInfos != ModelInfos.end();
      ++ItModelInfos)
  {
    if ((*ItModelInfos)->isType(
        openfluid::fluidx::ModelItemDescriptor::PluggedObserver))
      break;
  }

  /* if exists (=> by position), gets all parameters */
  if (ItModelInfos != ModelInfos.end())
  {
      Params = ((openfluid::fluidx::ObserverDescriptor*)(*ItModelInfos))->
          getParameters();

      std::map<std::string, std::string> MapInfos =
          openfluid::fluidx::WareDescriptor::getParamsAsMap(Params);

      std::map<std::string, std::string>::iterator ItMapInfos;

      for (ItMapInfos = MapInfos.begin(); ItMapInfos != MapInfos.end();
          ++ItMapInfos)
        ListRes.append(boost::python::str((*ItMapInfos).first));
  }

  return ListRes;
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::addObserver (boost::python::object ObsID)
{
  boost::python::extract<std::string> getStringObsID(ObsID);
  if (!getStringObsID.check())
    throw PyOFException("needed string for observer id", PyExc_TypeError);

  std::string ObsIDStr = getStringObsID();

  /* looking for position of the observer in list */
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
        break;
    }
    ++ItModelInfos;
  }

  /* raising exception if exists, or else adds */
  if (ItModelInfos != ModelInfos.end())
    throw PyOFException("observer id already exists");
  else
  {
    openfluid::fluidx::ObserverDescriptor* NewObserver =
        new openfluid::fluidx::ObserverDescriptor(ObsIDStr);

    this->m_FXDesc.getMonitoringDescriptor().appendItem(NewObserver);
  }
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::removeObserver (boost::python::object ObsID)
{
  boost::python::extract<std::string> getStringObsID(ObsID);
  if (!getStringObsID.check())
    throw PyOFException("needed string for observer id", PyExc_TypeError);

  std::string ObsIDStr = getStringObsID();

  /* looking for position of the observer */
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
        break;
    }
    ++ItModelInfos;
  }

  /* if exists (=> by position), erases it from descriptor */
  if (ItModelInfos != ModelInfos.end())
    ModelInfos.erase(ItModelInfos);
  else
    pyopenfluid::topython::printWarning("observer doesn't exist");
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
// =====================================================================


boost::python::object PyOpenFLUID::getObserversInMonitoring ()
{
  boost::python::list ListRes = boost::python::list();

  openfluid::fluidx::MonitoringDescriptor::SetDescription_t
      ModelInfos = this->m_FXDesc.getMonitoringDescriptor().getItems();

  openfluid::fluidx::MonitoringDescriptor::SetDescription_t::iterator
      ItModelInfos;

  for (ItModelInfos = ModelInfos.begin(); ItModelInfos != ModelInfos.end();
      ++ItModelInfos)
    if ((*ItModelInfos)->isType(
        openfluid::fluidx::ModelItemDescriptor::PluggedObserver))
      ListRes.append(boost::python::str((
          (openfluid::fluidx::ObserverDescriptor*)(*ItModelInfos))->getID()));

  return ListRes;
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


boost::python::object PyOpenFLUID::getUnitsIDs (
    boost::python::object UnitClass)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyOFException("needed string for unit class", PyExc_TypeError);

  std::string UnitClassRef = getStringUnitClass();

  boost::python::list ListID = boost::python::list();

  std::list<openfluid::fluidx::UnitDescriptor>
      ListUnit = this->m_FXDesc.getDomainDescriptor().getUnits();

  std::list<openfluid::fluidx::UnitDescriptor>::iterator IterUnit;

  for (IterUnit = ListUnit.begin(); IterUnit != ListUnit.end(); ++IterUnit)
    if ((*IterUnit).getUnitClass() == UnitClassRef )
      ListID.append(boost::python::object((*IterUnit).getUnitID()));

  return ListID;
}


// =====================================================================
// =====================================================================

// TODO fixed colums order
void PyOpenFLUID::addUnit (boost::python::object UnitClass,
                           boost::python::object UnitID,
                           boost::python::object PcsOrder)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyOFException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitID(UnitID);
  if (!getIntUnitID.check())
    throw PyOFException("needed integer for unit id", PyExc_TypeError);
  boost::python::extract<int> getIntProcessOrder(PcsOrder);
  if (!getIntProcessOrder.check())
    throw PyOFException("needed integer for process order", PyExc_TypeError);

  std::string UnitClassStr = getStringUnitClass();
  int UnitIDInt = getIntUnitID();
  int PcsOrderInt = getIntProcessOrder();

  std::list<openfluid::fluidx::UnitDescriptor>& ListUnit =
      this->m_FXDesc.getDomainDescriptor().getUnits();

  std::list<openfluid::fluidx::UnitDescriptor>::iterator IterUnit;

  openfluid::fluidx::UnitDescriptor UnitDesp;

  /* searches for unique id */
  for (IterUnit = ListUnit.begin(); IterUnit != ListUnit.end(); ++IterUnit)
  {
    UnitDesp = *IterUnit;
    if (UnitDesp.getUnitClass() == UnitClassStr && UnitDesp.getUnitID()
        == UnitIDInt)
      throw PyOFException("unit already exists", PyExc_ValueError);
  }

  /* adds */
  openfluid::fluidx::UnitDescriptor* NewUnitDesp;
  NewUnitDesp = new openfluid::fluidx::UnitDescriptor();
  NewUnitDesp->getUnitClass().assign(UnitClassStr);
  NewUnitDesp->getUnitID() = UnitIDInt;
  NewUnitDesp->getProcessOrder() = PcsOrderInt;
  ListUnit.push_back(*NewUnitDesp);

  /* -- adds in input data -- */
  std::list<openfluid::fluidx::InputDataDescriptor>&
      IData = this->m_FXDesc.getDomainDescriptor().getInputData();

  std::list<openfluid::fluidx::InputDataDescriptor>::iterator
    ItIData = IData.begin();

  /* searching for unit class */
  while (ItIData != IData.end() && (*ItIData).getUnitsClass() != UnitClassStr)
    ++ItIData;

  /* if new unit class */
  if (ItIData == IData.end())
  {
    openfluid::fluidx::InputDataDescriptor* InputDataUnitDespPtr;
    /* new input data class */
    InputDataUnitDespPtr = new openfluid::fluidx::InputDataDescriptor();
    InputDataUnitDespPtr->getUnitsClass().assign(UnitClassStr);
    InputDataUnitDespPtr->getData() =
        openfluid::fluidx::InputDataDescriptor::UnitIDInputData_t();
    InputDataUnitDespPtr->getColumnsOrder() = std::vector<std::string>();
    IData.push_back(*InputDataUnitDespPtr);
    ItIData = IData.end();
    --ItIData;
  }

  openfluid::fluidx::InputDataDescriptor& InputDataUnitDesp = *ItIData;

  // the class that contains all input datas of an unit
  openfluid::fluidx::InputDataDescriptor::InputDataNameValue_t
    InputDataNameValue = 
      openfluid::fluidx::InputDataDescriptor::InputDataNameValue_t();

  // if there is an unit in the unit class
  // we fill the list of input data with empty string for each key
  if (InputDataUnitDesp.getData().size() > 0)
  {
    openfluid::fluidx::InputDataDescriptor::InputDataNameValue_t ListKeys =
        (*InputDataUnitDesp.getData().begin()).second;

    for (openfluid::fluidx::InputDataDescriptor::InputDataNameValue_t::iterator
        ItKey = ListKeys.begin(); ItKey != ListKeys.end(); ++ItKey)
      InputDataNameValue.insert(InputDataNameValue.begin(),
        std::pair<openfluid::core::InputDataName_t,
                  std::string>
            ((*ItKey).first, std::string("")));
  }

  // building the pair to add to the list of ids' input data
  std::pair<openfluid::core::UnitID_t,
            openfluid::fluidx::InputDataDescriptor::InputDataNameValue_t>
    PairInputDataNameValue =
      std::pair<openfluid::core::UnitID_t,
                openfluid::fluidx::InputDataDescriptor::InputDataNameValue_t>
        (UnitIDInt, InputDataNameValue);

  // adding to the end the new unit
  InputDataUnitDesp.getData().insert(InputDataUnitDesp.getData().end(),
    PairInputDataNameValue);
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::removeUnit (boost::python::object UnitClass,
                              boost::python::object UnitID)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyOFException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitID(UnitID);
  if (!getIntUnitID.check())
    throw PyOFException("needed integer for unit id", PyExc_TypeError);

  std::string UnitClassStr = getStringUnitClass();
  int UnitIDInt = getIntUnitID();

  /* looking for position of the unit */
  std::list<openfluid::fluidx::UnitDescriptor>& ListUnit =
      this->m_FXDesc.getDomainDescriptor().getUnits();

  std::list<openfluid::fluidx::UnitDescriptor>::iterator
      IterUnit = ListUnit.begin();

  openfluid::fluidx::UnitDescriptor UnitDesp;

  while (IterUnit != ListUnit.end())
  {
    UnitDesp = *IterUnit;
    if (UnitDesp.getUnitClass() == UnitClassStr && UnitDesp.getUnitID()
        == UnitIDInt)
      break;
    ++IterUnit;
  }

  /* if exists (=> by position), erases it from descriptor */
  if (IterUnit != ListUnit.end())
    ListUnit.erase(IterUnit);
  else
    pyopenfluid::topython::printWarning("unit doesn't exist");

  /* -- removes in input data -- */
  std::list<openfluid::fluidx::InputDataDescriptor>&
      IData = this->m_FXDesc.getDomainDescriptor().getInputData();

  std::list<openfluid::fluidx::InputDataDescriptor>::iterator
    ItIData = IData.begin();

  /* searching for unit class */
  while (ItIData != IData.end() && (*ItIData).getUnitsClass() != UnitClassStr)
    ++ItIData;

  /* if unit class exists */
  if (ItIData != IData.end())
  {
    openfluid::fluidx::InputDataDescriptor::UnitIDInputData_t& IDataIDDescp =
        (*ItIData).getData();

    openfluid::fluidx::InputDataDescriptor::UnitIDInputData_t::iterator
        ItIDataID = IDataIDDescp.begin();

    /* searching for unit id */
    while (ItIDataID != IDataIDDescp.end() && (*ItIDataID).first
        != getIntUnitID)
      ++ItIDataID;

    /* if unit id exists */
    if (ItIDataID != IDataIDDescp.end())
    {
      IDataIDDescp.erase(ItIDataID);
    }
    else
      pyopenfluid::topython::printWarning(
          "unit id doesn't exist in input data");
  }
  else
    pyopenfluid::topython::printWarning(
        "unit class doesn't exist in input data");
}


// =====================================================================
// =====================================================================

// TODO: olso erase link between units !!!
void PyOpenFLUID::clearUnitClass (boost::python::object UnitClass)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyOFException("needed string for unit class", PyExc_TypeError);

  std::string UnitClassStr = getStringUnitClass();

  std::list<openfluid::fluidx::UnitDescriptor>& ListUnit =
      this->m_FXDesc.getDomainDescriptor().getUnits();

  std::list<openfluid::fluidx::UnitDescriptor>::iterator
      IterUnit = ListUnit.begin();

  while (IterUnit != ListUnit.end())
  {
    if (((openfluid::fluidx::UnitDescriptor)(*IterUnit)).getUnitClass()
        == UnitClassStr)
      IterUnit = ListUnit.erase(IterUnit);
    else
      ++IterUnit;
  }
}


// =====================================================================
// =====================================================================

//TODO change replace operation
void PyOpenFLUID::setUnitProcessOrder (boost::python::object UnitClass,
                                       boost::python::object UnitID,
                                       boost::python::object PcsOrder)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyOFException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitID(UnitID);
  if (!getIntUnitID.check())
    throw PyOFException("needed integer for unit id", PyExc_TypeError);
  boost::python::extract<int> getIntProcessOrder(PcsOrder);
  if (!getIntProcessOrder.check())
    throw PyOFException("needed integer for process order", PyExc_TypeError);

  std::string UnitClassStr = getStringUnitClass();
  int UnitIDInt = getIntUnitID();
  int ProcessOrderInt = getIntProcessOrder();

  /* looking for position of the unit */
  std::list<openfluid::fluidx::UnitDescriptor>& ListUnit =
      this->m_FXDesc.getDomainDescriptor().getUnits();

  std::list<openfluid::fluidx::UnitDescriptor>::iterator
      IterUnit = ListUnit.begin();

  openfluid::fluidx::UnitDescriptor UnitDesp;

  while (IterUnit != ListUnit.end())
  {
    UnitDesp = *IterUnit;
    if (UnitDesp.getUnitClass() == UnitClassStr && UnitDesp.getUnitID()
        == UnitIDInt)
      break;
    ++IterUnit;
  }

  /* if exists (=> by position), change its value and replaces it from list */
  if (IterUnit != ListUnit.end())
  {
    UnitDesp.getProcessOrder() = ProcessOrderInt;
    IterUnit = ListUnit.erase(IterUnit);
    ListUnit.insert(IterUnit, UnitDesp);
  }
  else
    pyopenfluid::topython::printWarning("unit doesn't exists");
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getUnitProcessOrder (
    boost::python::object UnitClass, boost::python::object UnitID)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyOFException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitID(UnitID);
  if (!getIntUnitID.check())
    throw PyOFException("needed integer for unit id", PyExc_TypeError);

  std::string UnitClassStr = getStringUnitClass();
  int UnitIDInt = getIntUnitID();

  /* looking for position of the unit */
  std::list<openfluid::fluidx::UnitDescriptor>& ListUnit =
      this->m_FXDesc.getDomainDescriptor().getUnits();

  std::list<openfluid::fluidx::UnitDescriptor>::iterator
      IterUnit = ListUnit.begin();

  openfluid::fluidx::UnitDescriptor UnitDesp;

  while (IterUnit != ListUnit.end())
  {
    UnitDesp = *IterUnit;
    if (UnitDesp.getUnitClass() == UnitClassStr && UnitDesp.getUnitID()
        == UnitIDInt)
      break;
    ++IterUnit;
  }

  /* if exists (=> by position), change its value and replaces it from list */
  if (IterUnit != ListUnit.end())
    return boost::python::object(UnitDesp.getProcessOrder());

  return boost::python::object(); /* makes Python NONE */
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getUnitsChildren (
    boost::python::object UnitClass, boost::python::object UnitID)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyOFException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitID(UnitID);
  if (!getIntUnitID.check())
    throw PyOFException("needed integer for unit id", PyExc_TypeError);

  std::string UnitClassStr = getStringUnitClass();
  int UnitIDInt = getIntUnitID();

  boost::python::list ListRes = boost::python::list();

  std::list<openfluid::fluidx::UnitDescriptor> ListUnit =
      this->m_FXDesc.getDomainDescriptor().getUnits();

  std::list<openfluid::fluidx::UnitDescriptor>::iterator IterUnit;

  std::list<openfluid::core::UnitClassID_t> ListUnits;
  std::list<openfluid::core::UnitClassID_t>::iterator ItUnits;

  for (IterUnit = ListUnit.begin(); IterUnit != ListUnit.end(); ++IterUnit)
  {
    ListUnits = (*IterUnit).getUnitsParents();
    ItUnits = ListUnits.begin();
    while (ItUnits != ListUnits.end() && ( (*ItUnits).first != UnitClassStr
        || (*ItUnits).second != UnitIDInt) )
      ++ItUnits;

    if (ItUnits != ListUnits.end())
      ListRes.append(boost::python::make_tuple(
          boost::python::str((*IterUnit).getUnitClass()),
          boost::python::object((*IterUnit).getUnitID()) ));
  }

  return ListRes;
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getUnitsParents (
    boost::python::object UnitClass, boost::python::object UnitID)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyOFException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitID(UnitID);
  if (!getIntUnitID.check())
    throw PyOFException("needed integer for unit id", PyExc_TypeError);

  std::string UnitClassStr = getStringUnitClass();
  int UnitIDInt = getIntUnitID();

  boost::python::list ListRes = boost::python::list();

  std::list<openfluid::fluidx::UnitDescriptor> ListUnit =
      this->m_FXDesc.getDomainDescriptor().getUnits();

  std::list<openfluid::fluidx::UnitDescriptor>::iterator IterUnit;

  openfluid::fluidx::UnitDescriptor UnitDesp;

  std::list<openfluid::core::UnitClassID_t> ListUnits;
  std::list<openfluid::core::UnitClassID_t>::iterator ItUnits;

  for (IterUnit = ListUnit.begin(); IterUnit != ListUnit.end(); ++IterUnit)
  {
    UnitDesp = *IterUnit;
    if (UnitDesp.getUnitClass() == UnitClassStr && UnitDesp.getUnitID()
        == UnitIDInt)
    {
      ListUnits = UnitDesp.getUnitsParents();
      for (ItUnits = ListUnits.begin(); ItUnits != ListUnits.end(); ++ItUnits)
        ListRes.append(boost::python::make_tuple(
            boost::python::str((*ItUnits).first),
            boost::python::object((*ItUnits).second) ));
      break;
    }
  }

  return ListRes;
}


// =====================================================================
// =====================================================================

// TODO change replace operation
void PyOpenFLUID::addUnitChild (
    boost::python::object UnitClassFrom, boost::python::object UnitIDFrom,
    boost::python::object UnitClassTo, boost::python::object UnitIDTo)
{
  boost::python::extract<std::string> getStringUnitClassFrom(UnitClassFrom);
  if (!getStringUnitClassFrom.check())
    throw PyOFException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitIDFrom(UnitIDFrom);
  if (!getIntUnitIDFrom.check())
    throw PyOFException("needed integer for unit id", PyExc_TypeError);

  boost::python::extract<std::string> getStringUnitClassTo(UnitClassTo);
  if (!getStringUnitClassTo.check())
    throw PyOFException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitIDTo(UnitIDTo);
  if (!getIntUnitIDTo.check())
    throw PyOFException("needed integer for unit id", PyExc_TypeError);

  std::string UnitClassFromStr = getStringUnitClassFrom();
  int UnitIDFromInt = getIntUnitIDFrom();

  std::string UnitClassToStr = getStringUnitClassTo();
  int UnitIDToInt = getIntUnitIDTo();

  std::list<openfluid::fluidx::UnitDescriptor>& ListUnit =
      this->m_FXDesc.getDomainDescriptor().getUnits();

  std::list<openfluid::fluidx::UnitDescriptor>::iterator IterUnitFrom;

  std::list<openfluid::fluidx::UnitDescriptor>::iterator IterUnitTo;

  openfluid::fluidx::UnitDescriptor UnitDespFrom;
  openfluid::fluidx::UnitDescriptor UnitDespTo;

  std::list<openfluid::core::UnitClassID_t> ListUnits;
  std::list<openfluid::core::UnitClassID_t>::iterator ItUnits;

  /* check (child) unit exists */
  IterUnitTo = ListUnit.begin();
  while (IterUnitTo != ListUnit.end() && ((*IterUnitTo).getUnitClass()
      != UnitClassToStr || (*IterUnitTo).getUnitID() != UnitIDToInt) )
    ++IterUnitTo;

  /* if child units doesn't exist */
  if (IterUnitTo == ListUnit.end())
    throw PyOFException("child unit doesn't exist", PyExc_ValueError);

  /* check (parent) unit exists */
  IterUnitFrom = ListUnit.begin();
  while (IterUnitFrom != ListUnit.end() && ((*IterUnitFrom).getUnitClass()
      != UnitClassFromStr || (*IterUnitFrom).getUnitID() != UnitIDFromInt) )
    ++IterUnitFrom;

  /* if parent units doesn't exist */
  if (IterUnitFrom == ListUnit.end())
    throw PyOFException("parent unit doesn't exist", PyExc_ValueError);

  /* if both units exist */
  UnitDespTo = *IterUnitTo;
  UnitDespFrom = *IterUnitFrom;

  /* check the link */
  ListUnits = UnitDespTo.getUnitsParents();
  ItUnits = ListUnits.begin();
  while (ItUnits != ListUnits.end() && ( (*ItUnits).first != UnitClassFromStr
      || (*ItUnits).second != UnitIDFromInt ))
    ++ItUnits;

  /* if doesn't exist */
  if (ItUnits == ListUnits.end())
  {
    std::pair<std::string, int> TmpUnit = std::pair<std::string, int>
        (UnitClassFromStr, UnitIDFromInt);

    /* replacing */
    UnitDespTo.getUnitsParents().push_back(TmpUnit);
    IterUnitTo = ListUnit.erase(IterUnitTo);
    ListUnit.insert(IterUnitTo, UnitDespTo);
  }
  else
    pyopenfluid::topython::printWarning("units are already linked");
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::removeUnitChild (
    boost::python::object UnitClassFrom, boost::python::object UnitIDFrom,
    boost::python::object UnitClassTo, boost::python::object UnitIDTo)
{
  boost::python::extract<std::string> getStringUnitClassFrom(UnitClassFrom);
  if (!getStringUnitClassFrom.check())
    throw PyOFException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitIDFrom(UnitIDFrom);
  if (!getIntUnitIDFrom.check())
    throw PyOFException("needed integer for unit id", PyExc_TypeError);

  boost::python::extract<std::string> getStringUnitClassTo(UnitClassTo);
  if (!getStringUnitClassTo.check())
    throw PyOFException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitIDTo(UnitIDTo);
  if (!getIntUnitIDTo.check())
    throw PyOFException("needed integer for unit id", PyExc_TypeError);

  std::string UnitClassFromStr = getStringUnitClassFrom();
  int UnitIDFromInt = getIntUnitIDFrom();

  std::string UnitClassToStr = getStringUnitClassTo();
  int UnitIDToInt = getIntUnitIDTo();

  std::list<openfluid::fluidx::UnitDescriptor>& ListUnit =
      this->m_FXDesc.getDomainDescriptor().getUnits();

  std::list<openfluid::fluidx::UnitDescriptor>::iterator IterUnitFrom;
  std::list<openfluid::fluidx::UnitDescriptor>::iterator IterUnitTo;

  /* check (child) unit exists */
  IterUnitTo = ListUnit.begin();
  while (IterUnitTo != ListUnit.end() && ((*IterUnitTo).getUnitClass()
      != UnitClassToStr || (*IterUnitTo).getUnitID() != UnitIDToInt) )
    ++IterUnitTo;

  /* if child unit doesn't exist */
  if (IterUnitTo == ListUnit.end())
    throw PyOFException("child unit doesn't exist", PyExc_ValueError);

  /* check (parent) unit exists */
  IterUnitFrom = ListUnit.begin();
  while (IterUnitFrom != ListUnit.end() && ((*IterUnitFrom).getUnitClass()
      != UnitClassFromStr || (*IterUnitFrom).getUnitID() != UnitIDFromInt) )
    ++IterUnitFrom;

  /* if parent unit doesn't exist */
  if (IterUnitFrom == ListUnit.end())
    throw PyOFException("parent unit doesn't exist", PyExc_ValueError);

  /* both units exist AT THIS POINT */
  /* checking the link */
  std::list<openfluid::core::UnitClassID_t>& ListUnits
      = (*IterUnitTo).getUnitsParents();
  std::list<openfluid::core::UnitClassID_t>::iterator ItUnits;

  ItUnits = ListUnits.begin();
  while (ItUnits != ListUnits.end() && ( (*ItUnits).first != UnitClassFromStr
      || (*ItUnits).second != UnitIDFromInt ))
    ++ItUnits;

  /* if exists, removing */
  if (ItUnits != ListUnits.end())
    ItUnits = ListUnits.erase(ItUnits);
  else
    pyopenfluid::topython::printWarning("units aren't linked");
}


// =====================================================================
// =====================================================================


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
    ItIData = IData.begin();

  openfluid::fluidx::InputDataDescriptor::UnitIDInputData_t::iterator
      ItUnitData;

  std::pair<openfluid::core::InputDataName_t,std::string>
      UnitDataName;

  bool keyExists = TRUE;

  std::cout << "searching for unit class ..";
  /* searching for unit class */
  while (ItIData != IData.end() && (*ItIData).getUnitsClass() != UnitClassStr)
    ++ItIData;
  std::cout << "." << std::endl;

  /* searching for unit name in the first unit */
  if (ItIData != IData.end())
  {
    if ((*ItIData).getData().size() > 0)
    {
      std::cout << "unit class empty" << std::endl;
      keyExists = FALSE;
    }
    else
    {
      std::cout << "searching for unit name ..";
      ItUnitData = (*ItIData).getData().begin();
      keyExists = (*ItUnitData).second.find(IDataNameStr) !=
          (*ItUnitData).second.end();
      std::cout << "." << std::endl;
    }

    if (!keyExists)
    {
      /* for all unit id */
      std::cout << "for all unit id" << std::endl;
      for (ItUnitData = (*ItIData).getData().begin(); ItUnitData !=
          (*ItIData).getData().end(); ++ItUnitData)
      {
        UnitDataName = std::pair<openfluid::core::InputDataName_t,std::string>
            (IDataNameStr, IDataValStr);
        std::cout << "item: " << (*ItUnitData).first << std::endl;
        (*ItUnitData).second.insert((*ItUnitData).second.end(), UnitDataName);
      }
    }
    else
      pyopenfluid::topython::printWarning("input data name exists");
  }
  else
    pyopenfluid::topython::printWarning("unit class doesn't exist");

  // TODO add key to colums order
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
    ItIData = IData.begin();

  openfluid::fluidx::InputDataDescriptor::UnitIDInputData_t::iterator
      ItUnitData;

  openfluid::fluidx::InputDataDescriptor::InputDataNameValue_t::iterator
      ItUnitDataName;

  /* searching for unit class */
  while (ItIData != IData.end() && (*ItIData).getUnitsClass() != UnitClassStr)
    ++ItIData;

  if (ItIData != IData.end())
  {
    /* searching for unit id */
    ItUnitData = (*ItIData).getData().find(UnitIDInt);

    if (ItUnitData != (*ItIData).getData().end())
    {
      /* searching for unit name */
      ItUnitDataName = (*ItUnitData).second.find(IDataNameStr);

      if (ItUnitDataName != (*ItUnitData).second.end())
      {
        return boost::python::str((*ItUnitDataName).second);
      }
    }
    else
      pyopenfluid::topython::printWarning("unit id doesn't exist");
  }
  else
    pyopenfluid::topython::printWarning("unit class doesn't exist");

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

  std::list<openfluid::fluidx::InputDataDescriptor>::iterator
    ItIData = IData.begin();

  openfluid::fluidx::InputDataDescriptor::UnitIDInputData_t::iterator
      ItUnitData;

  /* searching for unit class */
  while (ItIData != IData.end() && (*ItIData).getUnitsClass() != UnitClassStr)
    ++ItIData;

  if (ItIData != IData.end())
  {
    /* searching for unit id */
    ItUnitData = (*ItIData).getData().find(UnitIDInt);

    if (ItUnitData != (*ItIData).getData().end())
    {
      /* searching for unit name */
      if ((*ItUnitData).second.find(IDataNameStr) !=
          (*ItUnitData).second.end())
      {
        (*ItUnitData).second[IDataNameStr] = IDataValStr;
      }
      else
        pyopenfluid::topython::printWarning("input data name doesn't exist");
    }
    else
      pyopenfluid::topython::printWarning("unit id doesn't exist");
  }
  else
    pyopenfluid::topython::printWarning("unit class doesn't exist");
}


// =====================================================================
// =====================================================================

// TODO see if it is optimizable
void PyOpenFLUID::removeInputData (boost::python::object UnitClass,
                                   boost::python::object IDataName)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyOFException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<std::string> getStringIDataName(IDataName);
  if (!getStringIDataName.check())
    throw PyOFException("needed string for data name", PyExc_TypeError);

  std::string UnitClassStr = getStringUnitClass();
  std::string IDataNameStr = getStringIDataName();

  std::list<openfluid::fluidx::InputDataDescriptor>&
      IData = this->m_FXDesc.getDomainDescriptor().getInputData();

  std::list<openfluid::fluidx::InputDataDescriptor>::iterator
    ItIData = IData.begin();

  openfluid::fluidx::InputDataDescriptor::UnitIDInputData_t::iterator
      ItUnitData;

  bool keyExists = TRUE;

  /* searching for unit class */
  while (ItIData != IData.end() && (*ItIData).getUnitsClass() != UnitClassStr)
    ++ItIData;

  /* searching for unit name in the first unit */
  if (ItIData != IData.end() && (*ItIData).getData().size() > 0)
  {
    ItUnitData = (*ItIData).getData().begin();
    keyExists = (*ItUnitData).second.find(IDataNameStr) !=
        (*ItUnitData).second.end();

    if (!keyExists)
    {
      /* for all unit id */
      for (ItUnitData = (*ItIData).getData().begin(); ItUnitData !=
          (*ItIData).getData().end(); ++ItUnitData)
      {
        (*ItUnitData).second.erase((*ItUnitData).second.find(IDataNameStr));
      }
    }
    else
      pyopenfluid::topython::printWarning("input data name doesn't exist");
  }
  else
    pyopenfluid::topython::printWarning("unit class doesn't exist or it doesn't contain any units");
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
  } HANDLE_EXCEPTION

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
  } HANDLE_EXCEPTION

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
    throw PyOFException("DefaultDeltaT cann't be negative or null",
        PyExc_ValueError);
  this->m_FXDesc.getRunDescriptor().setDeltaT(DefaultDeltaTInt);
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getPeriodBeginDate ()
{
  /* 'yyyy-mm-dd hh:mm:ss' */
  openfluid::core::DateTime BrutDate = this->m_FXDesc.getRunDescriptor()
      .getBeginDate();
  std::stringstream StreamRes(std::stringstream::in | std::stringstream::out);
  StreamRes << pyopenfluid::tools::zeroFill(boost::lexical_cast<std::string>(
      BrutDate.getYear()), 1) << "-";
  StreamRes << pyopenfluid::tools::zeroFill(boost::lexical_cast<std::string>(
      BrutDate.getMonth()), 2) << "-";
  StreamRes << pyopenfluid::tools::zeroFill(boost::lexical_cast<std::string>(
      BrutDate.getDay()), 2) << " ";
  StreamRes << pyopenfluid::tools::zeroFill(boost::lexical_cast<std::string>(
      BrutDate.getHour()), 2) << ":";
  StreamRes << pyopenfluid::tools::zeroFill(boost::lexical_cast<std::string>(
      BrutDate.getMinute()), 2) << ":";
  StreamRes << pyopenfluid::tools::zeroFill(boost::lexical_cast<std::string>(
      BrutDate.getSecond()), 2);
  return boost::python::str(StreamRes.str().c_str());
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getPeriodEndDate ()
{
  /* 'yyyy-mm-dd hh:mm:ss' */
  openfluid::core::DateTime BrutDate = this->m_FXDesc.getRunDescriptor()
      .getEndDate();
  std::stringstream StreamRes(std::stringstream::in | std::stringstream::out);
  StreamRes << pyopenfluid::tools::zeroFill(boost::lexical_cast<std::string>(
      BrutDate.getYear()), 1) << "-";
  StreamRes << pyopenfluid::tools::zeroFill(boost::lexical_cast<std::string>(
      BrutDate.getMonth()), 2) << "-";
  StreamRes << pyopenfluid::tools::zeroFill(boost::lexical_cast<std::string>(
      BrutDate.getDay()), 2) << " ";
  StreamRes << pyopenfluid::tools::zeroFill(boost::lexical_cast<std::string>(
      BrutDate.getHour()), 2) << ":";
  StreamRes << pyopenfluid::tools::zeroFill(boost::lexical_cast<std::string>(
      BrutDate.getMinute()), 2) << ":";
  StreamRes << pyopenfluid::tools::zeroFill(boost::lexical_cast<std::string>(
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

  /* 'yyyy-mm-dd hh:mm:ss' */
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
  else
    pyopenfluid::topython::printWarning(
        "begin date isn't formatted with good format");
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::setPeriodEndDate (boost::python::object EDate)
{
  boost::python::extract<std::string> getStringEDate(EDate);
  if (!getStringEDate.check())
    throw PyOFException("needed string", PyExc_TypeError);

  /* 'yyyy-mm-dd hh:mm:ss' */
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
  else
    pyopenfluid::topython::printWarning(
        "end date isn't formatted with good format");
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

    /* instantiation */
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

    /* simulation */
    Engine->initialize();

    Engine->initParams();
    Engine->prepareData();
    Engine->checkConsistency();
    Engine->run();

    Engine->finalize();

    delete Engine;

    return boost::python::object(true);
  } HANDLE_EXCEPTION

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

  /* 'PyOpenFLUID(<<version>>)' */
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
