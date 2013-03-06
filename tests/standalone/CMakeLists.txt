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




ADD_TEST(ExtraFunctionsPaths_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/ExtraFunctionsPaths_TEST.py)
SET_TESTS_PROPERTIES(ExtraFunctionsPaths_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(ExtraObserversPaths_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/ExtraObserversPaths_TEST.py)
SET_TESTS_PROPERTIES(ExtraObserversPaths_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(ModelGlobalParameter_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/ModelGlobalParameter_TEST.py)
SET_TESTS_PROPERTIES(ModelGlobalParameter_TEST PROPERTIES
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




ADD_TEST(ObserverParameter_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/ObserverParameter_TEST.py")
SET_TESTS_PROPERTIES(ObserverParameter_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(Functions_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/Functions_TEST.py")
SET_TESTS_PROPERTIES(Functions_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(FunctionsParameter_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/FunctionsParameter_TEST.py"
         "${TEST_INPUT_FluidXWriter}")
SET_TESTS_PROPERTIES(FunctionsParameter_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")
