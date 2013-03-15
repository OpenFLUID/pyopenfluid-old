#
# CMake environment variable for PyOpenFLUID
#
# Author : Bastien VAYSSE <bastien.vaysse@supagro.inra.fr>
#

# ------ GENERAL ------ #
SET(OUTPUT_PATH "${CMAKE_BINARY_DIR}")
SET(CURRENT_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

SET(PYOPENFLUID_MAIN_NAME "pyopenfluid")
SET(PYOPENFLUID_DISPLAY_NAME "PyOpenFLUID")
SET(PYOPENFLUID_VERSION ${OpenFLUID_VERSION})


# ------ DIRECTORIES ------ #
# "PYOPENFLUID_INPUT_<S>" -> for the main repository
# "<S>_PATH" -> for built and installed repository (relative path)
# "<S>_OUTPUT_PATH" -> for the built repository (absolute path)

SET(PYOPENFLUID_INPUT_RESSOURCE "${CURRENT_PATH}/ressource")
SET(PYOPENFLUID_INPUT_MODULE "${CURRENT_PATH}/module")
SET(PYOPENFLUID_INPUT_SOURCE "${CURRENT_PATH}/src")
SET(PYOPENFLUID_INPUT_DOC "${CURRENT_PATH}/doc")

#TODO remove installation for python
IF (UNIX)
  SET(PYTHON_LIB_PATH       "lib/python${PYTHON_VERSION}")
ELSE (UNIX)
  SET(PYTHON_LIB_PATH       "Lib")
ENDIF (UNIX)
SET(PYTHON_MODULE_PATH      "${PYTHON_LIB_PATH}/site-packages/PyOpenFLUID")
SET(DOC_PATH                "share/doc")
SET(TESTS_OUTPUTS_PATH      "tests-outputs")


# ------ PREFIXS ------ #
SET(BUILD_PREFIX "dist")
SET(BUILD_PATH "${OUTPUT_PATH}/${BUILD_PREFIX}")


# ------ DOCUMENTATION ------ #
SET(CREATE_DOC_HTML YES)
SET(CREATE_DOC_LATEX YES)
SET(CREATE_DOC_MAN YES)


# ------ TESTS FILES ------ #
SET(OPENFLUID_TESTS_PROJECT_1
    "${OpenFLUID_HOME_DIR}/share/doc/openfluid/examples/projects/Primitives")
SET(OPENFLUID_TESTS_FUNCTIONS_PATH
    "${OpenFLUID_HOME_DIR}/${FUNCTIONS_PLUGINS_STDDIR}")
SET(OPENFLUID_TESTS_OBSERVERS_PATH
    "${OpenFLUID_HOME_DIR}/${OBSERVERS_PLUGINS_STDDIR}")
