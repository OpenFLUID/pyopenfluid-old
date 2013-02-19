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

SET(PYOPENFLUID_INPUT_MODULE "${CURRENT_PATH}/module")
SET(PYOPENFLUID_INPUT_SOURCE "${CURRENT_PATH}/src")
SET(PYOPENFLUID_INPUT_DOC "${CURRENT_PATH}/doc")

SET(PYTHON_LIB_PATH         "lib/python${PYTHON_VERSION}")
SET(PYTHON_LIBDYNLOAD_PATH  "lib/python${PYTHON_VERSION}/lib-dynload")
SET(PYTHON_MODULE_PATH      "lib/python${PYTHON_VERSION}/PyOpenFLUID")
SET(DOC_PATH                "share/doc")

# ------ PREFIXS ------ #
SET(BUILD_PREFIX "dist")
SET(BUILD_PATH "${OUTPUT_PATH}/${BUILD_PREFIX}")


# ------ DOCUMENTATION ------ #
SET(CREATE_DOC_HTML YES)
SET(CREATE_DOC_LATEX YES)
SET(CREATE_DOC_MAN YES)



