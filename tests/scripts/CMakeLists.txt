#
# CMake environment variable for PyOpenFLUID
#
# Author : Bastien VAYSSE <bastien.vaysse@supagro.inra.fr>
#


# =============================================================================
# =============================  NO NEEDS OF DATAS ============================

ADD_TEST(Version_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/Version_TEST.py)
SET_TESTS_PROPERTIES(Version_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(BeginPeriodDate_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/BeginPeriodDate_TEST.py)
SET_TESTS_PROPERTIES(BeginPeriodDate_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(EndPeriodDate_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/EndPeriodDate_TEST.py)
SET_TESTS_PROPERTIES(EndPeriodDate_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(DefaultDeltaT_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/DefaultDeltaT_TEST.py)
SET_TESTS_PROPERTIES(DefaultDeltaT_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(ExtraSimulatorsPaths_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/ExtraSimulatorsPaths_TEST.py)
SET_TESTS_PROPERTIES(ExtraSimulatorsPaths_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(ExtraObserversPaths_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/ExtraObserversPaths_TEST.py)
SET_TESTS_PROPERTIES(ExtraObserversPaths_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(ModelGlobalParameters_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/ModelGlobalParameters_TEST.py)
SET_TESTS_PROPERTIES(ModelGlobalParameters_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(OutputDir_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/OutputDir_TEST.py)
SET_TESTS_PROPERTIES(OutputDir_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(PrintSimulationInfo_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/PrintSimulationInfo_TEST.py)
SET_TESTS_PROPERTIES(PrintSimulationInfo_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(Observer_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/Observer_TEST.py")
SET_TESTS_PROPERTIES(Observer_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(ObserverParameters_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/ObserverParameters_TEST.py")
SET_TESTS_PROPERTIES(ObserverParameters_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(Simulators_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/Simulators_TEST.py")
SET_TESTS_PROPERTIES(Simulators_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(SimulatorParameters_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/SimulatorParameters_TEST.py")
SET_TESTS_PROPERTIES(SimulatorParameters_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(Units_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/Units_TEST.py")
SET_TESTS_PROPERTIES(Units_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(UnitsParentsChildren_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/UnitsParentsChildren_TEST.py")
SET_TESTS_PROPERTIES(UnitsParentsChildren_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(UnitsFromsTos_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/UnitsFromsTos_TEST.py")
SET_TESTS_PROPERTIES(UnitsFromsTos_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(Attribute_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/Attribute_TEST.py")
SET_TESTS_PROPERTIES(Attribute_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(UnitsIDsClasses_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/UnitsIDsClasses_TEST.py")
SET_TESTS_PROPERTIES(UnitsIDsClasses_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




SET(DATASETTEST_NAME "cmd_dataset")
FILE(MAKE_DIRECTORY "${TEST_PATH}/${DATASETTEST_NAME}")
ADD_TEST(Dataset_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/Dataset_TEST.py"
         "--dataset" "${TEST_PATH}/${DATASETTEST_NAME}/IN")
SET_TESTS_PROPERTIES(Dataset_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




SET(PROJECTTEST_NAME "cmd_project")
ADD_TEST(Project_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/Project_TEST.py"
         "--project" "${TEST_PATH}/${PROJECTTEST_NAME}")
SET_TESTS_PROPERTIES(Project_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")



# =============================================================================
# =========================  NEEDS DATASET OR PROJECT =========================

ADD_TEST(GeneratorParameters_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/GeneratorParameters_TEST.py"
         "--dataset" "${TEST_PATH}/${PROJECT_NAME_1}/IN")
SET_TESTS_PROPERTIES(GeneratorParameters_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(ModelItems_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/ModelItems_TEST.py"
         "--dataset" "${TEST_PATH}/${PROJECT_NAME_1}/IN")
SET_TESTS_PROPERTIES(ModelItems_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(RunProject_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/RunProject_TEST.py"
         "--project" "${TEST_PATH}/${RUNPROJECT_NAME}")
SET_TESTS_PROPERTIES(RunProject_TEST PROPERTIES
                     DEPENDS RunSimulation_TEST
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(RunSimulation_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/RunSimulation_TEST.py"
         "--project" "${TEST_PATH}/${RUNSIMULATION_NAME}")
SET_TESTS_PROPERTIES(RunSimulation_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(Results_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/Results_TEST.py"
         "--project" "${TEST_PATH}/${RESULTS_NAME}")
SET_TESTS_PROPERTIES(Results_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")
