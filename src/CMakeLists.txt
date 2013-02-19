SET(pyopenfluid_source
    Wrapper.cpp
    PyOpenFLUID.hpp          PyOpenFLUID.cpp
    PyOpenFLUIDError.hpp     PyOpenFLUIDError.cpp
    Convert.hpp              Convert.cpp)

ADD_LIBRARY(PyOpenFLUID SHARED ${pyopenfluid_source})

TARGET_LINK_LIBRARIES(PyOpenFLUID
    ${Boost_LIBRARIES}
    ${PYTHON_LIBRARIES}
    ${OpenFLUID_LIBRARIES})

# it makes the full name : "_pyopenfluid"
SET_TARGET_PROPERTIES(PyOpenFLUID PROPERTIES
  OUTPUT_NAME "pyopenfluid" 
  PREFIX "_"
)
