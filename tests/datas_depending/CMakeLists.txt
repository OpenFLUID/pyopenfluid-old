#
# CMake environment variable for PyOpenFLUID
#
# Author : Bastien VAYSSE <bastien.vaysse@supagro.inra.fr>
#

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
