# preparation
SET(pyopenfluid_raw_source
    Wrapper.cpp              Wrapper.hpp
    PyOpenFLUID.hpp          PyOpenFLUID.cpp
    PyOpenFLUIDError.hpp     PyOpenFLUIDError.cpp
    PythonUtilities.hpp      PythonUtilities.cpp)

SET(OUTPUT_SOURCE_PATH "${OUTPUT_PATH}/src")

FOREACH(RAW_SOURCE ${pyopenfluid_raw_source})
  FILE(COPY "${CMAKE_CURRENT_SOURCE_DIR}/${RAW_SOURCE}"
       DESTINATION "${OUTPUT_SOURCE_PATH}")
ENDFOREACH()

# configuration
CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/PyOpenFLUIDConstants.hpp.in"
    "${OUTPUT_SOURCE_PATH}/PyOpenFLUIDConstants.hpp" @ONLY)

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
)
