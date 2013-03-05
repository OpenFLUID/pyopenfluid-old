SET(pyopenfluid_source
    Wrapper.cpp
    PyOpenFLUID.hpp          PyOpenFLUID.cpp
    PyOpenFLUIDError.hpp     PyOpenFLUIDError.cpp
    PythonUtilities.hpp      PythonUtilities.cpp)

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
)
