SET(OUTPUT_SOURCE_PATH "${OUTPUT_PATH}/src")

# preparation
SET(pyopenfluid_raw_source
    Wrapper.hpp
    PyOpenFLUID.hpp          PyOpenFLUID.cpp
    PyOpenFLUIDError.hpp     PyOpenFLUIDError.cpp
    PythonUtilities.hpp      PythonUtilities.cpp)
FOREACH(RAW_SOURCE ${pyopenfluid_raw_source})
  FILE(COPY "${CMAKE_CURRENT_SOURCE_DIR}/${RAW_SOURCE}"
       DESTINATION "${OUTPUT_SOURCE_PATH}")
ENDFOREACH()


## configuration
SET(pyopenfluid_files_config_required
    Wrapper.cpp
    PyOpenFLUIDConstants.hpp)
FOREACH(RAW_SOURCE ${pyopenfluid_files_config_required})
CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/${RAW_SOURCE}.in"
    "${OUTPUT_SOURCE_PATH}/${RAW_SOURCE}" @ONLY)
ENDFOREACH()


## add library
SET(pyopenfluid_files
    Wrapper.cpp              Wrapper.hpp
    PyOpenFLUID.hpp          PyOpenFLUID.cpp
    PyOpenFLUIDError.hpp     PyOpenFLUIDError.cpp
    PythonUtilities.hpp      PythonUtilities.cpp
    PyOpenFLUIDConstants.hpp)
SET(pyopenfluid_source)
FOREACH(READY_SOURCE ${pyopenfluid_files})
    LIST(APPEND pyopenfluid_source "${OUTPUT_SOURCE_PATH}/${READY_SOURCE}")
ENDFOREACH()

ADD_LIBRARY(PyOpenFLUID SHARED ${pyopenfluid_source})

TARGET_LINK_LIBRARIES(PyOpenFLUID
    ${Boost_LIBRARIES}
    ${PYTHON_LIBRARIES}
    ${OpenFLUID_LIBRARIES}
    ${GLIBMM_LIBRARIES}
    ${GTHREAD_LIBRARIES}
    ${LibXML2_LIBRARIES})

# it makes the full name : "_pyopenfluid"
SET_TARGET_PROPERTIES(PyOpenFLUID PROPERTIES
  OUTPUT_NAME "pyopenfluid" 
  PREFIX "_"
  LINK_FLAGS "-Wl,--no-undefined"
  LIBRARY_OUTPUT_DIRECTORY "${PYTHON_OUTPUT_SRC_PATH}"
)
