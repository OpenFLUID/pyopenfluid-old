ADD_TEST(OpenDataset_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/OpenDataset_TEST.py"
         "--dataset" "${TEST_INPUT_PATH_PROJECT_1}/IN"
         "--output" "${TEST_OUTPUT_PATH_PROJECT_1}")
SET_TESTS_PROPERTIES(OpenDataset_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(OpenProject_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/OpenProject_TEST.py"
         "--project" "${TEST_INPUT_PATH_PROJECT_1}"
         "--output" "${TEST_OUTPUT_PATH_PROJECT_1}")
SET_TESTS_PROPERTIES(OpenProject_TEST PROPERTIES
                     DEPENDS OpenDataset_TEST
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




SET(TEST_RUNPROJECT_PATH "${TEST_PATH}/cmd_runproject")
CreateOFRepository("${OPENFLUID_TESTS_PROJECT_1}" "${TEST_RUNPROJECT_PATH}")

ADD_TEST(RunProject_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/RunProject_TEST.py"
         "--project" "${TEST_RUNPROJECT_PATH}"
         "--funpath" "${TEST_RESSOURCE_FUNCTIONS}"
         "--obspath" "${TEST_RESSOURCE_OBSERVERS}")
SET_TESTS_PROPERTIES(RunProject_TEST PROPERTIES
                     DEPENDS OpenDataset_TEST
                     DEPENDS RunSimulation_TEST
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(RunSimulation_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/RunSimulation_TEST.py"
         "--dataset" "${TEST_INPUT_PATH_PROJECT_1}/IN"
         "--output" "${TEST_OUTPUT_PATH_PROJECT_1}"
         "--funpath" "${TEST_RESSOURCE_FUNCTIONS}"
         "--obspath" "${TEST_RESSOURCE_OBSERVERS}")
SET_TESTS_PROPERTIES(RunSimulation_TEST PROPERTIES
                     DEPENDS OpenDataset_TEST
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(GeneratorParameter_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/GeneratorParameter_TEST.py"
         "--dataset" "${TEST_INPUT_PATH_PROJECT_1}/IN"
         "--output" "${TEST_OUTPUT_PATH_PROJECT_1}")
SET_TESTS_PROPERTIES(GeneratorParameter_TEST PROPERTIES
                     DEPENDS OpenDataset_TEST
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(UnitsClasses_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/UnitsClasses_TEST.py"
         "--dataset" "${TEST_INPUT_PATH_PROJECT_1}/IN"
         "--output" "${TEST_OUTPUT_PATH_PROJECT_1}")
SET_TESTS_PROPERTIES(UnitsClasses_TEST PROPERTIES
                     DEPENDS OpenDataset_TEST
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(UnitsIDs_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/UnitsIDs_TEST.py"
         "--dataset" "${TEST_INPUT_PATH_PROJECT_1}/IN"
         "--output" "${TEST_OUTPUT_PATH_PROJECT_1}")
SET_TESTS_PROPERTIES(UnitsIDs_TEST PROPERTIES
                     DEPENDS OpenDataset_TEST
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")
