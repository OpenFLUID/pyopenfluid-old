#include <Python.h>
#include <stdio.h>
#include <boost/python/str.hpp>
#include <boost/python/dict.hpp>
#include <boost/python/list.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/object.hpp>

#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/exception/all.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/optional.hpp>

#include <set>
#include <map>
#include <list>
#include <ctime>
#include <vector>
#include <string>
#include <utility>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <exception>

#include <glibmm/ustring.h>

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
#include <openfluid/fluidx/AdvancedModelDescriptor.hpp>
#include <openfluid/fluidx/AdvancedFluidXDescriptor.hpp>
#include <openfluid/fluidx/AdvancedDomainDescriptor.hpp>
#include <openfluid/fluidx/AdvancedMonitoringDescriptor.hpp>

#include "PyOpenFLUID.hpp"
#include "PyOpenFLUIDError.hpp"
#include "PythonUtilities.hpp"
#include "PyOpenFLUIDConstants.hpp"


// =====================================================================
// =====================================================================


PyOpenFLUID::PyOpenFLUID ()
{
  try
  {
    this->mp_IOL = new openfluid::base::IOListener();
    this->mp_FXDesc = new openfluid::fluidx::FluidXDescriptor(this->mp_IOL);
    this->mp_AdvFXDesc = new openfluid::fluidx::AdvancedFluidXDescriptor(
        *(this->mp_FXDesc));

    openfluid::fluidx::RunDescriptor& runDescp = this->mp_FXDesc->
      getRunDescriptor();

    std::time_t t = time(0);   // get time now
    struct std::tm *Now = localtime( &t );

    runDescp.setDeltaT((unsigned int)60);
    runDescp.setBeginDate(openfluid::core::DateTime(Now->tm_year+1900,\
        Now->tm_mon+1, Now->tm_mday, 0, 0, 0));
    runDescp.setEndDate(openfluid::core::DateTime(Now->tm_year+1900,\
        Now->tm_mon+1, Now->tm_mday, 1, 0, 0));
    runDescp.setFilled(true);
  }
  catch (openfluid::base::OFException& E)
  {
    throw PyOFException(E.what());
  }
  catch (std::bad_alloc& E)
  {
    throw PyOFException(std::string("MEMORY ALLOCATION ERROR, ") \
        + std::string(E.what()) \
        + std::string(". Possibly not enough memory available"), \
        PyExc_MemoryError);
  }
  catch (...)
  {
    throw PyOFException("UNKNOWN EXCEPTION");
  }
}


// =====================================================================
// =====================================================================


PyOpenFLUID::~PyOpenFLUID ()
{
  if (this->mp_IOL != NULL) /* security */
    delete this->mp_IOL;
  if (this->mp_FXDesc != NULL) /* security */
    delete this->mp_FXDesc;
  if (this->mp_AdvFXDesc != NULL) /* security */
    delete this->mp_AdvFXDesc;
}


// =====================================================================
/* ----------------------  GENERAL FUNCTIONS  ----------------------- */


PyObject* PyOpenFLUID::getVersion (PyObject* PyObSelf, PyObject* InTuple,
    PyObject* InDict)
{
  if (PyTuple_Size(InTuple) != 0)
    throw PyOFException("method called with parameters",
        PyExc_TypeError);
  if (PyDict_Size(InDict) != 0)
    throw PyOFException("method called with keywords parameters",
        PyExc_TypeError);

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

  std::map<std::string,std::map<int, openfluid::fluidx::BuilderUnit> >
      MapUnitClassID = this->mp_AdvFXDesc->getDomain().getUnitsByIdByClass();

  std::map<std::string,std::map<int, openfluid::fluidx::BuilderUnit> >::iterator
      ItMapUnitClassID;

  SStream << "Spatial domain is made of " << MapUnitClassID.size()
      << " spatial units" << std::endl;

  for (ItMapUnitClassID = MapUnitClassID.begin();
      ItMapUnitClassID != MapUnitClassID.end(); ++ItMapUnitClassID)
    SStream << " - " << (*ItMapUnitClassID).second.size() << " units of class "
        << (*ItMapUnitClassID).first << std::endl;


  /* Model */
  openfluid::fluidx::GeneratorDescriptor* pGenDesc;

  std::list<openfluid::fluidx::ModelItemDescriptor*> ModelInfos =
      this->mp_AdvFXDesc->getModel().getItems();

  std::list<openfluid::fluidx::ModelItemDescriptor*>::iterator ItModelInfos;

  SStream << "Model is made of "
      << ModelInfos.size()
      << " simulation items" << std::endl;
  for (ItModelInfos = ModelInfos.begin(); ItModelInfos != ModelInfos.end();
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
      this->mp_AdvFXDesc->getRunDescriptor().getBeginDate().getAsISOString().c_str()
      << " to "
      << this->mp_AdvFXDesc->getRunDescriptor().getEndDate().getAsISOString().c_str()
      << std::endl;

  /* Time step */
  SStream << "Simulation time step : "
      << this->mp_AdvFXDesc->getRunDescriptor().getDeltaT() << std::endl;

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

  int PosItem = this->mp_AdvFXDesc->getModel().getFirstItemIndex(FuncIDStr);

  if (PosItem >= 0)
  {
    openfluid::fluidx::ModelItemDescriptor* ItemFound =
        this->mp_AdvFXDesc->getModel().getItemAt(PosItem);

    openfluid::fluidx::FunctionDescriptor* FuncDescp =
        dynamic_cast<openfluid::fluidx::FunctionDescriptor*>(ItemFound);

    if (FuncDescp != NULL)
    {
      boost::optional<std::string> Res =
          FuncDescp->getParameters().get_optional<std::string>(ParamNameStr);

      if (Res)
        return boost::python::str(*Res);
    }
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

  int PosItem = this->mp_AdvFXDesc->getModel().getFirstItemIndex(FuncIDStr);

  if (PosItem >= 0)
  {
    openfluid::fluidx::ModelItemDescriptor* ItemFound =
        this->mp_AdvFXDesc->getModel().getItemAt(PosItem);

    openfluid::fluidx::FunctionDescriptor* FuncDescp =
        dynamic_cast<openfluid::fluidx::FunctionDescriptor*>(ItemFound);

    if (FuncDescp != NULL)
      FuncDescp->setParameter(ParamNameStr,ParamValueStr);
  }
  else
    throw PyOFException("function doesn't exists");
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

  int PosItem = this->mp_AdvFXDesc->getModel().getFirstItemIndex(FuncIDStr);

  if (PosItem >= 0)
  {
    openfluid::fluidx::ModelItemDescriptor* ItemFound =
        this->mp_AdvFXDesc->getModel().getItemAt(PosItem);

    openfluid::fluidx::FunctionDescriptor* FuncDescp =
        dynamic_cast<openfluid::fluidx::FunctionDescriptor*>(ItemFound);

    if (FuncDescp != NULL)
      FuncDescp->eraseParameter(ParamNameStr);
  }
  else
    throw PyOFException("function doesn't exists");
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

  int PosItem = this->mp_AdvFXDesc->getModel().getFirstItemIndex(FuncIDStr);

  if (PosItem >= 0)
  {
    openfluid::fluidx::ModelItemDescriptor* ItemFound =
        this->mp_AdvFXDesc->getModel().getItemAt(PosItem);

    openfluid::fluidx::FunctionDescriptor* FuncDescp =
        dynamic_cast<openfluid::fluidx::FunctionDescriptor*>(ItemFound);

    if (FuncDescp != NULL)
    {
      openfluid::ware::WareParams_t Params = FuncDescp->getParameters();
      openfluid::ware::WareParams_t::iterator ItParam;
      for (ItParam = Params.begin(); ItParam != Params.end(); ++ItParam)
        ListRes.append(boost::python::str((*ItParam).first));
    }
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

  std::list<openfluid::fluidx::ModelItemDescriptor*> ModelInfos =
      this->mp_AdvFXDesc->getModel().getItems();

  std::list<openfluid::fluidx::ModelItemDescriptor*>::iterator
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
  std::list<openfluid::fluidx::ModelItemDescriptor*> ModelInfos =
      this->mp_AdvFXDesc->getModel().getItems();

  std::list<openfluid::fluidx::ModelItemDescriptor*>::iterator
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
    throw PyOFException("generator doesn't exists");
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
  openfluid::ware::WareParams_t Params = this->mp_AdvFXDesc->getModel()
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

  this->mp_AdvFXDesc->getModel().setGlobalParameter(ParamNameStr,ParamValueStr);
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getModelGlobalParams ()
{
  boost::python::list ListRes = boost::python::list();

  openfluid::ware::WareParams_t Params = this->mp_AdvFXDesc->getModel()
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

  this->mp_AdvFXDesc->getModel().eraseGlobalParameter(ParamNameStr);
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getModelItems ()
{
  boost::python::list ListRes = boost::python::list();

  std::list<openfluid::fluidx::ModelItemDescriptor*> ListItem =
      this->mp_AdvFXDesc->getModel().getItems();

  std::list<openfluid::fluidx::ModelItemDescriptor*>::iterator ItListItem;

  openfluid::fluidx::FunctionDescriptor* FuncDescp;
  openfluid::fluidx::GeneratorDescriptor* GenDescp;

  for(ItListItem = ListItem.begin(); ItListItem != ListItem.end(); ++ItListItem)
    if ((*ItListItem)->isType(
          openfluid::fluidx::FunctionDescriptor::PluggedFunction))
    {
      FuncDescp = (openfluid::fluidx::FunctionDescriptor*) *ItListItem;
      ListRes.append(boost::python::object(FuncDescp->getFileID()));
    }
    else if ((*ItListItem)->isType(
          openfluid::fluidx::GeneratorDescriptor::Generator))
    {
      GenDescp = (openfluid::fluidx::GeneratorDescriptor*) *ItListItem;
      ListRes.append(boost::python::object(GenDescp->getGeneratedID()));
    }

  return ListRes;
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::addFunction (boost::python::object FuncID)
{
  boost::python::extract<std::string> getStringFuncID(FuncID);
  if (!getStringFuncID.check())
    throw PyOFException("needed string for function id", PyExc_TypeError);

  std::string FuncIDStr = getStringFuncID();

  try
  {
    openfluid::fluidx::FunctionDescriptor* NewFunction =
        new openfluid::fluidx::FunctionDescriptor(FuncIDStr);

    this->mp_AdvFXDesc->getModel().appendItem(NewFunction);
  } HANDLE_OFEXCEPTION
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::removeFunction (boost::python::object FuncID)
{
  boost::python::extract<std::string> getStringFuncID(FuncID);
  if (!getStringFuncID.check())
    throw PyOFException("needed string for observer id", PyExc_TypeError);

  std::string FuncIDStr = getStringFuncID();

  try
  {
    this->mp_AdvFXDesc->getModel().removeItem(
      this->mp_AdvFXDesc->getModel().getFirstItemIndex(FuncIDStr));
  } HANDLE_OFEXCEPTION
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::clearModel ()
{
  std::list<openfluid::fluidx::ModelItemDescriptor*> Items =
      this->mp_AdvFXDesc->getModel().getItems();

  std::list<openfluid::fluidx::ModelItemDescriptor*>::iterator ItItems;

  try
  {
    for (ItItems = Items.begin(); ItItems != Items.end(); ++ItItems)
      if ((*ItItems)->isType(
          openfluid::fluidx::FunctionDescriptor::PluggedFunction))
        this->mp_AdvFXDesc->getModel().removeItem(
          this->mp_AdvFXDesc->getModel().getFirstItemIndex(*ItItems));
  } HANDLE_OFEXCEPTION
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getFunctionsInModel ()
{
  boost::python::list ListRes = boost::python::list();

  std::list<openfluid::fluidx::ModelItemDescriptor*>
      ItemList = this->mp_AdvFXDesc->getModel().getItems();

  std::list<openfluid::fluidx::ModelItemDescriptor*>::iterator
      ItItemList;

  for (ItItemList = ItemList.begin(); ItItemList != ItemList.end();
      ++ItItemList)
    if ((*ItItemList)->isType(
        openfluid::fluidx::ModelItemDescriptor::PluggedFunction))
      ListRes.append(boost::python::str((
          (openfluid::fluidx::FunctionDescriptor*)(*ItItemList))->getFileID()));

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

  try
  {
    openfluid::fluidx::ObserverDescriptor ObsDesc =
       this->mp_AdvFXDesc->getMonitoring().getDescriptor(ObsIDStr);

    boost::optional<std::string> Res =
        ObsDesc.getParameters().get_optional<std::string>(ParamNameStr);

    if (Res)
      return boost::python::str(*Res);

  } WARNING_OFEXCEPTION

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

  try
  {
    openfluid::fluidx::ObserverDescriptor& ObsDesc =
       this->mp_AdvFXDesc->getMonitoring().getDescriptor(ObsIDStr);

    ObsDesc.setParameter(ParamNameStr, ParamValueStr);

  } HANDLE_OFEXCEPTION
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

  try
  {
    openfluid::fluidx::ObserverDescriptor& ObsDesc =
       this->mp_AdvFXDesc->getMonitoring().getDescriptor(ObsIDStr);

    ObsDesc.eraseParameter(ParamNameStr);

  } HANDLE_OFEXCEPTION
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

  try
  {
    openfluid::fluidx::ObserverDescriptor ObsDesc =
       this->mp_AdvFXDesc->getMonitoring().getDescriptor(ObsIDStr);

    std::map<std::string, std::string> MapInfos = openfluid::fluidx::
        WareDescriptor::getParamsAsMap(ObsDesc.getParameters());

    std::map<std::string, std::string>::iterator ItMapInfos;

    for (ItMapInfos = MapInfos.begin(); ItMapInfos != MapInfos.end();
        ++ItMapInfos)
      ListRes.append(boost::python::str((*ItMapInfos).first));

  } WARNING_OFEXCEPTION

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

  try
  {
    this->mp_AdvFXDesc->getMonitoring().addToObserverList(ObsIDStr);
  } HANDLE_OFEXCEPTION
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::removeObserver (boost::python::object ObsID)
{
  boost::python::extract<std::string> getStringObsID(ObsID);
  if (!getStringObsID.check())
    throw PyOFException("needed string for observer id", PyExc_TypeError);

  std::string ObsIDStr = getStringObsID();

  try
  {
    this->mp_AdvFXDesc->getMonitoring().removeFromObserverList(ObsIDStr);
  } HANDLE_OFEXCEPTION
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::clearMonitoring ()
{
  std::list<openfluid::fluidx::ObserverDescriptor*> EmptyList =
      std::list< openfluid::fluidx::ObserverDescriptor * >();
  this->mp_AdvFXDesc->getMonitoring().setItems(EmptyList);
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getObserversInMonitoring ()
{
  boost::python::list ListRes = boost::python::list();

  std::list<openfluid::fluidx::ObserverDescriptor*>
      ObsList = this->mp_AdvFXDesc->getMonitoring().getItems();

  std::list<openfluid::fluidx::ObserverDescriptor*>::iterator
      ItObsList;

  for (ItObsList = ObsList.begin(); ItObsList != ObsList.end(); ++ItObsList)
    ListRes.append(boost::python::str((*ItObsList)->getID()));

  return ListRes;
}


// =====================================================================
/* -------------------  SPATIAL DOMAIN FUNCTIONS  ------------------- */


boost::python::object PyOpenFLUID::getUnitsClasses ()
{
  boost::python::list ListID = boost::python::list();

  std::set<std::string> SetClass = this->mp_AdvFXDesc->getDomain().
    getClassNames();

  std::set<std::string>::iterator IterClass;

  for(IterClass = SetClass.begin(); IterClass != SetClass.end(); ++IterClass)
    ListID.append(boost::python::object(*IterClass));

  return ListID;
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

  std::set<int> SetID = this->mp_AdvFXDesc->getDomain().
    getIDsOfClass(UnitClassRef);

  std::set<int>::iterator IterID;

  for(IterID = SetID.begin(); IterID != SetID.end(); ++IterID)
    ListID.append(boost::python::object(*IterID));

  return ListID;
}


// =====================================================================
// =====================================================================


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

  /* adds */
  openfluid::fluidx::UnitDescriptor* NewUnitDesp;
  NewUnitDesp = new openfluid::fluidx::UnitDescriptor();
  NewUnitDesp->getUnitClass().assign(UnitClassStr);
  NewUnitDesp->getUnitID() = UnitIDInt;
  NewUnitDesp->getProcessOrder() = PcsOrderInt;

  try
  {
    this->mp_AdvFXDesc->getDomain().addUnit(NewUnitDesp);
  } HANDLE_OFEXCEPTION
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

  try
  {
    this->mp_AdvFXDesc->getDomain().deleteUnit(UnitClassStr, UnitIDInt);
  } HANDLE_OFEXCEPTION
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::clearAllUnits (boost::python::object UnitClass)
{
  if (UnitClass.ptr() == Py_None)
  {
    this->mp_AdvFXDesc->getDomain().clearDomain();
  }
  else
  {
    boost::python::extract<std::string> getStringUnitClass(UnitClass);
    if (!getStringUnitClass.check())
      throw PyOFException("needed string for unit class", PyExc_TypeError);

    std::string UnitClassStr = getStringUnitClass();

    std::set<int> SetID = this->mp_AdvFXDesc->getDomain().
        getIDsOfClass(UnitClassStr);

    std::set<int>::iterator IterID;

    for(IterID = SetID.begin(); IterID != SetID.end(); ++IterID)
      this->mp_AdvFXDesc->getDomain().deleteUnit(UnitClassStr, *IterID);
  }
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::setProcessOrder (boost::python::object UnitClass,
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

  try
  {
    openfluid::fluidx::BuilderUnit Unit =
        this->mp_AdvFXDesc->getDomain().getUnit(UnitClassStr, UnitIDInt);
    Unit.mp_UnitDesc->getProcessOrder() = ProcessOrderInt;
  } HANDLE_OFEXCEPTION
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getProcessOrder (
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

  try
  {
    openfluid::fluidx::BuilderUnit Unit =
        this->mp_AdvFXDesc->getDomain().getUnit(UnitClassStr, UnitIDInt);
    return boost::python::object(Unit.mp_UnitDesc->getProcessOrder());
  } WARNING_OFEXCEPTION

  return boost::python::object(); /* makes Python NONE */
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getUnitTos (
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

  try
  {
    openfluid::core::UnitClassID_t TmpPair = openfluid::core::UnitClassID_t
        (UnitClassStr, UnitIDInt);

    std::list<openfluid::core::UnitClassID_t> ListUnit = this->mp_AdvFXDesc->
        getDomain().getUnitsToOf(TmpPair);

    std::list<openfluid::core::UnitClassID_t>::iterator ItListUnit;

    for(ItListUnit = ListUnit.begin(); ItListUnit != ListUnit.end(); ++ItListUnit)
      ListRes.append(boost::python::make_tuple(
          boost::python::object((*ItListUnit).first),
          boost::python::object((*ItListUnit).second) ));
  } WARNING_OFEXCEPTION

  return ListRes;
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getUnitFroms (
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

  try
  {
    openfluid::core::UnitClassID_t TmpPair = openfluid::core::UnitClassID_t
        (UnitClassStr, UnitIDInt);

    std::list<openfluid::core::UnitClassID_t> ListUnit = this->mp_AdvFXDesc->
        getDomain().getUnitsFromOf(TmpPair);

    std::list<openfluid::core::UnitClassID_t>::iterator ItListUnit;

    for(ItListUnit = ListUnit.begin(); ItListUnit != ListUnit.end(); ++ItListUnit)
      ListRes.append(boost::python::make_tuple(
          boost::python::object((*ItListUnit).first),
          boost::python::object((*ItListUnit).second) ));
  } WARNING_OFEXCEPTION

  return ListRes;
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::addFromToConnection (
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

  openfluid::core::UnitClassID_t FromUnit = openfluid::core::UnitClassID_t
      (UnitClassFromStr, UnitIDFromInt);
  openfluid::core::UnitClassID_t ToUnit = openfluid::core::UnitClassID_t
      (UnitClassToStr, UnitIDToInt);

  try
  {
    this->mp_AdvFXDesc->getDomain().addFromToRelation(
        FromUnit, ToUnit);
  } HANDLE_OFEXCEPTION
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::removeFromToConnection (
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

  openfluid::core::UnitClassID_t FromUnit = openfluid::core::UnitClassID_t
      (UnitClassFromStr, UnitIDFromInt);
  openfluid::core::UnitClassID_t ToUnit = openfluid::core::UnitClassID_t
      (UnitClassToStr, UnitIDToInt);

  try
  {
    this->mp_AdvFXDesc->getDomain().removeFromToRelation(
        FromUnit, ToUnit);
  } HANDLE_OFEXCEPTION
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getUnitChildren (
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

  try
  {
    openfluid::core::UnitClassID_t TmpPair = openfluid::core::UnitClassID_t
        (UnitClassStr, UnitIDInt);

    std::list<openfluid::core::UnitClassID_t> ListUnit = this->mp_AdvFXDesc->
        getDomain().getUnitsChildrenOf(TmpPair);

    std::list<openfluid::core::UnitClassID_t>::iterator ItListUnit;

    for(ItListUnit = ListUnit.begin(); ItListUnit != ListUnit.end(); ++ItListUnit)
      ListRes.append(boost::python::make_tuple(
          boost::python::object((*ItListUnit).first),
          boost::python::object((*ItListUnit).second) ));
  } WARNING_OFEXCEPTION

  return ListRes;
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getUnitParents (
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

  try
  {
    openfluid::core::UnitClassID_t TmpPair = openfluid::core::UnitClassID_t
        (UnitClassStr, UnitIDInt);
    std::list<openfluid::core::UnitClassID_t> ListUnit = this->mp_AdvFXDesc->
        getDomain().getUnitsParentsOf(TmpPair);

    std::list<openfluid::core::UnitClassID_t>::iterator ItListUnit;

    for(ItListUnit = ListUnit.begin(); ItListUnit != ListUnit.end(); ++ItListUnit)
      ListRes.append(boost::python::make_tuple(
          boost::python::object((*ItListUnit).first),
          boost::python::object((*ItListUnit).second) ));
  } WARNING_OFEXCEPTION

  return ListRes;
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::addParentChildConnection (
    boost::python::object UnitClassParent, boost::python::object UnitIDParent,
    boost::python::object UnitClassChild, boost::python::object UnitIDChild)
{
  boost::python::extract<std::string> getStringUnitClassParent(UnitClassParent);
  if (!getStringUnitClassParent.check())
    throw PyOFException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitIDParent(UnitIDParent);
  if (!getIntUnitIDParent.check())
    throw PyOFException("needed integer for unit id", PyExc_TypeError);

  boost::python::extract<std::string> getStringUnitClassChild(UnitClassChild);
  if (!getStringUnitClassChild.check())
    throw PyOFException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitIDChild(UnitIDChild);
  if (!getIntUnitIDChild.check())
    throw PyOFException("needed integer for unit id", PyExc_TypeError);

  std::string UnitClassParentStr = getStringUnitClassParent();
  int UnitIDParentInt = getIntUnitIDParent();

  std::string UnitClassChildStr = getStringUnitClassChild();
  int UnitIDChildInt = getIntUnitIDChild();

  openfluid::core::UnitClassID_t ParentUnit = openfluid::core::UnitClassID_t
      (UnitClassParentStr, UnitIDParentInt);
  openfluid::core::UnitClassID_t ChildUnit = openfluid::core::UnitClassID_t
      (UnitClassChildStr, UnitIDChildInt);

  try
  {
    this->mp_AdvFXDesc->getDomain().addParentChildRelation(
        ParentUnit, ChildUnit);
  } HANDLE_OFEXCEPTION
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::removeParentChildConnection (
    boost::python::object UnitClassParent, boost::python::object UnitIDParent,
    boost::python::object UnitClassChild, boost::python::object UnitIDChild)
{
  boost::python::extract<std::string> getStringUnitClassParent(UnitClassParent);
  if (!getStringUnitClassParent.check())
    throw PyOFException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitIDParent(UnitIDParent);
  if (!getIntUnitIDParent.check())
    throw PyOFException("needed integer for unit id", PyExc_TypeError);

  boost::python::extract<std::string> getStringUnitClassChild(UnitClassChild);
  if (!getStringUnitClassChild.check())
    throw PyOFException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitIDChild(UnitIDChild);
  if (!getIntUnitIDChild.check())
    throw PyOFException("needed integer for unit id", PyExc_TypeError);

  std::string UnitClassParentStr = getStringUnitClassParent();
  int UnitIDParentInt = getIntUnitIDParent();

  std::string UnitClassChildStr = getStringUnitClassChild();
  int UnitIDChildInt = getIntUnitIDChild();

  openfluid::core::UnitClassID_t ParentUnit = openfluid::core::UnitClassID_t
      (UnitClassParentStr, UnitIDParentInt);
  openfluid::core::UnitClassID_t ChildUnit = openfluid::core::UnitClassID_t
      (UnitClassChildStr, UnitIDChildInt);

  try
  {
    this->mp_AdvFXDesc->getDomain().removeParentChildRelation(
        ParentUnit, ChildUnit);
  } HANDLE_OFEXCEPTION
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

  try
  {
    this->mp_AdvFXDesc->getDomain().addInputData(UnitClassStr, IDataNameStr,
        IDataValStr);
  } HANDLE_OFEXCEPTION
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
  int UnitIDInt = getUnitID();
  std::string IDataNameStr = getStringIDataName();

  try
  {
    std::string ResIpDt = this->mp_AdvFXDesc->getDomain().getInputData(
        UnitClassStr, UnitIDInt, IDataNameStr);
    return boost::python::object(ResIpDt);
  } WARNING_OFEXCEPTION

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
  int UnitIDInt = getUnitID();
  std::string IDataNameStr = getStringIDataName();
  std::string IDataValStr = getStringIDataValue();

  try
  {
    std::string& ResIpDt = this->mp_AdvFXDesc->getDomain().getInputData(
        UnitClassStr, UnitIDInt, IDataNameStr);
    ResIpDt.assign(IDataValStr);
  } HANDLE_OFEXCEPTION
}


// =====================================================================
// =====================================================================


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

  try
  {
    this->mp_AdvFXDesc->getDomain().deleteInputData(UnitClassStr, IDataNameStr);
  } HANDLE_OFEXCEPTION
}


// =====================================================================
/* --------------------  INPUT OUTPUT FUNCTIONS  -------------------- */


void PyOpenFLUID::openDataset (boost::python::object Path)
{
  boost::python::extract<std::string> getStringPath(Path);
  if (!getStringPath.check())
    throw PyOFException("needed string for dataset path", PyExc_TypeError);

  std::string StrPath = getStringPath();

  try
  {
    openfluid::base::Init();

    if (this->mp_IOL != NULL) /* security */
      delete this->mp_IOL;
    this->mp_IOL = new openfluid::base::IOListener();

    openfluid::base::RuntimeEnvironment::getInstance()->
        setInputDir(std::string(StrPath));
    this->mp_FXDesc->loadFromDirectory(openfluid::base::RuntimeEnvironment::
        getInstance()->getInputDir());

    if (this->mp_AdvFXDesc != NULL) /* security */
      delete this->mp_AdvFXDesc;
    this->mp_AdvFXDesc = new openfluid::fluidx::AdvancedFluidXDescriptor(
        *(this->mp_FXDesc));

  } HANDLE_EXCEPTION
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::saveDataset (boost::python::object Path)
{
  boost::python::extract<std::string> getStringPath(Path);
  if (!getStringPath.check())
    throw PyOFException("needed string for dataset path", PyExc_TypeError);

  std::string StrPath = getStringPath();

  try
  {
    if (!boost::filesystem::exists(StrPath))
    {
      boost::filesystem::create_directory(StrPath);
      if (!boost::filesystem::exists(StrPath))
        throw PyOFException("error creating dataset directory");
    }

    openfluid::fluidx::RunDescriptor& RunDescp =
        this->mp_FXDesc->getRunDescriptor();
    RunDescp.setFilled(true);
    this->mp_FXDesc->writeToManyFiles(StrPath);
  } HANDLE_EXCEPTION
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::openProject (boost::python::object Path)
{
  boost::python::extract<std::string> getStringPath(Path);
  if (!getStringPath.check())
    throw PyOFException("needed string for project path", PyExc_TypeError);

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

    this->openDataset(BoostPath);
  } HANDLE_EXCEPTION
}


// =====================================================================
// =====================================================================


PyObject* PyOpenFLUID::saveProject (PyObject* PyObSelf, PyObject* InTuple,
    PyObject* InDict)
//void PyOpenFLUID::saveProject (boost::python::object Path)
{
  char* Keywords[5];
  Keywords[0] = (char*) "path";
  Keywords[1] = (char*) "name";
  Keywords[2] = (char*) "description";
  Keywords[3] = (char*) "authors";
  Keywords[4] = NULL;
  char* CharPath = NULL;
  char* CharName = NULL;
  char* CharDescp = NULL;
  char* CharAuth = NULL;
  if (!PyArg_ParseTupleAndKeywords(InTuple, InDict, "s|sss", Keywords,\
      &CharPath, &CharName, &CharDescp, &CharAuth))
  {
    if (CharPath == NULL)
      throw PyOFException("project output path not given");
    throw PyOFException("error getting parameters");
  }

  Glib::ustring GUProjectPath = Glib::ustring(CharPath);

  std::string StrProjectPath = boost::filesystem::path(CharPath).string();

  openfluid::base::ProjectManager* ProjectManager =
      openfluid::base::ProjectManager::getInstance();

  try
  {
    /* directories */
    if (!boost::filesystem::exists(StrProjectPath))
    {
      boost::filesystem::create_directory(StrProjectPath);
      if (!boost::filesystem::exists(StrProjectPath))
        throw PyOFException("error creating project directory");
    }

    /* project */
    /* if exists */
    if (ProjectManager->isProject(GUProjectPath))
    {
      if(!ProjectManager->open(GUProjectPath))
        throw PyOFException("ProjectManager::open, error opening project");

      if (CharName != NULL)
      {
        Glib::ustring GUTmpName = Glib::ustring(CharName);
        ProjectManager->setName(GUTmpName);
      }
      if (CharDescp != NULL)
      {
        Glib::ustring GUTmpDescp = Glib::ustring(CharDescp);
        ProjectManager->setDescription(GUTmpDescp);
      }
      if (CharAuth != NULL)
      {
        Glib::ustring GUTmpAuthors = Glib::ustring(CharAuth);
        ProjectManager->setAuthors(GUTmpAuthors);
      }

      if (!ProjectManager->save())
        throw PyOFException("ProjectManager::save, error saving project");
    }
    /* if creates */
    else
    {
      Glib::ustring GUTmpName;
      if (CharName != NULL)
        GUTmpName = Glib::ustring(CharName);
      else
        GUTmpName = Glib::ustring("");

      Glib::ustring GUTmpDescp;
      if (CharDescp != NULL)
        GUTmpDescp = Glib::ustring(CharDescp);
      else
        GUTmpDescp = Glib::ustring("");

      Glib::ustring GUTmpAuthors;
      if (CharAuth != NULL)
        GUTmpAuthors = Glib::ustring(CharAuth);
      else
        GUTmpAuthors = Glib::ustring("");

      if (!ProjectManager->
          create(GUProjectPath, GUTmpName, GUTmpDescp, GUTmpAuthors, true))
        throw PyOFException("ProjectManager::create, error creating\
 and saving project");
    }

    std::string InputDir = ProjectManager->getInputDir().raw();
    std::string OuputDir = ProjectManager->getOutputDir().raw();

    /* dataset */
    this->mp_FXDesc->writeToManyFiles(InputDir);

    ProjectManager->close();

  } HANDLE_EXCEPTION

  /* return */
  Py_INCREF(Py_None);
  return Py_None;
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::setCurrentOutputDir (boost::python::object Path)
{
  boost::python::extract<std::string> getStringPath(Path);
  if (!getStringPath.check())
    throw PyOFException("needed string for output path", PyExc_TypeError);

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
  return boost::python::object(this->mp_AdvFXDesc->getRunDescriptor()
      .getDeltaT());
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::setDefaultDeltaT (boost::python::object DefaultDeltaT)
{
  boost::python::extract<int> getDefaultDeltaT(DefaultDeltaT);
  if (!getDefaultDeltaT.check())
    throw PyOFException("needed integer for default delta t", PyExc_TypeError);

  const int DefaultDeltaTInt = getDefaultDeltaT();
  if (DefaultDeltaTInt <= 0)
    throw PyOFException("default delta t can't be negative or null",
        PyExc_ValueError);
  this->mp_AdvFXDesc->getRunDescriptor().setDeltaT(DefaultDeltaTInt);
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getPeriodBeginDate ()
{
  /* 'yyyy-mm-dd hh:mm:ss' */
  openfluid::core::DateTime BrutDate = this->mp_AdvFXDesc->getRunDescriptor()
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
  openfluid::core::DateTime BrutDate = this->mp_AdvFXDesc->getRunDescriptor()
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
    throw PyOFException("needed string for period begin date", PyExc_TypeError);

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
  this->mp_AdvFXDesc->getRunDescriptor().setBeginDate(BDate);
  }
  else
    throw PyOFException("begin date isn't formatted with good format",
        PyExc_ValueError);
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::setPeriodEndDate (boost::python::object EDate)
{
  boost::python::extract<std::string> getStringEDate(EDate);
  if (!getStringEDate.check())
    throw PyOFException("needed string for period end date", PyExc_TypeError);

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
  this->mp_AdvFXDesc->getRunDescriptor().setEndDate(BDate);
  }
  else
    throw PyOFException("end date isn't formatted with good format",
        PyExc_ValueError);
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::runProject (boost::python::object Path)
{
  this->openProject(Path);
  this->runSimulation();
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::runSimulation ()
{
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
    openfluid::machine::MachineListener* MachineListen =
        new openfluid::machine::MachineListener();

    /* instantiation */
    openfluid::machine::ModelInstance Model(SBlob,MachineListen);
    openfluid::machine::MonitoringInstance Monitoring(SBlob);

    openfluid::machine::Factory::buildSimulationBlobFromDescriptors(
        *(this->mp_FXDesc),SBlob);

    openfluid::machine::Factory::buildModelInstanceFromDescriptor(
        this->mp_FXDesc->getModelDescriptor(), Model);

    openfluid::machine::Factory::buildMonitoringInstanceFromDescriptor(
        this->mp_FXDesc->getMonitoringDescriptor(), Monitoring);

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

//  for (DescIt = this->mp_FXDesc->getMonitoringDescriptor().getFileSets().begin();
//       DescIt != this->mp_FXDesc->getMonitoringDescriptor().getFileSets().end();
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

  /* 'PyOpenFLUID(<<version pyof>>)' */
  SStream << "PyOpenFLUID(" << PYOPENFLUID_VERSION << ")";

  return boost::python::object(SStream.str());
}
