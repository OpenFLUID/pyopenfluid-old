#ifndef __PYOPENFLUID_HPP__
#define __PYOPENFLUID_HPP__

#include <Python.h>
#include <boost/python/dict.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/object.hpp>

#include <openfluid/base/IOListener.hpp>
#include <openfluid/fluidx/FluidXDescriptor.hpp>
#include <openfluid/fluidx/AdvancedFluidXDescriptor.hpp>


// =====================================================================
// =====================================================================


class PyOpenFLUID
{
  public :

// =====================================================================
// =====================================================================


    PyOpenFLUID ();


// =====================================================================
// =====================================================================


    ~PyOpenFLUID ();


// =====================================================================
/* ----------------------  GENERAL FUNCTIONS  ----------------------- */


    PyObject* getVersion (PyObject* PyObSelf,
                          PyObject* InTuple,
                          PyObject* InDict);


// =====================================================================
// =====================================================================


    void addExtraFunctionsPaths (boost::python::object Paths);


// =====================================================================
// =====================================================================


    void resetExtraFunctionsPaths ();


// =====================================================================
// =====================================================================


    boost::python::object getExtraFunctionsPaths ();


// =====================================================================
// =====================================================================


    void addExtraObserversPaths (boost::python::object Paths);


// =====================================================================
// =====================================================================


    void resetExtraObserversPaths ();


// =====================================================================
// =====================================================================


    boost::python::object getExtraObserversPaths ();


// =====================================================================
// =====================================================================


    void printSimulationInfo ();


// =====================================================================
/* ------------------------  MODEL FUNCTIONS  ----------------------- */


    boost::python::object getFunctionParam (boost::python::object FuncID,
                                            boost::python::object ParamName);


// =====================================================================
// =====================================================================


    void setFunctionParam (boost::python::object FuncID,
                           boost::python::object ParamName,
                           boost::python::object ParamValue);


// =====================================================================
// =====================================================================


    void removeFunctionParam (boost::python::object FuncID,
                              boost::python::object ParamName);


// =====================================================================
// =====================================================================


    boost::python::object getFunctionParams (boost::python::object FuncID);


// =====================================================================
// =====================================================================


    boost::python::object getGeneratorParam (boost::python::object UnitClass,
                                             boost::python::object VarName,
                                             boost::python::object ParamName);


// =====================================================================
// =====================================================================


    void setGeneratorParam (boost::python::object UnitClass,
                            boost::python::object VarName,
                            boost::python::object ParamName,
                            boost::python::object ParamValue);


// =====================================================================
// =====================================================================


    boost::python::object getModelGlobalParam (boost::python::object ParamName);


// =====================================================================
// =====================================================================


    void setModelGlobalParam (boost::python::object ParamName,
                              boost::python::object ParamValue);


// =====================================================================
// =====================================================================


    boost::python::object getModelGlobalParams ();


// =====================================================================
// =====================================================================


    void removeModelGlobalParam (boost::python::object ParamName);


// =====================================================================
// =====================================================================


    boost::python::object getModelItems ();


// =====================================================================
// =====================================================================


    void addFunction (boost::python::object FuncID);


// =====================================================================
// =====================================================================


    void removeFunction (boost::python::object FuncID);


// =====================================================================
// =====================================================================


    void clearModel ();


// =====================================================================
// =====================================================================


    boost::python::object getFunctionsInModel ();


// =====================================================================
/* ---------------------  MONITORING FUNCTIONS  --------------------- */


    boost::python::object getObserverParam (boost::python::object ObsID,
                                            boost::python::object ParamName);


// =====================================================================
// =====================================================================


    void setObserverParam (boost::python::object ObsID,
                           boost::python::object ParamName,
                           boost::python::object ParamValue);


// =====================================================================
// =====================================================================


    void removeObserverParam (boost::python::object ObsID,
                              boost::python::object ParamName);


// =====================================================================
// =====================================================================


    boost::python::object getObserverParams (boost::python::object ObsID);


// =====================================================================
// =====================================================================


    void addObserver (boost::python::object ObsID);


// =====================================================================
// =====================================================================


    void removeObserver (boost::python::object ObsID);


// =====================================================================
// =====================================================================


    void clearMonitoring ();


// =====================================================================
// =====================================================================


    boost::python::object getObserversInMonitoring ();


// =====================================================================
/* -------------------  SPATIAL DOMAIN FUNCTIONS  ------------------- */


    boost::python::object getUnitsClasses ();


// =====================================================================
// =====================================================================


    boost::python::object getUnitsIDs (boost::python::object UnitClass);


// =====================================================================
// =====================================================================


    void addUnit (boost::python::object UnitClass,
                  boost::python::object UnitID,
                  boost::python::object PcsOrder);


// =====================================================================
// =====================================================================


    void removeUnit (boost::python::object UnitClass,
                     boost::python::object UnitID);


// =====================================================================
// =====================================================================


    void clearAllUnits (boost::python::object UnitClass);


// =====================================================================
// =====================================================================


    void setUnitProcessOrder (boost::python::object UnitClass,
                              boost::python::object UnitID,
                              boost::python::object PcsOrder);


// =====================================================================
// =====================================================================


    boost::python::object getUnitProcessOrder (boost::python::object UnitClass,
                                               boost::python::object UnitID);


// =====================================================================
// =====================================================================


    boost::python::object getUnitTos (boost::python::object UnitClass,
                                      boost::python::object UnitID);


// =====================================================================
// =====================================================================


    boost::python::object getUnitFroms (boost::python::object UnitClass,
                                        boost::python::object UnitID);


// =====================================================================
// =====================================================================


    void addFromToConnection (boost::python::object UnitClassFrom,
                              boost::python::object UnitIDFrom,
                              boost::python::object UnitClassTo,
                              boost::python::object UnitIDTo);


// =====================================================================
// =====================================================================


    void removeFromToConnection (boost::python::object UnitClassFrom,
                                 boost::python::object UnitIDFrom,
                                 boost::python::object UnitClassTo,
                                 boost::python::object UnitIDTo);


// =====================================================================
// =====================================================================


    boost::python::object getUnitChildren (boost::python::object UnitClass,
                                            boost::python::object UnitID);


// =====================================================================
// =====================================================================


    boost::python::object getUnitParents (boost::python::object UnitClass,
                                           boost::python::object UnitID);


// =====================================================================
// =====================================================================


    void addParentChildConnection (boost::python::object UnitClassParent,
                                   boost::python::object UnitIDParent,
                                   boost::python::object UnitClassChild,
                                   boost::python::object UnitIDChild);


// =====================================================================
// =====================================================================


    void removeParentChildConnection (boost::python::object UnitClassParent,
                                      boost::python::object UnitIDParent,
                                      boost::python::object UnitClassChild,
                                      boost::python::object UnitIDChild);


// =====================================================================
// =====================================================================


    void createInputData (boost::python::object UnitClass,
                          boost::python::object IDataName,
                          boost::python::object IDataVal);


// =====================================================================
// =====================================================================


    boost::python::object getInputData (boost::python::object UnitClass,
                                        boost::python::object UnitID,
                                        boost::python::object IDataName);

// =====================================================================
// =====================================================================


    void setInputData (boost::python::object UnitClass,
                       boost::python::object UnitID,
                       boost::python::object IDataName,
                       boost::python::object IDataValue);


// =====================================================================
// =====================================================================


    void removeInputData (boost::python::object UnitClass,
                          boost::python::object IDataName);


// =====================================================================
/* --------------------  INPUT OUTPUT FUNCTIONS  -------------------- */


    void openDataset (boost::python::object Path);


// =====================================================================
// =====================================================================


    void openProject (boost::python::object Path);


// =====================================================================
// =====================================================================


    void setCurrentOutputDir (boost::python::object Path);


// =====================================================================
// =====================================================================


    boost::python::object getCurrentOutputDir ();


// =====================================================================
/* ---------------------  SIMULATION FUNCTIONS  --------------------- */


    boost::python::object getDefaultDeltaT ();


// =====================================================================
// =====================================================================


    void setDefaultDeltaT (boost::python::object DefaultDeltaT);


// =====================================================================
// =====================================================================


    boost::python::object getPeriodBeginDate ();


// =====================================================================
// =====================================================================


    boost::python::object getPeriodEndDate ();


// =====================================================================
// =====================================================================


    void setPeriodBeginDate (boost::python::object BDate);


// =====================================================================
// =====================================================================


    void setPeriodEndDate (boost::python::object EDate);


// =====================================================================
// =====================================================================


    void runProject (boost::python::object Path);


// =====================================================================
// =====================================================================


    boost::python::object runSimulation ();


// =====================================================================
// =====================================================================


//    void loadResult (boost::python::object UnitClass,
//                             boost::python::object UnitID,
//                             boost::python::object Suffix);


// =====================================================================
// =====================================================================


//    void loadResultFile (boost::python::object FilePath);


// =====================================================================
// =====================================================================


    void updateOutputsConfig ();


// =====================================================================
/* ------------------------ PYTHON FUNCTIONS  ----------------------- */


    boost::python::object getStr ();


// =====================================================================
// =====================================================================


  private :
    openfluid::base::IOListener* mp_IOL;
    openfluid::fluidx::FluidXDescriptor* mp_FXDesc;
    openfluid::fluidx::AdvancedFluidXDescriptor* mp_AdvFXDesc;

};


#endif // __PYOPENFLUID_HPP__
