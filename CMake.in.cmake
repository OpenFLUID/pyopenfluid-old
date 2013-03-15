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

SET(PYOPENFLUID_MAJOR_VERSION "1")
SET(PYOPENFLUID_MINOR_VERSION "0")
SET(PYOPENFLUID_PATCH_VERSION "0")
SET(PYOPENFLUID_STATUS_VERSION "alpha")
SET(PYOPENFLUID_VERSION "${PYOPENFLUID_MAJOR_VERSION}.${PYOPENFLUID_MINOR_VERSION}.${PYOPENFLUID_PATCH_VERSION}~${PYOPENFLUID_STATUS_VERSION}")


SET(PYOPENFLUID_LICENCE "GPLv3")
SET(PYOPENFLUID_SHORT_DESCRIPTION "This module allows to load, parameterize, run and analyse OpenFLUID simulations within the Python 2.x environment.")
SET(PYOPENFLUID_LONG_DESCRIPTION "This module allows to load, parameterize, run and analyse OpenFLUID simulations within the Python 2.x environment. (long version)")
SET(PYOPENFLUID_AUTHORS_LIST "Bastien VAYSSE")
SET(PYOPENFLUID_EMAIL_LIST "bastien.vaysse@supagro.inra.fr")
SET(PYOPENFLUID_MAINTAINER "Bastien VAYSSE")
SET(PYOPENFLUID_EMAIL_MAINTAINER "bastien.vaysse@supagro.inra.fr")
SET(PYOPENFLUID_URL "http://www.openfluid-project.org/openfluid/community/index.php/Main_Page")


# ------ DIRECTORIES ------ #
# "PYOPENFLUID_INPUT_<S>" -> for the main repository
# "<S>_PATH" -> for built and installed repository (relative path)
# "<S>_OUTPUT_PATH" -> for the built repository (absolute path)

SET(PYOPENFLUID_INPUT_RESSOURCE "${CURRENT_PATH}/ressource")
SET(PYOPENFLUID_INPUT_MODULE "${CURRENT_PATH}/module")
SET(PYOPENFLUID_INPUT_SOURCE "${CURRENT_PATH}/src")
SET(PYOPENFLUID_INPUT_DOC "${CURRENT_PATH}/doc")

#TODO remove installation later for python official installer
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
