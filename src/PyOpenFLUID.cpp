/* boost.python */
#include <boost/python/str.hpp>
#include <boost/python/dict.hpp>
#include <boost/python/list.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/object.hpp>
/* boost */
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/exception/all.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/optional.hpp>
/* standard library c++ */
#include <set>
#include <map>
#include <list>
#include <ctime>
#include <vector>
#include <string>
#include <utility>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <exception>
/* glibmm */
#include <glibmm/ustring.h>
/* openfluid */
#include <openfluid/config.hpp>
/* openfluid base */
#include <openfluid/base/Init.hpp>
#include <openfluid/base/IOListener.hpp>
#include <openfluid/base/RuntimeEnv.hpp>
#include <openfluid/base/ApplicationException.hpp>
#include <openfluid/base/ProjectManager.hpp>
/* openfluid core */
#include <openfluid/core/TypeDefs.hpp>
#include <openfluid/core/DateTime.hpp>
#include <openfluid/core/StringValue.hpp>
/* openfluid ware */
#include <openfluid/ware/PluggableWare.hpp>
/* openfluid machine */
#include <openfluid/machine/Engine.hpp>
#include <openfluid/machine/Factory.hpp>
#include <openfluid/machine/ModelInstance.hpp>
#include <openfluid/machine/SimulationBlob.hpp>
#include <openfluid/machine/MachineListener.hpp>
#include <openfluid/machine/MonitoringInstance.hpp>
#include <openfluid/machine/SimulatorPluginsManager.hpp>
#include <openfluid/machine/ObserverPluginsManager.hpp>
/* openfluid fluidx */
#include <openfluid/fluidx/RunDescriptor.hpp>
#include <openfluid/fluidx/WareDescriptor.hpp>
#include <openfluid/fluidx/UnitDescriptor.hpp>
#include <openfluid/fluidx/AttributesDescriptor.hpp>
#include <openfluid/fluidx/FluidXDescriptor.hpp>
#include <openfluid/fluidx/DomainDescriptor.hpp>
#include <openfluid/fluidx/SimulatorDescriptor.hpp>
#include <openfluid/fluidx/ObserverDescriptor.hpp>
#include <openfluid/fluidx/GeneratorDescriptor.hpp>
#include <openfluid/fluidx/DatastoreDescriptor.hpp>
#include <openfluid/fluidx/MonitoringDescriptor.hpp>
#include <openfluid/fluidx/CoupledModelDescriptor.hpp>
#include <openfluid/fluidx/AdvancedModelDescriptor.hpp>
#include <openfluid/fluidx/AdvancedFluidXDescriptor.hpp>
#include <openfluid/fluidx/AdvancedDomainDescriptor.hpp>
#include <openfluid/fluidx/AdvancedMonitoringDescriptor.hpp>
/* pyopenfluid */
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
    /* basics */
    this->mp_IOL = new openfluid::base::IOListener();
    this->mp_FXDesc = new openfluid::fluidx::FluidXDescriptor(this->mp_IOL);
    this->mp_AdvFXDesc = new openfluid::fluidx::AdvancedFluidXDescriptor(
        *(this->mp_FXDesc));

    this->initWithoutDescriptor();
    this->initFluidxDescriptor();
    this->initAdvancedFluidxDescriptor();
  }
  catch (openfluid::base::ApplicationException& E)
  {
    throw PyApplicationException(E.what());
  }
  catch (std::bad_alloc& E)
  {
    throw PyApplicationException(std::string("MEMORY ALLOCATION ERROR, ") \
        + std::string(E.what()) \
        + std::string(". Possibly not enough memory available"), \
        PyExc_MemoryError);
  }
  catch (...)
  {
    throw PyApplicationException("UNKNOWN EXCEPTION");
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
    throw PyApplicationException("method called with parameters",
        PyExc_TypeError);
  if (PyDict_Size(InDict) != 0)
    throw PyApplicationException("method called with keywords parameters",
        PyExc_TypeError);

  return PyString_FromString((const char*)
      openfluid::config::FULL_VERSION.c_str());
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::addExtraSimulatorsPaths (boost::python::object Paths)
{
  boost::python::extract<std::string> getStringPaths(Paths);
  if (!getStringPaths.check())
    throw PyApplicationException("needed string for extra simulators paths",
        PyExc_TypeError);

  openfluid::base::RuntimeEnvironment::getInstance()->
    addExtraSimulatorsPluginsPaths(getStringPaths());
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::resetExtraSimulatorsPaths ()
{
  openfluid::base::RuntimeEnvironment::getInstance()->
    resetExtraSimulatorsPluginsPaths();
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getExtraSimulatorsPaths ()
{
  std::vector<std::string> VectPath = openfluid::base::RuntimeEnvironment
      ::getInstance()->getExtraSimulatorsPluginsPaths();

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
    throw PyApplicationException("needed string for extra observers paths",
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


/* same prompt as ROpenFLUID 1.7.2 */
void PyOpenFLUID::printSimulationInfo ()
{
  /* output stream */
  std::stringstream SStream(std::stringstream::in | std::stringstream::out);

  /* Spatial domain */
  openfluid::core::UnitClass_t ClassName;

  std::map<std::string,std::map<int, openfluid::fluidx::AdvancedUnitDescriptor> >
      MapUnitClassID = this->mp_AdvFXDesc->getDomain().getUnitsByIdByClass();

  std::map<std::string,std::map<int, openfluid::fluidx::AdvancedUnitDescriptor> >
      ::iterator ItMapUnitClassID;

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
        openfluid::fluidx::ModelItemDescriptor::PluggedSimulator))
    {
      SStream << ((openfluid::fluidx::SimulatorDescriptor*)(*ItModelInfos))->
          getFileID().c_str() << " simulation simulator" << std::endl;
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
      this->mp_AdvFXDesc->getRunDescriptor().getBeginDate().
          getAsISOString().c_str()
      << " to "
      << this->mp_AdvFXDesc->getRunDescriptor().getEndDate().
          getAsISOString().c_str()
      << std::endl;

  /* Time step */
  SStream << "Simulation time step : "
      << this->mp_AdvFXDesc->getRunDescriptor().getDeltaT() << std::endl;

  /* Printing */
  pyopenfluid::topython::printStdOut(SStream);
}


// =====================================================================
/* ------------------------  MODEL FUNCTIONS  ----------------------- */


boost::python::object PyOpenFLUID::getSimulatorParam (
    boost::python::object SimID, boost::python::object ParamName)
{
  boost::python::extract<std::string> getStringSimID(SimID);
  if (!getStringSimID.check())
    throw PyApplicationException("needed string for simulator id", PyExc_TypeError);
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyApplicationException("needed string for parameter name", PyExc_TypeError);

  std::string SimIDStr = getStringSimID();
  std::string ParamNameStr = getStringParamName();

  int PosItem = this->mp_AdvFXDesc->getModel().getFirstItemIndex(SimIDStr);

  /* if exists */
  if (PosItem >= 0)
  {
    openfluid::fluidx::ModelItemDescriptor* ItemFound =
        this->mp_AdvFXDesc->getModel().getItemAt(PosItem);

    openfluid::fluidx::SimulatorDescriptor* SimDescp =
        dynamic_cast<openfluid::fluidx::SimulatorDescriptor*>(ItemFound);

    if (SimDescp != NULL)
    {
      openfluid::ware::WareParams_t Params = SimDescp->getParameters();

      openfluid::ware::WareParams_t::iterator ItParam = Params.find(ParamNameStr);

      if (ItParam != Params.end())
        return boost::python::str(std::string(ItParam->second.get()));
    }
  }

  return boost::python::object(); /* makes Python NONE */
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::setSimulatorParam (boost::python::object SimID,
                                    boost::python::object ParamName,
                                    boost::python::object ParamValue)
{
  boost::python::extract<std::string> getStringSimID(SimID);
  if (!getStringSimID.check())
    throw PyApplicationException("needed string for simulator id", PyExc_TypeError);
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyApplicationException("needed string for parameter name", PyExc_TypeError);
  boost::python::extract<std::string> getStringParamValue(ParamValue);
  if (!getStringParamValue.check())
    throw PyApplicationException("needed string for parameter value", PyExc_TypeError);

  std::string SimIDStr = getStringSimID();
  std::string ParamNameStr = getStringParamName();
  std::string ParamValueStr = getStringParamValue();

  int PosItem = this->mp_AdvFXDesc->getModel().getFirstItemIndex(SimIDStr);

  /* if exists */
  if (PosItem >= 0)
  {
    openfluid::fluidx::ModelItemDescriptor* ItemFound =
        this->mp_AdvFXDesc->getModel().getItemAt(PosItem);

    openfluid::fluidx::SimulatorDescriptor* SimDescp =
        dynamic_cast<openfluid::fluidx::SimulatorDescriptor*>(ItemFound);

    if (SimDescp != NULL)
    {
      openfluid::ware::WareParams_t PairParam;
      PairParam[ParamNameStr] = openfluid::core::StringValue(ParamValueStr);

      SimDescp->setParameters(PairParam);
    }
  }
  else
    throw PyApplicationException("simulator doesn't exists");
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::removeSimulatorParam (boost::python::object SimID,
                                       boost::python::object ParamName)
{
  boost::python::extract<std::string> getStringSimID(SimID);
  if (!getStringSimID.check())
    throw PyApplicationException("needed string for simulator id", PyExc_TypeError);
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyApplicationException("needed string for parameter name", PyExc_TypeError);

  std::string SimIDStr = getStringSimID();
  std::string ParamNameStr = getStringParamName();

  int PosItem = this->mp_AdvFXDesc->getModel().getFirstItemIndex(SimIDStr);

  /* if exists */
  if (PosItem >= 0)
  {
    openfluid::fluidx::ModelItemDescriptor* ItemFound =
        this->mp_AdvFXDesc->getModel().getItemAt(PosItem);

    openfluid::fluidx::SimulatorDescriptor* SimDescp =
        dynamic_cast<openfluid::fluidx::SimulatorDescriptor*>(ItemFound);

    if (SimDescp != NULL)
      SimDescp->eraseParameter(ParamNameStr);
  }
  else
    throw PyApplicationException("simulator doesn't exists");
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getSimulatorParams(
    boost::python::object SimID)
{
  boost::python::extract<std::string> getStringSimID(SimID);
  if (!getStringSimID.check())
    throw PyApplicationException("needed string for simulator id", PyExc_TypeError);

  std::string SimIDStr = getStringSimID();

  boost::python::list ListRes = boost::python::list();

  int PosItem = this->mp_AdvFXDesc->getModel().getFirstItemIndex(SimIDStr);

  /* if exists */
  if (PosItem >= 0)
  {
    openfluid::fluidx::ModelItemDescriptor* ItemFound =
        this->mp_AdvFXDesc->getModel().getItemAt(PosItem);

    openfluid::fluidx::SimulatorDescriptor* SimDescp =
        dynamic_cast<openfluid::fluidx::SimulatorDescriptor*>(ItemFound);

    if (SimDescp != NULL)
    {
      openfluid::ware::WareParams_t Params = SimDescp->getParameters();

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
    throw PyApplicationException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<std::string> getStringVarName(VarName);
  if (!getStringVarName.check())
    throw PyApplicationException("needed string for variable name", PyExc_TypeError);
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyApplicationException("needed string for parameter name", PyExc_TypeError);

  std::string UnitClassStr = getStringUnitClass();
  std::string VarNameStr = getStringVarName();
  std::string ParamNameStr = getStringParamName();

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
    openfluid::ware::WareParams_t Params = GenDescp->getParameters();

    openfluid::ware::WareParams_t::iterator ItParam = Params.find(ParamNameStr);

    if (ItParam != Params.end())
      return boost::python::str(std::string(ItParam->second.get()));
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
    throw PyApplicationException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<std::string> getStringVarName(VarName);
  if (!getStringVarName.check())
    throw PyApplicationException("needed string for variable name", PyExc_TypeError);
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyApplicationException("needed string for parameter name", PyExc_TypeError);
  boost::python::extract<std::string> getStringParamValue(ParamValue);
  if (!getStringParamValue.check())
    throw PyApplicationException("needed string for parameter value", PyExc_TypeError);

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
  {
    openfluid::ware::WareParams_t PairParam;
    PairParam[ParamNameStr] = openfluid::core::StringValue(ParamValueStr);

    GenDescp->setParameters(PairParam);
  }
  else
    throw PyApplicationException("generator doesn't exists");
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getModelGlobalParam (
    boost::python::object ParamName)
{
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyApplicationException("needed string for parameter name", PyExc_TypeError);

  std::string ParamNameStr = getStringParamName();

  /* looking for position of the parameter */
  openfluid::ware::WareParams_t Params = this->mp_AdvFXDesc->getModel()
      .getGlobalParameters();

  openfluid::ware::WareParams_t::iterator ItParam = Params.begin();

  while (ItParam != Params.end() && (*ItParam).first != ParamNameStr)
    ++ItParam;

  /* if found */
  if (ItParam != Params.end())
    return boost::python::str(std::string(ItParam->second.get()));

  return boost::python::object(); /* makes Python NONE */
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::setModelGlobalParam (boost::python::object ParamName,
                                       boost::python::object ParamValue)
{
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyApplicationException("needed string for parameter name", PyExc_TypeError);
  boost::python::extract<std::string> getStringParamValue(ParamValue);
  if (!getStringParamValue.check())
    throw PyApplicationException("needed string for parameter value", PyExc_TypeError);

  openfluid::ware::WareParamKey_t ParamNameStr =
      (openfluid::ware::WareParamKey_t) getStringParamName();
  openfluid::ware::WareParamValue_t ParamValueStr =
      (openfluid::ware::WareParamValue_t) getStringParamValue();

  this->mp_AdvFXDesc->getModel().
      setGlobalParameter(ParamNameStr,ParamValueStr);
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
    throw PyApplicationException("needed string for parameter name", PyExc_TypeError);

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

  openfluid::fluidx::SimulatorDescriptor* SimDescp;
  openfluid::fluidx::GeneratorDescriptor* GenDescp;

  for(ItListItem = ListItem.begin(); ItListItem != ListItem.end();
      ++ItListItem)
    if ((*ItListItem)->isType(
          openfluid::fluidx::SimulatorDescriptor::PluggedSimulator))
    {
      SimDescp = (openfluid::fluidx::SimulatorDescriptor*) *ItListItem;
      ListRes.append(boost::python::object(SimDescp->getFileID()));
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


void PyOpenFLUID::addSimulator (boost::python::object SimID)
{
  boost::python::extract<std::string> getStringSimID(SimID);
  if (!getStringSimID.check())
    throw PyApplicationException("needed string for simulator id", PyExc_TypeError);

  std::string SimIDStr = getStringSimID();

  try
  {
    openfluid::fluidx::SimulatorDescriptor* NewSimulator =
        new openfluid::fluidx::SimulatorDescriptor(SimIDStr);

    this->mp_AdvFXDesc->getModel().appendItem(NewSimulator);
  } HANDLE_APPLICATIONEXCEPTION
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::removeSimulator (boost::python::object SimID)
{
  boost::python::extract<std::string> getStringSimID(SimID);
  if (!getStringSimID.check())
    throw PyApplicationException("needed string for observer id", PyExc_TypeError);

  std::string SimIDStr = getStringSimID();

  try
  {
    this->mp_AdvFXDesc->getModel().removeItem(
      this->mp_AdvFXDesc->getModel().getFirstItemIndex(SimIDStr));
  } HANDLE_APPLICATIONEXCEPTION
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
    openfluid::fluidx::AdvancedModelDescriptor& ModelDescp = 
        this->mp_AdvFXDesc->getModel();

    for (ItItems = Items.begin(); ItItems != Items.end(); ++ItItems)
      if ((*ItItems)->isType(
          openfluid::fluidx::SimulatorDescriptor::PluggedSimulator))
        ModelDescp.removeItem(ModelDescp.getFirstItemIndex(*ItItems));
  } HANDLE_APPLICATIONEXCEPTION
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getSimulatorsInModel ()
{
  boost::python::list ListRes = boost::python::list();

  std::list<openfluid::fluidx::ModelItemDescriptor*>
      ItemList = this->mp_AdvFXDesc->getModel().getItems();

  std::list<openfluid::fluidx::ModelItemDescriptor*>::iterator
      ItItemList;

  for (ItItemList = ItemList.begin(); ItItemList != ItemList.end();
      ++ItItemList)
    if ((*ItItemList)->isType(
        openfluid::fluidx::ModelItemDescriptor::PluggedSimulator))
      ListRes.append(boost::python::str(
          ((openfluid::fluidx::SimulatorDescriptor*)(*ItItemList))->
          getFileID()));

  return ListRes;
}


// =====================================================================
/* ---------------------  MONITORING FUNCTIONS  --------------------- */


boost::python::object PyOpenFLUID::getObserverParam (
    boost::python::object ObsID, boost::python::object ParamName)
{
  boost::python::extract<std::string> getStringObsID(ObsID);
  if (!getStringObsID.check())
    throw PyApplicationException("needed string for observer id", PyExc_TypeError);
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyApplicationException("needed string for parameter name", PyExc_TypeError);

  std::string ObsIDStr = getStringObsID();
  std::string ParamNameStr = getStringParamName();

  try
  {
    openfluid::fluidx::ObserverDescriptor ObsDesc =
       this->mp_AdvFXDesc->getMonitoring().getDescriptor(ObsIDStr);

    openfluid::ware::WareParams_t Params = ObsDesc.getParameters();

    openfluid::ware::WareParams_t::iterator ItParam = Params.find(ParamNameStr);

    if (ItParam != Params.end())
      return boost::python::str(std::string((*ItParam).second.get()));

  } WARNING_EXCEPTION

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
    throw PyApplicationException("needed string for observer id", PyExc_TypeError);
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyApplicationException("needed string for parameter name", PyExc_TypeError);
  boost::python::extract<std::string> getStringParamValue(ParamValue);
  if (!getStringParamValue.check())
    throw PyApplicationException("needed string for parameter value", PyExc_TypeError);

  std::string ObsIDStr = getStringObsID();
  std::string ParamNameStr = getStringParamName();
  std::string ParamValueStr = getStringParamValue();

  try
  {
    openfluid::fluidx::ObserverDescriptor& ObsDesc =
       this->mp_AdvFXDesc->getMonitoring().getDescriptor(ObsIDStr);

    openfluid::ware::WareParams_t PairParam;
    PairParam[ParamNameStr] = openfluid::core::StringValue(ParamValueStr);

    ObsDesc.setParameters(PairParam);

  } HANDLE_APPLICATIONEXCEPTION
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::removeObserverParam (boost::python::object ObsID,
                                       boost::python::object ParamName)
{
  boost::python::extract<std::string> getStringObsID(ObsID);
  if (!getStringObsID.check())
    throw PyApplicationException("needed string for observer id", PyExc_TypeError);
  boost::python::extract<std::string> getStringParamName(ParamName);
  if (!getStringParamName.check())
    throw PyApplicationException("needed string for parameter name", PyExc_TypeError);

  std::string ObsIDStr = getStringObsID();
  std::string ParamNameStr = getStringParamName();

  try
  {
    openfluid::fluidx::ObserverDescriptor& ObsDesc =
       this->mp_AdvFXDesc->getMonitoring().getDescriptor(ObsIDStr);

    ObsDesc.eraseParameter(ParamNameStr);

  } HANDLE_APPLICATIONEXCEPTION
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getObserverParams (
    boost::python::object ObsID)
{
  boost::python::extract<std::string> getStringObsID(ObsID);
  if (!getStringObsID.check())
    throw PyApplicationException("needed string for observer id", PyExc_TypeError);

  std::string ObsIDStr = getStringObsID();

  boost::python::list ListRes = boost::python::list();

  try
  {
    openfluid::fluidx::ObserverDescriptor ObsDesc =
       this->mp_AdvFXDesc->getMonitoring().getDescriptor(ObsIDStr);

    openfluid::ware::WareParams_t MapInfos = ObsDesc.getParameters();

    openfluid::ware::WareParams_t::iterator ItMapInfos;

    for (ItMapInfos = MapInfos.begin(); ItMapInfos != MapInfos.end();
        ++ItMapInfos)
      ListRes.append(boost::python::str((*ItMapInfos).first));

  } WARNING_EXCEPTION

  return ListRes;
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::addObserver (boost::python::object ObsID)
{
  boost::python::extract<std::string> getStringObsID(ObsID);
  if (!getStringObsID.check())
    throw PyApplicationException("needed string for observer id", PyExc_TypeError);

  std::string ObsIDStr = getStringObsID();

  try
  {
    this->mp_AdvFXDesc->getMonitoring().addToObserverList(ObsIDStr);
  } HANDLE_APPLICATIONEXCEPTION
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::removeObserver (boost::python::object ObsID)
{
  boost::python::extract<std::string> getStringObsID(ObsID);
  if (!getStringObsID.check())
    throw PyApplicationException("needed string for observer id", PyExc_TypeError);

  std::string ObsIDStr = getStringObsID();

  try
  {
    this->mp_AdvFXDesc->getMonitoring().removeFromObserverList(ObsIDStr);
  } HANDLE_APPLICATIONEXCEPTION
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::clearMonitoring ()
{
  std::list<openfluid::fluidx::ObserverDescriptor*> EmptyList =
      std::list< openfluid::fluidx::ObserverDescriptor*>();
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
// =====================================================================


boost::python::object PyOpenFLUID::addCSVOutput (
    boost::python::object UnitClass, boost::python::object Vars,
    boost::python::object ListID)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyApplicationException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<std::string> getStringVars(Vars);
  if (!getStringVars.check())
    throw PyApplicationException("needed string for vars", PyExc_TypeError);
  boost::python::extract<std::string> getStringIDs(ListID);
  if (!getStringIDs.check())
    throw PyApplicationException("needed string for ids", PyExc_TypeError);

  /* temp stream for making keys */
  std::stringstream Stream(std::stringstream::in | std::stringstream::out);

  /* pyof<n> */
  Stream << "pyof" << this->m_LastObsID;
  this->m_LastObsID++;
  std::string ObsIDStr;
  Stream.flush();
  Stream >> ObsIDStr;

  /* begin of keys 'set.<obs>' */
  Stream.clear(); Stream.str("");
  Stream << "set.";
  Stream << ObsIDStr;
  Stream.flush();

  /* unit class */
  std::string ObsUnitClassStr = Stream.str() + std::string(".unitclass");

  /* unit id */
  std::string ObsIDsStr = Stream.str() + std::string(".unitsIDs");

  /* vars */
  std::string ObsVarsStr = Stream.str() + std::string(".vars");

  /* format */
  std::string ObsFormatStr = Stream.str() + std::string(".format");

  /* add */
  try
  {
    /* add format if doesn't exists */
    std::string ObsID = std::string("export.vars.files.csv");
    try /* if doesn't exists */
    {
      this->mp_AdvFXDesc->getMonitoring().getDescriptor(ObsID);
    }
    catch (openfluid::base::ApplicationException& E)
    {
      this->mp_AdvFXDesc->getMonitoring().addToObserverList(ObsID);
    }

    openfluid::fluidx::ObserverDescriptor& Observer =
        this->mp_AdvFXDesc->getMonitoring().getDescriptor(ObsID);
    setPyOFCSVFormat(Observer);

    openfluid::ware::WareParams_t PairParam;
    PairParam[ObsUnitClassStr] = openfluid::core::StringValue(getStringUnitClass());
    PairParam[ObsIDsStr] = openfluid::core::StringValue(getStringIDs());
    PairParam[ObsVarsStr] = openfluid::core::StringValue(getStringVars());
    PairParam[ObsFormatStr] = openfluid::core::StringValue(std::string("pyofformat"));

    Observer.setParameters(PairParam);
  } HANDLE_APPLICATIONEXCEPTION

  return boost::python::str(ObsIDStr);
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
    throw PyApplicationException("needed string for unit class", PyExc_TypeError);

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
    throw PyApplicationException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitID(UnitID);
  if (!getIntUnitID.check())
    throw PyApplicationException("needed integer for unit id", PyExc_TypeError);
  boost::python::extract<int> getIntProcessOrder(PcsOrder);
  if (!getIntProcessOrder.check())
    throw PyApplicationException("needed integer for process order", PyExc_TypeError);

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
  } HANDLE_APPLICATIONEXCEPTION
}

// =====================================================================
// =====================================================================


void PyOpenFLUID::removeUnit (boost::python::object UnitClass,
                              boost::python::object UnitID)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyApplicationException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitID(UnitID);
  if (!getIntUnitID.check())
    throw PyApplicationException("needed integer for unit id", PyExc_TypeError);

  std::string UnitClassStr = getStringUnitClass();
  int UnitIDInt = getIntUnitID();

  try
  {
    this->mp_AdvFXDesc->getDomain().deleteUnit(UnitClassStr, UnitIDInt);
  } HANDLE_APPLICATIONEXCEPTION
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::clearAllUnits (boost::python::object UnitClass)
{
  /* if python None */
  if (UnitClass.ptr() == Py_None)
  {
    this->mp_AdvFXDesc->getDomain().clearDomain();
  }
  else
  {
    boost::python::extract<std::string> getStringUnitClass(UnitClass);
    if (!getStringUnitClass.check())
      throw PyApplicationException("needed string for unit class", PyExc_TypeError);

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
    throw PyApplicationException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitID(UnitID);
  if (!getIntUnitID.check())
    throw PyApplicationException("needed integer for unit id", PyExc_TypeError);
  boost::python::extract<int> getIntProcessOrder(PcsOrder);
  if (!getIntProcessOrder.check())
    throw PyApplicationException("needed integer for process order", PyExc_TypeError);

  std::string UnitClassStr = getStringUnitClass();
  int UnitIDInt = getIntUnitID();
  int ProcessOrderInt = getIntProcessOrder();

  try
  {
    openfluid::fluidx::AdvancedUnitDescriptor Unit =
        this->mp_AdvFXDesc->getDomain().getUnit(UnitClassStr, UnitIDInt);
    Unit.UnitDescriptor->getProcessOrder() = ProcessOrderInt;
  } HANDLE_APPLICATIONEXCEPTION
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getProcessOrder (
    boost::python::object UnitClass, boost::python::object UnitID)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyApplicationException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitID(UnitID);
  if (!getIntUnitID.check())
    throw PyApplicationException("needed integer for unit id", PyExc_TypeError);

  std::string UnitClassStr = getStringUnitClass();
  int UnitIDInt = getIntUnitID();

  try
  {
    openfluid::fluidx::AdvancedUnitDescriptor Unit =
        this->mp_AdvFXDesc->getDomain().getUnit(UnitClassStr, UnitIDInt);
    return boost::python::object(Unit.UnitDescriptor->getProcessOrder());
  } WARNING_EXCEPTION

  return boost::python::object(); /* makes Python NONE */
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getUnitTos (
    boost::python::object UnitClass, boost::python::object UnitID)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyApplicationException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitID(UnitID);
  if (!getIntUnitID.check())
    throw PyApplicationException("needed integer for unit id", PyExc_TypeError);

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

    for(ItListUnit = ListUnit.begin(); ItListUnit != ListUnit.end();
        ++ItListUnit)
      ListRes.append(boost::python::make_tuple(
          boost::python::object((*ItListUnit).first),
          boost::python::object((*ItListUnit).second) ));
  } WARNING_EXCEPTION

  return ListRes;
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getUnitFroms (
    boost::python::object UnitClass, boost::python::object UnitID)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyApplicationException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitID(UnitID);
  if (!getIntUnitID.check())
    throw PyApplicationException("needed integer for unit id", PyExc_TypeError);

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

    for(ItListUnit = ListUnit.begin(); ItListUnit != ListUnit.end();
        ++ItListUnit)
      ListRes.append(boost::python::make_tuple(
          boost::python::object((*ItListUnit).first),
          boost::python::object((*ItListUnit).second) ));
  } WARNING_EXCEPTION

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
    throw PyApplicationException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitIDFrom(UnitIDFrom);
  if (!getIntUnitIDFrom.check())
    throw PyApplicationException("needed integer for unit id", PyExc_TypeError);

  boost::python::extract<std::string> getStringUnitClassTo(UnitClassTo);
  if (!getStringUnitClassTo.check())
    throw PyApplicationException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitIDTo(UnitIDTo);
  if (!getIntUnitIDTo.check())
    throw PyApplicationException("needed integer for unit id", PyExc_TypeError);

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
  } HANDLE_APPLICATIONEXCEPTION
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::removeFromToConnection (
    boost::python::object UnitClassFrom, boost::python::object UnitIDFrom,
    boost::python::object UnitClassTo, boost::python::object UnitIDTo)
{
  boost::python::extract<std::string> getStringUnitClassFrom(UnitClassFrom);
  if (!getStringUnitClassFrom.check())
    throw PyApplicationException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitIDFrom(UnitIDFrom);
  if (!getIntUnitIDFrom.check())
    throw PyApplicationException("needed integer for unit id", PyExc_TypeError);

  boost::python::extract<std::string> getStringUnitClassTo(UnitClassTo);
  if (!getStringUnitClassTo.check())
    throw PyApplicationException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitIDTo(UnitIDTo);
  if (!getIntUnitIDTo.check())
    throw PyApplicationException("needed integer for unit id", PyExc_TypeError);

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
  } HANDLE_APPLICATIONEXCEPTION
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getUnitChildren (
    boost::python::object UnitClass, boost::python::object UnitID)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyApplicationException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitID(UnitID);
  if (!getIntUnitID.check())
    throw PyApplicationException("needed integer for unit id", PyExc_TypeError);

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

    for(ItListUnit = ListUnit.begin(); ItListUnit != ListUnit.end();
        ++ItListUnit)
      ListRes.append(boost::python::make_tuple(
          boost::python::object((*ItListUnit).first),
          boost::python::object((*ItListUnit).second) ));
  } WARNING_EXCEPTION

  return ListRes;
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getUnitParents (
    boost::python::object UnitClass, boost::python::object UnitID)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyApplicationException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitID(UnitID);
  if (!getIntUnitID.check())
    throw PyApplicationException("needed integer for unit id", PyExc_TypeError);

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

    for(ItListUnit = ListUnit.begin(); ItListUnit != ListUnit.end();
        ++ItListUnit)
      ListRes.append(boost::python::make_tuple(
          boost::python::object((*ItListUnit).first),
          boost::python::object((*ItListUnit).second) ));
  } WARNING_EXCEPTION

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
    throw PyApplicationException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitIDParent(UnitIDParent);
  if (!getIntUnitIDParent.check())
    throw PyApplicationException("needed integer for unit id", PyExc_TypeError);

  boost::python::extract<std::string> getStringUnitClassChild(UnitClassChild);
  if (!getStringUnitClassChild.check())
    throw PyApplicationException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitIDChild(UnitIDChild);
  if (!getIntUnitIDChild.check())
    throw PyApplicationException("needed integer for unit id", PyExc_TypeError);

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
  } HANDLE_APPLICATIONEXCEPTION
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::removeParentChildConnection (
    boost::python::object UnitClassParent, boost::python::object UnitIDParent,
    boost::python::object UnitClassChild, boost::python::object UnitIDChild)
{
  boost::python::extract<std::string> getStringUnitClassParent(UnitClassParent);
  if (!getStringUnitClassParent.check())
    throw PyApplicationException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitIDParent(UnitIDParent);
  if (!getIntUnitIDParent.check())
    throw PyApplicationException("needed integer for unit id", PyExc_TypeError);

  boost::python::extract<std::string> getStringUnitClassChild(UnitClassChild);
  if (!getStringUnitClassChild.check())
    throw PyApplicationException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getIntUnitIDChild(UnitIDChild);
  if (!getIntUnitIDChild.check())
    throw PyApplicationException("needed integer for unit id", PyExc_TypeError);

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
  } HANDLE_APPLICATIONEXCEPTION
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::createAttribute (boost::python::object UnitClass,
                                   boost::python::object AttrName,
                                   boost::python::object AttrVal)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyApplicationException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<std::string> getStringAttrName(AttrName);
  if (!getStringAttrName.check())
    throw PyApplicationException("needed string for attribute name", PyExc_TypeError);
  boost::python::extract<std::string> getStringAttrValue(AttrVal);
  if (!getStringAttrValue.check())
    throw PyApplicationException("needed string for attribute value", PyExc_TypeError);

  std::string UnitClassStr = getStringUnitClass();
  std::string AttrNameStr = getStringAttrName();
  std::string AttrValStr = getStringAttrValue();

  try
  {
    this->mp_AdvFXDesc->getDomain().addAttribute(UnitClassStr, AttrNameStr,
        AttrValStr);
  } HANDLE_APPLICATIONEXCEPTION
}


// =====================================================================
// =====================================================================


boost::python::object PyOpenFLUID::getAttribute (
    boost::python::object UnitClass, boost::python::object UnitID,
    boost::python::object AttrName)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyApplicationException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getUnitID(UnitID);
  if (!getUnitID.check())
    throw PyApplicationException("needed integer for unit id", PyExc_TypeError);
  boost::python::extract<std::string> getStringAttrName(AttrName);
  if (!getStringAttrName.check())
    throw PyApplicationException("needed string for attribute name", PyExc_TypeError);

  std::string UnitClassStr = getStringUnitClass();
  int UnitIDInt = getUnitID();
  std::string AttrNameStr = getStringAttrName();

  try
  {
    std::string ResAttr = this->mp_AdvFXDesc->getDomain().getAttribute(
        UnitClassStr, UnitIDInt, AttrNameStr);
    return boost::python::object(ResAttr);
  } WARNING_EXCEPTION

  return boost::python::object(); /* makes Python NONE */
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::setAttribute (boost::python::object UnitClass,
                                boost::python::object UnitID,
                                boost::python::object AttrName,
                                boost::python::object AttrValue)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyApplicationException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<int> getUnitID(UnitID);
  if (!getUnitID.check())
    throw PyApplicationException("needed integer for unit id", PyExc_TypeError);
  boost::python::extract<std::string> getStringAttrName(AttrName);
  if (!getStringAttrName.check())
    throw PyApplicationException("needed string for attribute name", PyExc_TypeError);
  boost::python::extract<std::string> getStringAttrValue(AttrValue);
  if (!getStringAttrValue.check())
    throw PyApplicationException("needed string for attribute value", PyExc_TypeError);

  std::string UnitClassStr = getStringUnitClass();
  int UnitIDInt = getUnitID();
  std::string AttrNameStr = getStringAttrName();
  std::string AttrValStr = getStringAttrValue();

  try
  {
    std::string& ResAttr = this->mp_AdvFXDesc->getDomain().getAttribute(
        UnitClassStr, UnitIDInt, AttrNameStr);
    ResAttr.assign(AttrValStr);
  } HANDLE_APPLICATIONEXCEPTION
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::removeAttribute (boost::python::object UnitClass,
                                   boost::python::object AttrName)
{
  boost::python::extract<std::string> getStringUnitClass(UnitClass);
  if (!getStringUnitClass.check())
    throw PyApplicationException("needed string for unit class", PyExc_TypeError);
  boost::python::extract<std::string> getStringAttrName(AttrName);
  if (!getStringAttrName.check())
    throw PyApplicationException("needed string for attribute name", PyExc_TypeError);

  std::string UnitClassStr = getStringUnitClass();
  std::string AttrNameStr = getStringAttrName();

  try
  {
    this->mp_AdvFXDesc->getDomain().
        deleteAttribute(UnitClassStr, AttrNameStr);
  } HANDLE_APPLICATIONEXCEPTION
}


// =====================================================================
/* --------------------  INPUT OUTPUT FUNCTIONS  -------------------- */


void PyOpenFLUID::openDataset (boost::python::object Path)
{
  boost::python::extract<std::string> getStringPath(Path);
  if (!getStringPath.check())
    throw PyApplicationException("needed string for dataset path", PyExc_TypeError);

  std::string StrPath = getStringPath();

  try
  {
    openfluid::base::Init();

    if (this->mp_IOL != NULL) /* security */
      delete this->mp_IOL;
    this->mp_IOL = new openfluid::base::IOListener();

    this->initWithoutDescriptor();
    this->initFluidxDescriptor();

    openfluid::base::RuntimeEnvironment::getInstance()->
        setInputDir(std::string(StrPath));
    this->mp_FXDesc->loadFromDirectory(openfluid::base::RuntimeEnvironment::
        getInstance()->getInputDir());

    if (this->mp_AdvFXDesc != NULL) /* security */
      delete this->mp_AdvFXDesc;
    this->mp_AdvFXDesc = new openfluid::fluidx::AdvancedFluidXDescriptor(
        *(this->mp_FXDesc));

    this->initAdvancedFluidxDescriptor();

  } HANDLE_EXCEPTION
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::saveDataset (boost::python::object Path)
{
  boost::python::extract<std::string> getStringPath(Path);
  if (!getStringPath.check())
    throw PyApplicationException("needed string for dataset path", PyExc_TypeError);

  std::string StrPath = getStringPath();

  try
  {
    if (!boost::filesystem::exists(StrPath))
    {
      boost::filesystem::create_directory(StrPath);
      if (!boost::filesystem::exists(StrPath))
        throw PyApplicationException("error creating dataset directory");
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
    throw PyApplicationException("needed string for project path", PyExc_TypeError);

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
      throw openfluid::base::ApplicationException("PyOpenFLUID", StrPath +
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
{
  char* Keywords[5]; /* parameter names */
  Keywords[0] = (char*) "Path";
  Keywords[1] = (char*) "Name";
  Keywords[2] = (char*) "Description";
  Keywords[3] = (char*) "Authors";
  Keywords[4] = NULL;
  char* CharPath = NULL;
  char* CharName = NULL;
  char* CharDescp = NULL;
  char* CharAuth = NULL;
  /* checking parameters */
  if (!PyArg_ParseTupleAndKeywords(InTuple, InDict, "s|sss", Keywords,\
      &CharPath, &CharName, &CharDescp, &CharAuth))
  {
    /* if not path parameter */
    if (CharPath == NULL)
      throw PyApplicationException("project output path not given");
    /* if other kind of error */
    throw PyApplicationException("error getting parameters");
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
        throw PyApplicationException("error creating project directory");
    }

    /* project */
    if (ProjectManager->isProject(GUProjectPath)) /* if exists */
    {
      if(!ProjectManager->open(GUProjectPath))
        throw PyApplicationException("ProjectManager::open, error opening project");

      if (CharName != NULL) /* is parameter set */
      {
        Glib::ustring GUTmpName = Glib::ustring(CharName);
        ProjectManager->setName(GUTmpName);
      }
      if (CharDescp != NULL) /* is parameter set */
      {
        Glib::ustring GUTmpDescp = Glib::ustring(CharDescp);
        ProjectManager->setDescription(GUTmpDescp);
      }
      if (CharAuth != NULL) /* is parameter set */
      {
        Glib::ustring GUTmpAuthors = Glib::ustring(CharAuth);
        ProjectManager->setAuthors(GUTmpAuthors);
      }

      if (!ProjectManager->save())
        throw PyApplicationException("ProjectManager::save, error saving project");
    }
    else /* if creates */
    {
      Glib::ustring GUTmpName;
      if (CharName != NULL) /* is parameter set */
        GUTmpName = Glib::ustring(CharName);
      else
        GUTmpName = Glib::ustring("");

      Glib::ustring GUTmpDescp;
      if (CharDescp != NULL) /* is parameter set */
        GUTmpDescp = Glib::ustring(CharDescp);
      else
        GUTmpDescp = Glib::ustring("");

      Glib::ustring GUTmpAuthors;
      if (CharAuth != NULL) /* is parameter set */
        GUTmpAuthors = Glib::ustring(CharAuth);
      else
        GUTmpAuthors = Glib::ustring("");

      if (!ProjectManager->
          create(GUProjectPath, GUTmpName, GUTmpDescp, GUTmpAuthors, true))
        throw PyApplicationException("ProjectManager::create, error creating\
 and saving project");
    }

    std::string InputDir = ProjectManager->getInputDir();

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
    throw PyApplicationException("needed string for output path", PyExc_TypeError);

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
    throw PyApplicationException("needed integer for default delta t", PyExc_TypeError);

  const int DefaultDeltaTInt = getDefaultDeltaT();
  if (DefaultDeltaTInt <= 0)
    throw PyApplicationException("default delta t can't be negative or null",
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
    throw PyApplicationException("needed string for period begin date", PyExc_TypeError);

  /* 'yyyy-mm-dd hh:mm:ss' */
  std::string Pattern = std::string(
      "^(\\d{1,4})-(\\d{2})-(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2})$");
  std::string Target = getStringBDate();

  boost::regex RegexPattern = boost::regex(Pattern, boost::regex::extended);
  boost::smatch ResMatch;

  bool isMatchFound = boost::regex_match(Target, ResMatch, RegexPattern);

  if (isMatchFound && ResMatch.size() == 7)
  {
    int TabRes[6]; /* storage of numbers */
    int i;
    std::string TmpStr; /* string buffer */
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
    throw PyApplicationException("begin date isn't formatted with good format",
        PyExc_ValueError);
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::setPeriodEndDate (boost::python::object EDate)
{
  boost::python::extract<std::string> getStringEDate(EDate);
  if (!getStringEDate.check())
    throw PyApplicationException("needed string for period end date", PyExc_TypeError);

  /* 'yyyy-mm-dd hh:mm:ss' */
  std::string Pattern = std::string(
      "^(\\d{1,4})-(\\d{2})-(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2})$");
   std::string Target = getStringEDate();

  boost::regex RegexPattern = boost::regex(Pattern, boost::regex::extended);
  boost::smatch ResMatch;

  bool isMatchFound = boost::regex_match(Target, ResMatch, RegexPattern);

  if (isMatchFound && ResMatch.size() == 7)
  {
    int TabRes[6]; /* storage of numbers */
    int i;
    std::string TmpStr; /* string buffer */
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
    throw PyApplicationException("end date isn't formatted with good format",
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

    openfluid::machine::SimulatorPluginsManager::getInstance()
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
        *(this->mp_FXDesc), SBlob);

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


void PyOpenFLUID::updateOutputsConfig ()
{
}


// =====================================================================
/* ------------------------ PYTHON FUNCTIONS  ----------------------- */


boost::python::object PyOpenFLUID::getStr ()
{
  std::stringstream SStream(std::stringstream::in | std::stringstream::out);

  /* output: 'PyOpenFLUID(<version pyof>)' */
  SStream << "PyOpenFLUID(" << PYOPENFLUID_VERSION << ")";

  return boost::python::object(SStream.str());
}


// =====================================================================
/* ----------------------- SPECIAL FUNCTIONS  ----------------------- */


void PyOpenFLUID::initWithoutDescriptor ()
{
    /* custom observer */
    this->m_LastObsID = 1;
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::initFluidxDescriptor ()
{
    /* run descp */
    openfluid::fluidx::RunDescriptor& runDescp = this->mp_FXDesc->
      getRunDescriptor();

    std::time_t t = time(0); // get current time
    struct std::tm *Now = localtime(&t);

    runDescp.setDeltaT((unsigned int)60);
    runDescp.setBeginDate(openfluid::core::DateTime(Now->tm_year+1900,\
        Now->tm_mon+1, Now->tm_mday, 0, 0, 0));
    runDescp.setEndDate(openfluid::core::DateTime(Now->tm_year+1900,\
        Now->tm_mon+1, Now->tm_mday, 1, 0, 0));
    runDescp.setFilled(true);
}


// =====================================================================
// =====================================================================


void PyOpenFLUID::initAdvancedFluidxDescriptor ()
{
}


// =====================================================================
/* ----------------------- STATIC FUNCTIONS  ------------------------ */


void setPyOFCSVFormat (openfluid::fluidx::ObserverDescriptor& Observer)
{

    openfluid::ware::WareParams_t PairParam;

    PairParam[std::string("format.pyofformat.header")] =
        openfluid::core::StringValue(std::string("colnames-as-data"));

    PairParam[std::string("format.pyofformat.date")] =
        openfluid::core::StringValue(std::string("%Y-%m-%dT%H:%M:%S"));

    PairParam[std::string("format.pyofformat.precision")] =
        openfluid::core::StringValue(std::string("7"));

    PairParam[std::string("format.pyofformat.colsep")] =
        openfluid::core::StringValue(std::string("	"));

    Observer.setParameters(PairParam);
}
