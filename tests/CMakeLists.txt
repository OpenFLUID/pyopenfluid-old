# TODO: erase first and second path when install or whenever
SET(PY_DIR "${PYTHON_LIB_OUTPUT_PATH}:${PYTHON_LIBDYNLOAD_OUTPUT_PATH}:${CMAKE_CURRENT_SOURCE_DIR}")

# creation of tests datasets and projects
# datasets
# TODO: replace by openfluid datasets path
SET(RESSOURCE_INPUT "/home/vaysseb/Téléchargements/openfluid/resources/tests/datasets")
# TODO: replace by openfluid binary test ressource
SET(TEST_INPUT_Generators "${RESSOURCE_INPUT}/OPENFLUID.IN.Generators")
SET(TEST_INPUT_FluidXWriter "${RESSOURCE_INPUT}/OPENFLUID.IN.FluidXWriter")

# binary functions
SET(TEST_RESSOURCE_FUNCTIONS "/home/vaysseb/Téléchargements/openfluid/_build/tests-bin")
SET(TEST_RESSOURCE_GENERATORS "/home/vaysseb/Téléchargements/openfluid/_build/tests-bin")

# projects
SET(TEST_OUTPUT_PROJECT_A "${TEST_OUTPUT_PATH}/project_A")
FILE(MAKE_DIRECTORY "${TEST_OUTPUT_PROJECT_A}")
FILE(MAKE_DIRECTORY "${TEST_OUTPUT_PROJECT_A}/OUT")
FILE(MAKE_DIRECTORY "${TEST_OUTPUT_PROJECT_A}/IN")

ADD_CUSTOM_TARGET(Tests_Preparation ALL)
ADD_CUSTOM_COMMAND(TARGET Tests_Preparation POST_BUILD
    COMMAND "${CMAKE_COMMAND}" "-E"
    "copy_directory" "${RESSOURCE_INPUT}/OPENFLUID.IN.FluidXWriter"
    "${TEST_OUTPUT_PROJECT_A}/IN/" VERBATIM)
# TODO: delete this file (project test)
ADD_CUSTOM_COMMAND(TARGET Tests_Preparation POST_BUILD
    COMMAND "${CMAKE_COMMAND}" "-E"
    "copy" "${CMAKE_CURRENT_SOURCE_DIR}/tmp_ressources/.openfluidprj"
    "${TEST_OUTPUT_PROJECT_A}/" VERBATIM)

#
ADD_TEST(TestofTestUnit
         ${PYTHON_EXECUTABLE}
         ${CMAKE_CURRENT_SOURCE_DIR}/TestofTestUnit.py)
SET_TESTS_PROPERTIES(TestofTestUnit PROPERTIES
                     WILL_FAIL TRUE
                     ENVIRONMENT "PYTHONPATH=${PY_DIR}")

#
ADD_SUBDIRECTORY(standalone)

ADD_SUBDIRECTORY(datas_depending)
