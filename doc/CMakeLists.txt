SET(CUSTOM_CSS_DOCUMENTATION_PATH "${PYOPENFLUID_INPUT_DOC}/doxygen_stylesheets.css")

# include files to the documentation
SET(DOC_FILES_INCLUDE
    "${PYTHON_OUTPUT_SRC_PATH}/PyOpenFLUID.py")
# exclude files to the documentation
SET(DOC_FILES_EXCLUDE
    "${PYTHON_OUTPUT_SRC_PATH}/__init__.py")

IF(DOXYGEN)

  CONFIGURE_FILE("${PYOPENFLUID_INPUT_DOC}/Doxyfile.in" "${OUTPUT_PATH}/Doxyfile")

  ADD_CUSTOM_TARGET(PyOpenFLUID_Documentation ALL
      "${DOXYGEN}" "${OUTPUT_PATH}/Doxyfile"
      VERBATIM)

ENDIF(DOXYGEN)
