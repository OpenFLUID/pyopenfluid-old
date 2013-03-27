#
# CMake environment variable for PyOpenFLUID
#
# Author : Bastien VAYSSE <bastien.vaysse@supagro.inra.fr>
#

ADD_TEST(GeneratorParameter_TEST
         "${PYTHON_EXECUTABLE}"
         "${CMAKE_CURRENT_SOURCE_DIR}/GeneratorParameter_TEST.py"
         "--dataset" "${TEST_PATH}/${PROJECT_NAME_1}/IN"
         "--output" "${TEST_PATH}/${PROJECT_NAME_1}/OUT")
SET_TESTS_PROPERTIES(GeneratorParameter_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")
