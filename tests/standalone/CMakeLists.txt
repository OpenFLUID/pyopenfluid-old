SET(PyOpenFLUID_SA_tests
    BeginPeriodDate_TEST.py
    DefaultDeltaT_TEST.py
    EndPeriodDate_TEST.py
    ExtraFunctionsPaths_TEST.py
    ExtraObserversPaths_TEST.py
    ModelGlobalParameter_TEST.py
    OutputDir_TEST.py
    PrintSimulationInfo_TEST.py
    Version_TEST.py
    )

FOREACH(TEST ${PyOpenFLUID_SA_tests})
    ADD_TEST(${TEST} ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/${TEST})
    SET_TESTS_PROPERTIES(${TEST} PROPERTIES
                         WILL_FAIL FALSE
                         ENVIRONMENT "PYTHONPATH=${PY_DIR}") 
ENDFOREACH()
