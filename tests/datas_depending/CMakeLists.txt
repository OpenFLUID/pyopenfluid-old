#
# CMake environment variable for PyOpenFLUID
#
# Author : Bastien VAYSSE <bastien.vaysse@supagro.inra.fr>
#

ADD_TEST(OpenProject_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/OpenProject_TEST.py"
         "--project" "${TEST_PATH}/${PROJECT_NAME_1}"
         "--output" "${TEST_PATH}/${PROJECT_NAME_1}/OUT")
SET_TESTS_PROPERTIES(OpenProject_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




SET(RUNPROJECT_NAME "cmd_runproject")
CreateOFRepository("${OPENFLUID_TESTS_PROJECT_1}" "${TEST_PATH}" "${RUNPROJECT_NAME}")

ADD_TEST(RunProject_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/RunProject_TEST.py"
         "--project" "${TEST_PATH}/${RUNPROJECT_NAME}")
SET_TESTS_PROPERTIES(RunProject_TEST PROPERTIES
                     DEPENDS RunSimulation_TEST
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




SET(RUNSIMULATION_NAME "cmd_runsimulation")
CreateOFRepository("${OPENFLUID_TESTS_PROJECT_1}" "${TEST_PATH}" "${RUNSIMULATION_NAME}")

ADD_TEST(RunSimulation_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/RunSimulation_TEST.py"
         "--dataset" "${TEST_PATH}/${RUNSIMULATION_NAME}/IN"
         "--output" "${TEST_PATH}/${RUNSIMULATION_NAME}/OUT")
SET_TESTS_PROPERTIES(RunSimulation_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(GeneratorParameter_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/GeneratorParameter_TEST.py"
         "--dataset" "${TEST_PATH}/${PROJECT_NAME_1}/IN"
         "--output" "${TEST_PATH}/${PROJECT_NAME_1}/OUT")
SET_TESTS_PROPERTIES(GeneratorParameter_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(UnitsClasses_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/UnitsClasses_TEST.py"
         "--dataset" "${TEST_PATH}/${PROJECT_NAME_1}/IN"
         "--output" "${TEST_PATH}/${PROJECT_NAME_1}/OUT")
SET_TESTS_PROPERTIES(UnitsClasses_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(UnitsIDs_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/UnitsIDs_TEST.py"
         "--dataset" "${TEST_PATH}/${PROJECT_NAME_1}/IN"
         "--output" "${TEST_PATH}/${PROJECT_NAME_1}/OUT")
SET_TESTS_PROPERTIES(UnitsIDs_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")
