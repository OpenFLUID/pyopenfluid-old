ADD_TEST(OpenDataset_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/OpenDataset_TEST.py"
         "${TEST_INPUT_Generators}"
         "${TEST_INPUT_FluidXWriter}")
SET_TESTS_PROPERTIES(OpenDataset_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(OpenProject_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/OpenProject_TEST.py"
         "${TEST_OUTPUT_PROJECT_A}")
SET_TESTS_PROPERTIES(OpenProject_TEST PROPERTIES
                     DEPENDS OpenDataset_TEST
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(RunProject_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/RunProject_TEST.py"
         "${TEST_OUTPUT_PROJECT_A}"
         "${TEST_RESSOURCE_FUNCTIONS}"
         "${TEST_RESSOURCE_GENERATORS}")
SET_TESTS_PROPERTIES(RunProject_TEST PROPERTIES
                     DEPENDS OpenDataset_TEST
                     DEPENDS RunSimulation_TEST
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(RunSimulation_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/RunSimulation_TEST.py"
         "${TEST_INPUT_Generators}"
         "${TEST_RESSOURCE_FUNCTIONS}"
         "${TEST_RESSOURCE_GENERATORS}")
SET_TESTS_PROPERTIES(RunSimulation_TEST PROPERTIES
                     DEPENDS OpenDataset_TEST
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(GeneratorParameter_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/GeneratorParameter_TEST.py"
         "${TEST_INPUT_Generators}")
SET_TESTS_PROPERTIES(GeneratorParameter_TEST PROPERTIES
                     DEPENDS OpenDataset_TEST
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(UnitsClasses_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/UnitsClasses_TEST.py"
         "${TEST_INPUT_FluidXWriter}")
SET_TESTS_PROPERTIES(UnitsClasses_TEST PROPERTIES
                     DEPENDS OpenDataset_TEST
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(UnitsIDs_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/UnitsIDs_TEST.py"
         "${TEST_INPUT_FluidXWriter}")
SET_TESTS_PROPERTIES(UnitsIDs_TEST PROPERTIES
                     DEPENDS OpenDataset_TEST
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")
