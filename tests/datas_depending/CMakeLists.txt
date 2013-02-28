SET(RESSOURCE_PROJECT_A "${PYOPENFLUID_INPUT_RESSOURCE}/project_A")
SET(RESSOURCE_PROJECT_B "${PYOPENFLUID_INPUT_RESSOURCE}/project_B")

SET(RESSOURCE_INPUT_A "${RESSOURCE_PROJECT_A}/IN")
SET(RESSOURCE_INPUT_B "${RESSOURCE_PROJECT_B}/IN")



ADD_TEST(OpenDataset_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/OpenDataset_TEST.py
         ${RESSOURCE_INPUT_A}
         ${RESSOURCE_INPUT_B})
SET_TESTS_PROPERTIES(OpenDataset_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(OpenProject_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/OpenProject_TEST.py
         ${RESSOURCE_PROJECT_A})
SET_TESTS_PROPERTIES(OpenProject_TEST PROPERTIES
                     DEPENDS OpenDataset_TEST
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(FunctionsParameter_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/FunctionsParameter_TEST.py
         ${RESSOURCE_INPUT_A})
SET_TESTS_PROPERTIES(FunctionsParameter_TEST PROPERTIES
                     DEPENDS OpenDataset_TEST
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(GeneratorParameter_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorParameter_TEST.py
         ${RESSOURCE_INPUT_B})
SET_TESTS_PROPERTIES(GeneratorParameter_TEST PROPERTIES
                     DEPENDS OpenDataset_TEST
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(InputData_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/InputData_TEST.py
         ${RESSOURCE_INPUT_A})
SET_TESTS_PROPERTIES(InputData_TEST PROPERTIES
                     DEPENDS OpenDataset_TEST
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(UnitsClasses_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/UnitsClasses_TEST.py
         ${RESSOURCE_INPUT_A})
SET_TESTS_PROPERTIES(UnitsClasses_TEST PROPERTIES
                     DEPENDS OpenDataset_TEST
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(UnitsIDs_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/UnitsIDs_TEST.py
         ${RESSOURCE_INPUT_A})
SET_TESTS_PROPERTIES(UnitsIDs_TEST PROPERTIES
                     DEPENDS OpenDataset_TEST
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")
