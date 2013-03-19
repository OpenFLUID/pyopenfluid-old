#ifndef __PYOPENFLUID_HPP__
#define __PYOPENFLUID_HPP__

#include <Python.h>
#include <boost/python/dict.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/object.hpp>

#include <openfluid/fluidx/FluidXDescriptor.hpp>
#include <openfluid/fluidx/AdvancedFluidXDescriptor.hpp>

/*!
 * @file pyopenfluid.cpp
 * @brief This package allows to load, parameterize, run and analyse OpenFLUID
 *    simulations within the Python 2.x environment
 * @version 1.7.2-0
 * @author Bastien Vaysse <bastien.vaysse@supagro.inra.fr>
 * @date mercredi 06 février 2013 
 */


// =====================================================================
// =====================================================================
struct PyOpenFLUIDCopy_t;


class PyOpenFLUID
{
  public :

// =====================================================================
// =====================================================================


    /*!
     * @brief Create an OpenFLUID class.
     * 
     */
    PyOpenFLUID ();


// =====================================================================
// =====================================================================


    /*!
     * @brief Destroy an OpenFLUID class.
     * 
     */
    ~PyOpenFLUID ();


// =====================================================================
/* ----------------------  GENERAL FUNCTIONS  ----------------------- */


    /*!
     * @brief Returns the OpenFLUID version.
     * 
     * 
     * @return
     *    the OpenFLUID version number
     */
    PyObject* getVersion (PyObject* PyObSelf,
                          PyObject* InTuple,
                          PyObject* InDict);


// =====================================================================
// =====================================================================


    /*!
     * @brief Adds paths to search for simulation functions.
     * 
     * @param Paths
     *    the semicolon separated paths to add
     */
    void addExtraFunctionsPaths (boost::python::object Paths);


// =====================================================================
// =====================================================================


    /*!
     * @brief Reset paths to search for simulation functions.
     * 
     */
    void resetExtraFunctionsPaths ();


// =====================================================================
// =====================================================================


    /*!
     * @brief Returns the added paths to search for simulation functions.
     * 
     * @return
     *    a list of paths
     */
    boost::python::object getExtraFunctionsPaths ();


// =====================================================================
// =====================================================================


    /*!
     * @brief Adds paths to search for observers.
     * 
     * @param Paths
     *    the semicolon separated paths to add
     */
    void addExtraObserversPaths (boost::python::object Paths);


// =====================================================================
// =====================================================================


    /*!
     * @brief Reset paths to search for observers.
     * 
     */
    void resetExtraObserversPaths ();


// =====================================================================
// =====================================================================


    /*!
     * @brief Returns the added paths to search for observers.
     * 
     * @return
     *    a list of paths
     */
    boost::python::object getExtraObserversPaths ();


// =====================================================================
// =====================================================================


    /*!
     * @brief Prints informations to screen about simulation definition class
     * (self).
     * 
     */
    void printSimulationInfo ();


// =====================================================================
/* ------------------------  MODEL FUNCTIONS  ----------------------- */


    /*!
     * @brief Returns a function parameter value.
     * 
     * @param FuncID
     *    the simulation function ID
     * @param ParamName
     *    the name of the parameter
     * 
     * @return
     *    the parameter value
     */
    boost::python::object getFunctionParam (boost::python::object FuncID,
                                            boost::python::object ParamName);


// =====================================================================
// =====================================================================


    /*!
     * @brief Sets a function parameter value.
     * 
     * @param FuncID
     *    the simulation function ID
     * @param ParamName
     *    the name of the parameter
     * @param ParamVal
     *    the parameter value
     */
    void setFunctionParam (boost::python::object FuncID,
                           boost::python::object ParamName,
                           boost::python::object ParamValue);


// =====================================================================
// =====================================================================


    /*!
     * @brief Removes a function parameter.
     * 
     * @param FuncID
     *    the simulation function ID
     * @param ParamName
     *    the name of the parameter
     */
    void removeFunctionParam (boost::python::object FuncID,
                              boost::python::object ParamName);


// =====================================================================
// =====================================================================


    /*!
     * @brief Gets all parameter of a function.
     * 
     * @param FuncID
     *    the simulation function ID
     *
     * @return
     *    a list of parameter name
     */
    boost::python::object getFunctionParams (boost::python::object FuncID);


// =====================================================================
// =====================================================================


    /*!
     * @brief Returns a generator parameter value.
     * 
     * @param UnitClass
     *    the unit class to which the generator is applied
     * @param VarName
     *    the variable name to which the generator is applied
     * @param ParamName
     *    the name of the parameter
     * 
     * @return
     *    the parameter value
     */
    boost::python::object getGeneratorParam (boost::python::object UnitClass,
                                             boost::python::object VarName,
                                             boost::python::object ParamName);


// =====================================================================
// =====================================================================


    /*!
     * @brief Sets a generator parameter value.
     * 
     * @param UnitClass
     *    the unit class to which the generator is applied
     * @param VarName
     *    the variable name to which the generator is applied
     * @param ParamName
     *    the name of the parameter
     * @param ParamVal
     *    the parameter value
     */
    void setGeneratorParam (boost::python::object UnitClass,
                            boost::python::object VarName,
                            boost::python::object ParamName,
                            boost::python::object ParamValue);


// =====================================================================
// =====================================================================


    /*!
     * @brief Returns a model global parameter value.
     * 
     * @param ParamName
     *    the name of the parameter
     * 
     * @return
     *    the parameter value
     */
    boost::python::object getModelGlobalParam (boost::python::object ParamName);


// =====================================================================
// =====================================================================


    /*!
     * @brief Sets a model global parameter value.
     * 
     * @param ParamName
     *    the name of the parameter
     * @param ParamVal
     *    the parameter value
     */
    void setModelGlobalParam (boost::python::object ParamName,
                              boost::python::object ParamValue);


// =====================================================================
// =====================================================================


    /*!
     * @brief Returns all model global parameter.
     * 
     * @return
     *    a list of parameter name.
     */
    boost::python::object getModelGlobalParams ();


// =====================================================================
// =====================================================================


    /*!
     * @brief Removes a model global parameter.
     * 
     * @param ParamName
     *    the name of the parameter
     */
    void removeModelGlobalParam (boost::python::object ParamName);


// =====================================================================
// =====================================================================


    /*!
     * @brief Adds a function.
     * 
     * @param FuncID
     *    the simulation function ID
     */
    void addFunction (boost::python::object FuncID);


// =====================================================================
// =====================================================================


    /*!
     * @brief Removes a function.
     * 
     * @param FuncID
     *    the simulation function ID
     */
    void removeFunction (boost::python::object FuncID);


// =====================================================================
// =====================================================================


    /*!
     * @brief Removes all functions.
     * 
     */
    void clearModel ();


// =====================================================================
// =====================================================================


    /*!
     * @brief Gets all functions names.
     * 
     * @return
     *    a list of function name.
     */
    boost::python::object getFunctionsInModel ();


// =====================================================================
/* ---------------------  MONITORING FUNCTIONS  --------------------- */


    /*!
     * @brief Returns an observer parameter value.
     * 
     * @param ObsID
     *    the observer id
     * @param ParamName
     *    the name of the parameter
     * 
     * @return
     *    the parameter value
     */
    boost::python::object getObserverParam (boost::python::object ObsID,
                                            boost::python::object ParamName);


// =====================================================================
// =====================================================================


    /*!
     * @brief Sets an observer parameter value.
     * 
     * @param ObsID
     *    the observer id
     * @param ParamName
     *    the name of the parameter
     * @param ParamVal
     *    the parameter value
     */
    void setObserverParam (boost::python::object ObsID,
                           boost::python::object ParamName,
                           boost::python::object ParamValue);


// =====================================================================
// =====================================================================


    /*!
     * @brief Removes an observer parameter.
     * 
     * @param ObsID
     *    the observer id
     * @param ParamName
     *    the name of the parameter
     */
    void removeObserverParam (boost::python::object ObsID,
                              boost::python::object ParamName);


// =====================================================================
// =====================================================================


    /*!
     * @brief Gets all observer parameters name.
     * 
     * @param ObsID
     *    the observer id
     * 
     * @return
     *    a list of parameters name
     */
    boost::python::object getObserverParams (boost::python::object ObsID);


// =====================================================================
// =====================================================================


    /*!
     * @brief Adds an observer.
     * 
     * @param ObsID
     *    the observer id
     */
    void addObserver (boost::python::object ObsID);


// =====================================================================
// =====================================================================


    /*!
     * @brief Removes an observer.
     * 
     * @param ObsID
     *    the observer id
     */
    void removeObserver (boost::python::object ObsID);


// =====================================================================
// =====================================================================


    /*!
     * @brief Removes all observers.
     */
    void clearMonitoring ();


// =====================================================================
// =====================================================================


    /*!
     * @brief Gets all observer name.
     * 
     * @return
     *    a list of observer name.
     */
    boost::python::object getObserversInMonitoring ();


// =====================================================================
/* -------------------  SPATIAL DOMAIN FUNCTIONS  ------------------- */


    /*!
     * @brief Returns the existing units classes.
     * 
     * @return
     *    a list of units classes
     */
    boost::python::object getUnitsClasses ();


// =====================================================================
// =====================================================================


    /*!
     * @brief Returns the existing units IDs for a given units class.
     * 
     * @param UnitClass
     *    the unit class
     * 
     * @return
     *    a list of units IDs
     */
    boost::python::object getUnitsIDs (boost::python::object UnitClass);


// =====================================================================
// =====================================================================


    /*!
     * @brief Adds an new unit.
     * 
     * @param UnitClass
     *    an unit class
     * @param UnitID
     *    an new unit id
     * @param PcsOrder
     *    a process order
     */
    void addUnit (boost::python::object UnitClass,
                  boost::python::object UnitID,
                  boost::python::object PcsOrder);


// =====================================================================
// =====================================================================


    /*!
     * @brief Removes an unit.
     * 
     * @param UnitClass
     *    an unit class
     * @param UnitID
     *    an unit id
     */
    void removeUnit (boost::python::object UnitClass,
                     boost::python::object UnitID);


// =====================================================================
// =====================================================================


    /*!
     * @brief Removes all units from an unit class.
     * 
     * @param UnitClass
     *    an unit class
     */
    void clearUnitClass (boost::python::object UnitClass);


// =====================================================================
// =====================================================================


    /*!
     * @brief Sets the process order of an unit.
     * 
     * @param UnitClass
     *    an unit class
     * @param UnitID
     *    an unit id
     * @param PcsOrder
     *    a process order
     */
    void setUnitProcessOrder (boost::python::object UnitClass,
                              boost::python::object UnitID,
                              boost::python::object PcsOrder);


// =====================================================================
// =====================================================================


    /*!
     * @brief Gets the process order of an unit.
     * 
     * @param UnitClass
     *    an unit class
     * @param UnitID
     *    an unit id
     * 
     * @return
     *    the process order
     */
    boost::python::object getUnitProcessOrder (boost::python::object UnitClass,
                                               boost::python::object UnitID);


// =====================================================================
// =====================================================================


    /*!
     * @brief Gets children units of an unit.
     * 
     * @param UnitClass
     *    an unit class
     * @param UnitID
     *    an unit id
     * 
     * @return
     *    a list of tuple of units classes and units
     */
    boost::python::object getUnitsChildren (boost::python::object UnitClass,
                                            boost::python::object UnitID);


// =====================================================================
// =====================================================================


    /*!
     * @brief Gets parents units of an unit.
     * 
     * @param UnitClass
     *    an unit class
     * @param UnitID
     *    an unit id
     * 
     * @return
     *    a list of tuple of units classes and units
     */
    boost::python::object getUnitsParents (boost::python::object UnitClass,
                                           boost::python::object UnitID);


// =====================================================================
// =====================================================================


    /*!
     * @brief Adds a child on an unit.
     * 
     * @param UnitClassFrom
     *    an unit class (parent)
     * @param UnitIDFrom
     *    an unit id (parent)
     * @param UnitClassTo
     *    an unit class (child)
     * @param UnitIDTo
     *    an unit id (child)
     */
    void addUnitChild (boost::python::object UnitClassFrom,
                       boost::python::object UnitIDFrom,
                       boost::python::object UnitClassTo,
                       boost::python::object UnitIDTo);


// =====================================================================
// =====================================================================


    /*!
     * @brief Removes a child of an unit.
     * 
     * @param UnitClassFrom
     *    an unit class (parent)
     * @param UnitIDFrom
     *    an unit id (parent)
     * @param UnitClassTo
     *    an unit class (child)
     * @param UnitIDTo
     *    an unit id (child)
     */
    void removeUnitChild (boost::python::object UnitClassFrom,
                          boost::python::object UnitIDFrom,
                          boost::python::object UnitClassTo,
                          boost::python::object UnitIDTo);


// =====================================================================
// =====================================================================


    /*!
     * @brief Creates an inputdata for alla spatial units of a class,
     *    initialized with a default value
     * 
     * @param UnitClass
     *    the unit class
     * @param IDataName
     *    the inputdata name
     * @param IDataVal
     *    the default inputdata value for alla units
     */
    void createInputData (boost::python::object UnitClass,
                          boost::python::object IDataName,
                          boost::python::object IDataVal);


// =====================================================================
// =====================================================================


    /*!
     * @brief Returns an inputdata value for a given spatial unit.
     * 
     * @param UnitClass
     *    the unit class
     * @param UnitID
     *    the unit
     * @param IDataName
     *    the name of the inputdata
     * 
     * @return
     *    the inputdata value
     */
    boost::python::object getInputData (boost::python::object UnitClass,
                                        boost::python::object UnitID,
                                        boost::python::object IDataName);

// =====================================================================
// =====================================================================


    /*!
     * @brief Sets an inputdata value for a given spatial unit.
     * 
     * @param UnitClass
     *    the unit class
     * @param UnitID
     *    the unit ID
     * @param IDataName
     *    the name of the inputdata
     * @param IDataVal
     *    the value of the inputdata
     */
    void setInputData (boost::python::object UnitClass,
                       boost::python::object UnitID,
                       boost::python::object IDataName,
                       boost::python::object IDataValue);


// =====================================================================
// =====================================================================


    /*!
     * @brief Removes an inputdata value for a given spatial unit.
     * 
     * @param UnitClass
     *    the unit class
     * @param UnitID
     *    the unit
     * @param IDataName
     *    the name of the inputdata
     */
    void removeInputData (boost::python::object UnitClass,
                          boost::python::object IDataName);


// =====================================================================
/* --------------------  INPUT OUTPUT FUNCTIONS  -------------------- */


    /*!
     * @brief Opens a dataset and returns a simulation definition class (self).
     * 
     * @param Path
     *    he full path of the dataset to open
     * 
     * @return
     *    a simulation definition class (PyOpenFLUID)
     */
    PyOpenFLUID* openDataset (boost::python::object Path);


// =====================================================================
// =====================================================================


    /*!
     * @brief Opens a project and returns a simulation definition class
     * (PyOpenFLUID).
     * 
     * @param Path
     *    the full path of the project to open
     * 
     * @return
     *    a simulation definition class (PyOpenFLUID)
     */
    PyOpenFLUID* openProject (boost::python::object Path);


// =====================================================================
// =====================================================================


    /*!
     * @brief Sets the current output directory for simulations.
     * 
     * @param Path
     *    the output directory path
     */
    void setCurrentOutputDir (boost::python::object Path);


// =====================================================================
// =====================================================================


    /*!
     * @brief Gets the current output directory for simulations.
     * 
     * @return
     *    the output directory path
     */
    boost::python::object getCurrentOutputDir ();


// =====================================================================
/* ---------------------  SIMULATION FUNCTIONS  --------------------- */


    /*!
     * @brief Returns the default simulation time step.
     * 
     * @return
     *    the time step value in seconds
     */
    boost::python::object getDefaultDeltaT ();


// =====================================================================
// =====================================================================


    /*!
     * @brief Sets the default simulation time step.
     * 
     * @param DeltaT
     *    the time step value in seconds
     */
    void setDefaultDeltaT (boost::python::object DefaultDeltaT);


// =====================================================================
// =====================================================================


    /*!
     * @brief Returns the simulation period begin date.
     * 
     * @return
     *    the begin date as a python dict, containing following attributs :
            year, month, day, hour, minute, second
     */
    boost::python::object getPeriodBeginDate ();


// =====================================================================
// =====================================================================


    /*!
     * @brief Returns the simulation period end date.
     * 
     * @return
     *    the end date as a python dict, containing following attributs :
            year, month, day, hour, minute, second
     */
    boost::python::object getPeriodEndDate ();


// =====================================================================
// =====================================================================


    /*!
     * @brief Sets the simulation period begin date.
     * 
     * @param BDate   the begin date as an ISO datetime string (%Y-%m-%d %H:%M:%S)
     */
    void setPeriodBeginDate (boost::python::object BDate);


// =====================================================================
// =====================================================================


    /*!
     * @brief Sets the simulation period end date.
     * 
     * @param EDate   the end date as an ISO datetime string (%Y-%m-%d %H:%M:%S)
     */
    void setPeriodEndDate (boost::python::object EDate);


// =====================================================================
// =====================================================================


    /*!
     * @brief Runs a project and returns a simulation definition class (PyOpenFLUID).
     * 
     * @param Path
     *    the full path of the project to open
     * 
     * @return
     *    a simulation definition class (PyOpenFLUID)
     */
    PyOpenFLUID* runProject (boost::python::object Path);


// =====================================================================
// =====================================================================


    /*!
     * @brief Runs a simulation from a simulation definition class (self).
     * 
     * @return
     *    1 if the simulation runned without problems, 0 otherwise
     */
    boost::python::object runSimulation ();


// =====================================================================
// =====================================================================


    /*!
     * @brief Loads results as a dataframe, giving output dataset informations.
     * 
     * @param UnitClass
     *    the unit class
     * @param UnitID
     *    the unit ID
     * @param Suffix
     *    the output dataset suffix
     * 
     * @return
     *    a dataframe containing the simulation results
     */
//    PyOpenFLUID* loadResult (boost::python::object UnitClass,
//                             boost::python::object UnitID,
//                             boost::python::object Suffix);


// =====================================================================
// =====================================================================


    /*!
     * @brief Loads results as a dataframe, giving output file name.
     * 
     * @param FilePath
     *    the full path of the file to load
     * 
     * @return
     *    a dataframe containing the simulation results
     */
//    PyOpenFLUID* loadResultFile (boost::python::object FilePath);


// =====================================================================
// =====================================================================


    /*!
     * @brief Updates output configuration.
     */
    void updateOutputsConfig ();


// =====================================================================
/* ------------------------ PYTHON FUNCTIONS  ----------------------- */


    /*!
     * @brief Return a string representation of the class.
     * 
     * @return
     *    a string representation of the class
     */
    boost::python::object getStr ();


// =====================================================================
/* ------------------------ OTHER FUNCTIONS  ------------------------ */


    void changeFluidXDescriptor (openfluid::fluidx::FluidXDescriptor& InputFXD);


// =====================================================================
// =====================================================================


    void getFromCopyStruct (PyOpenFLUIDCopy_t* CopyStruct);


// =====================================================================
// =====================================================================


    void putOnCopyStruct (PyOpenFLUIDCopy_t* CopyStruct);


// =====================================================================
// =====================================================================


  private :
    openfluid::fluidx::FluidXDescriptor m_FXDesc;
    openfluid::fluidx::AdvancedFluidXDescriptor m_AdvFXDesc;

};


// =====================================================================
// =====================================================================


struct PyOpenFLUIDCopy_t
{
  public:
    openfluid::fluidx::FluidXDescriptor* mp_FXDesc;
    openfluid::fluidx::AdvancedFluidXDescriptor* mp_AdvFXDesc;
};


// =====================================================================
// =====================================================================


void copy (PyOpenFLUID InputClass, PyOpenFLUID OutputClass);


#endif // __PYOPENFLUID_HPP__
