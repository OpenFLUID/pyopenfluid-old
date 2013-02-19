SET(PY_DIR "${PYTHON_LIB_OUTPUT_PATH}:${PYTHON_LIBDYNLOAD_OUTPUT_PATH}")

SET(PyOpenFLUID_tests
    DefaultDeltaT_TEST.py
    ExtraFunctionsPaths_TEST.py
    FunctionsParameter_TEST.py
    GeneratorParameter_TEST.py
    InputData_TEST.py
    ModelGlobalParameter_TEST.py
    PeriodDate_TEST.py
    Project_TEST.py
    Results_TEST.py
    Simulation_TEST.py
    UnitsClasses_TEST.py
    UnitsIDs_TEST.py
    Version_TEST.py
    )

FOREACH(TEST ${PyOpenFLUID_tests})
    ADD_TEST(${TEST} ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/${TEST})
    SET_TESTS_PROPERTIES(${TEST} PROPERTIES
                         WILL_FAIL FALSE
                         ENVIRONMENT "PYTHONPATH=${PY_DIR}") 
ENDFOREACH()
