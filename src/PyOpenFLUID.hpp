#include <Python.h>
#include <boost/python.hpp>
//#include <openfluid/base.hpp>
#include <vector>
#include <string>

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



class PyOpenFLUID
{
  public :

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
    boost::python::str* getVersion ();


// =====================================================================
// =====================================================================


    /*!
     * @brief Adds paths to search for simulation functions.
     * 
     * @param Paths
     *    the semicolon separated paths to add
     */
    void addExtraFunctionsPaths (boost::python::str BoostPaths);


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
     *    a vector of paths
     */
    boost::python::list* getExtraFunctionsPaths ();


// =====================================================================
// =====================================================================


    /*!
     * @brief Adds paths to search for observers.
     * 
     * @param Paths
     *    the semicolon separated paths to add
     */
    void addExtraObserversPaths (boost::python::str BoostPaths);


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
     *    a vector of paths
     */
    boost::python::list* getExtraObserversPaths ();


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
    boost::python::str* getFunctionParam (boost::python::str FuncID,
                                          boost::python::str ParamName);


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
    void setFunctionParam (boost::python::str FuncID,
                           boost::python::str ParamName,
                           boost::python::str ParamValue);


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
    boost::python::str* getGeneratorParam (boost::python::str UnitClass,
                                           boost::python::str VarName,
                                           boost::python::str ParamName);


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
    void setGeneratorParam (boost::python::str UnitClass,
                            boost::python::str VarName,
                            boost::python::str ParamName,
                            boost::python::str ParamValue);


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
    boost::python::str* getModelGlobalParam (boost::python::str ParamName);


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
    void setModelGlobalParam (boost::python::str ParamName,
                              boost::python::str ParamValue);


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
    boost::python::str* getObserverParam (boost::python::str ObsID,
                                          boost::python::str ParamName);


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
    void setObserverParam (boost::python::str ObsID,
                           boost::python::str ParamName,
                           boost::python::str ParamValue);


// =====================================================================
/* -------------------  SPATIAL DOMAIN FUNCTIONS  ------------------- */


    /*!
     * @brief Returns the existing units classes.
     * 
     * @return
     *    a vector of units classes
     */
    boost::python::list* getUnitsClasses ();


// =====================================================================
// =====================================================================


    /*!
     * @brief Returns the existing units IDs for a given units class.
     * 
     * @param UnitClass
     *    the unit class
     * 
     * @return
     *    a vector of units IDs
     */
    boost::python::list* getUnitsIDs (boost::python::str UnitClass);


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
    void createInputData (boost::python::str UnitClass,
                          boost::python::str IDataName,
                          boost::python::str IDataVal);


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
    boost::python::str* getInputData (boost::python::str UnitClass, int UnitID,
                                      boost::python::str IDataName);


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
    void setInputData (boost::python::str UnitClass, int UnitID,
                       boost::python::str IDataName,
                       boost::python::str IDataValue);


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
    PyOpenFLUID* openDataset (boost::python::str Path);


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
    PyOpenFLUID* openProject (boost::python::str Path);


// =====================================================================
// =====================================================================


    /*!
     * @brief Sets the current output directory for simulations.
     * 
     * @param Path
     *    the output directory path
     */
    void setCurrentOutputDir (boost::python::str Path);


// =====================================================================
/* ---------------------  SIMULATION FUNCTIONS  --------------------- */


    /*!
     * @brief Returns the default simulation time step.
     * 
     * @return
     *    the time step value in seconds
     */
    int getDefaultDeltaT ();


// =====================================================================
// =====================================================================


    /*!
     * @brief Sets the default simulation time step.
     * 
     * @param DeltaT
     *    the time step value in seconds
     */
    void setDefaultDeltaT (int DeltaT);


// =====================================================================
// =====================================================================


    /*!
     * @brief Returns the simulation period begin date.
     * 
     * @return
     *    the begin date as an ISO datetime string (%Y-%m-%d %H:%M:%S)
     */
    boost::python::str* getPeriodBeginDate ();


// =====================================================================
// =====================================================================


    /*!
     * @brief Returns the simulation period end date.
     * 
     * @return
     *    the end date as an ISO datetime string (%Y-%m-%d %H:%M:%S)
     */
    boost::python::str* getPeriodEndDate ();


// =====================================================================
// =====================================================================


    /*!
     * @brief Sets the simulation period begin date.
     * 
     * @param BeginDate
     *    the begin date as an ISO datetime string (%Y-%m-%d %H:%M:%S)
     */
    void setPeriodBeginDate (boost::python::str BeginDate);


// =====================================================================
// =====================================================================


    /*!
     * @brief Sets the simulation period end date.
     * 
     * @param EndDate
     *    the end date as an ISO datetime string (%Y-%m-%d %H:%M:%S)
     */
    void setPeriodEndDate (boost::python::str EndDate);


// =====================================================================
// =====================================================================


    /*!
     * @brief Runs a project and returns a simulation definition class (PyOpenFLUID).
     * 
     * @param Path
     *    the full path of the dataset to open
     * 
     * @return
     *    a simulation definition class (PyOpenFLUID)
     */
    PyOpenFLUID* runProject (boost::python::str Path);


// =====================================================================
// =====================================================================


    /*!
     * @brief Runs a simulation from a simulation definition class (self).
     * 
     */
    void runSimulation ();


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
    PyOpenFLUID* loadResult (boost::python::str UnitClass, int UnitID,
                               boost::python::str Suffix);


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
    PyOpenFLUID* loadResultFile (boost::python::str FilePath);


// =====================================================================
// =====================================================================


  private :
//    openfluid::base::DomainDescriptor m_Domain;
//    openfluid::base::DatastoreDescriptor m_Datastore;
//    openfluid::base::ModelDescriptor m_Model;
//    openfluid::base::MonitoringDescriptor m_Monitoring;
//    openfluid::base::RunDescriptor m_Run;

};
