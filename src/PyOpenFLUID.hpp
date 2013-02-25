#include <Python.h>
#include <boost/python.hpp>
#include <openfluid/fluidx/FluidXDescriptor.hpp>

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
    boost::python::object getVersion ();


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
    boost::python::object getFunctionParam (boost::python::str FuncID,
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
    boost::python::object getGeneratorParam (boost::python::str UnitClass,
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
    boost::python::object getModelGlobalParam (boost::python::str ParamName);


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
    boost::python::object getObserverParam (boost::python::str ObsID,
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
    boost::python::object getUnitsIDs (boost::python::str UnitClass);


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
    boost::python::object getInputData (boost::python::str UnitClass, int UnitID,
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
    int getDefaultDeltaT ();


// =====================================================================
// =====================================================================


    /*!
     * @brief Sets the default simulation time step.
     * 
     * @param DeltaT
     *    the time step value in seconds
     */
    void setDefaultDeltaT (int DefaultDeltaT);


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
     * @param BYear
     *    the begin date's year
     * @param BMonth
     *    the begin date's month
     * @param BDay
     *    the begin date's day
     * @param BHour
     *    the begin date's hour
     * @param BMinute
     *    the begin date's minute
     * @param BSecond
     *    the begin date's second
     */
    void setPeriodBeginDate (int BYear, int BMonth, int BDay,
                             int BHour, int BMinute, int BSecond);


// =====================================================================
// =====================================================================


    /*!
     * @brief Sets the simulation period end date.
     * 
     * @param EYear
     *    the end date's year
     * @param EMonth
     *    the end date's month
     * @param EDay
     *    the end date's day
     * @param EHour
     *    the end date's hour
     * @param EMinute
     *    the end date's minute
     * @param ESecond
     *    the end date's second
     */
    void setPeriodEndDate (int EYear, int EMonth, int EDay,
                           int EHour, int EMinute, int ESecond);


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
    PyOpenFLUID* runProject (boost::python::str Path);


// =====================================================================
// =====================================================================


    /*!
     * @brief Runs a simulation from a simulation definition class (self).
     * 
     * @return
     *    1 if the simulation runned without problems, 0 otherwise
     */
    unsigned short int runSimulation ();


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
//    PyOpenFLUID* loadResult (boost::python::str UnitClass, int UnitID,
//                               boost::python::str Suffix);


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
//    PyOpenFLUID* loadResultFile (boost::python::str FilePath);


// =====================================================================
/* ------------------------ OTHER FUNCTIONS  ------------------------ */


    /*!
     * @brief Copy all attributs from the parameter in self.
     * 
     * @param InputClass
     *    the PyOpenFLUID class to copy
     */
    void copy (PyOpenFLUID InputClass);


// =====================================================================
// =====================================================================


    /*!
     * @brief Return the internal FluidXDescriptor by reference.
     * 
     * @return 
     *    a reference FluidXDescriptor
     */
    openfluid::fluidx::FluidXDescriptor& getFluidXDescriptor ();


// =====================================================================
// =====================================================================


    /*!
     * @brief Updates output configuration.
     */
    void updateOutputsConfig ();


// =====================================================================
// =====================================================================


  private :
    openfluid::fluidx::FluidXDescriptor m_FXDesc;

};
