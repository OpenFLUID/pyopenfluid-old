<<<<<<< HEAD
#
# CMake environment variable for PyOpenFLUID
#
# Author : Bastien VAYSSE <bastien.vaysse@supagro.inra.fr>
#

=======
>>>>>>> b967a700084551510a01146bf1d7abf461e7edf8
SET(PY_DIR "${PYTHON_MODULE_OUTPUT_PATH}:${CMAKE_CURRENT_SOURCE_DIR}")
SET(TEST_PATH "${TEST_OUTPUT_PATH}")

# binary paths
SET(TEST_RESSOURCE_FUNCTIONS "${OPENFLUID_TESTS_FUNCTIONS_PATH}")
SET(TEST_RESSOURCE_OBSERVERS "${OPENFLUID_TESTS_OBSERVERS_PATH}")
<<<<<<< HEAD
=======

# macro - create a copy of openfluid projet path
MACRO(CreateOFRepository SOURCE FINALPATH)
  FILE(MAKE_DIRECTORY "${FINALPATH}")
  FILE(MAKE_DIRECTORY "${FINALPATH}/IN")
  FILE(MAKE_DIRECTORY "${FINALPATH}/OUT")
  FILE(COPY "${SOURCE}" DESTINATION "${FINALPATH}")
ENDMACRO(CreateOFRepository)

# output projects path
SET(TEST_PATH_PROJECT_1        "${TEST_PATH}/project_1")
SET(TEST_INPUT_PATH_PROJECT_1  "${TEST_PATH}/project_1/IN")
SET(TEST_OUTPUT_PATH_PROJECT_1 "${TEST_PATH}/project_1/OUT")

# input projects path (use read-only)
CreateOFRepository("${OPENFLUID_TESTS_PROJECT_1}" "${TEST_PATH_PROJECT_1}")
>>>>>>> b967a700084551510a01146bf1d7abf461e7edf8

# macro - create a copy of openfluid projet path
MACRO(CreateOFRepository SOURCE FINALPATH FINALNAME)
  FILE(COPY "${SOURCE}" DESTINATION "${FINALPATH}")
  GET_FILENAME_COMPONENT(SOURCENAME ${SOURCE} NAME CACHE)
  FILE(RENAME "${FINALPATH}/${SOURCENAME}"
       "${FINALPATH}/${FINALNAME}")
  FILE(MAKE_DIRECTORY "${FINALPATH}/${FINALNAME}")
  FILE(MAKE_DIRECTORY "${FINALPATH}/${FINALNAME}/IN")
  FILE(MAKE_DIRECTORY "${FINALPATH}/${FINALNAME}/OUT")
ENDMACRO(CreateOFRepository)

# output projects path
SET(PROJECT_NAME_1        "project_1")

# input projects path (use read-only)
CreateOFRepository("${OPENFLUID_TESTS_PROJECT_1}" "${TEST_PATH}" "${PROJECT_NAME_1}")

##
ADD_TEST(TestOfTestUnit
         ${PYTHON_EXECUTABLE}
         "${CMAKE_CURRENT_SOURCE_DIR}/TestOfTestUnit.py")
SET_TESTS_PROPERTIES(TestOfTestUnit PROPERTIES
                     WILL_FAIL TRUE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")

#
ADD_SUBDIRECTORY(standalone)

ADD_SUBDIRECTORY(datas_depending)
