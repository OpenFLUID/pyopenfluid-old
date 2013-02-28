SET(pyopenfluid_script
    __init__.py
    PyOpenFLUID.py)

# copy PyOpenFLUID module (python files) of the library
ADD_CUSTOM_TARGET(PyOpenFLUID_File_Copy ALL)
FOREACH(script ${pyopenfluid_script})
  ADD_CUSTOM_COMMAND(TARGET PyOpenFLUID_File_Copy POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy "${PYOPENFLUID_INPUT_MODULE}/${script}"
    ${PYTHON_MODULE_OUTPUT_PATH}
  VERBATIM
  )
ENDFOREACH(script)
