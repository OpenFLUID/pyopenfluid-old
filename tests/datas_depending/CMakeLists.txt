SET(BASE_RESSOURCE_INPUT "/home/vaysseb/Téléchargements/openfluid/resources/tests/datasets")

SET(RESSOURCE_INPUT_Generators "${BASE_RESSOURCE_INPUT}/OPENFLUID.IN.Generators")
SET(RESSOURCE_INPUT_FluidXWriter "${BASE_RESSOURCE_INPUT}/OPENFLUID.IN.FluidXWriter")

SET(RESSOURCE_PROJECT "${BASE_RESSOURCE_INPUT}")




ADD_TEST(OpenDataset_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/OpenDataset_TEST.py
         ${RESSOURCE_INPUT_Generators}
         ${RESSOURCE_INPUT_FluidXWriter})
SET_TESTS_PROPERTIES(OpenDataset_TEST PROPERTIES
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(OpenProject_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/OpenProject_TEST.py
         ${RESSOURCE_PROJECT})
SET_TESTS_PROPERTIES(OpenProject_TEST PROPERTIES
                     DEPENDS OpenDataset_TEST
                     WILL_FAIL TRUE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(FunctionsParameter_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/FunctionsParameter_TEST.py
         ${RESSOURCE_INPUT_FluidXWriter})
SET_TESTS_PROPERTIES(FunctionsParameter_TEST PROPERTIES
                     DEPENDS OpenDataset_TEST
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(GeneratorParameter_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorParameter_TEST.py
         ${RESSOURCE_INPUT_Generators})
SET_TESTS_PROPERTIES(GeneratorParameter_TEST PROPERTIES
                     DEPENDS OpenDataset_TEST
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(InputData_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/InputData_TEST.py
         ${RESSOURCE_INPUT_FluidXWriter})
SET_TESTS_PROPERTIES(InputData_TEST PROPERTIES
                     DEPENDS OpenDataset_TEST
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(UnitsClasses_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/UnitsClasses_TEST.py
         ${RESSOURCE_INPUT_FluidXWriter})
SET_TESTS_PROPERTIES(UnitsClasses_TEST PROPERTIES
                     DEPENDS OpenDataset_TEST
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")




ADD_TEST(UnitsIDs_TEST
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/UnitsIDs_TEST.py
         ${RESSOURCE_INPUT_FluidXWriter})
SET_TESTS_PROPERTIES(UnitsIDs_TEST PROPERTIES
                     DEPENDS OpenDataset_TEST
                     WILL_FAIL FALSE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")
