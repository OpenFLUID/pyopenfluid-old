#
# CMake build for PyOpenFLUID
#
# Author : Bastien VAYSSE <bastien.vaysse@supagro.inra.fr>
#

# include all functions infos
INCLUDE(DocStrings.cmake)

STRING(ASCII 35 HASH) # '#'
STRING(ASCII 37 POURC) # '%'
STRING(ASCII 38 AMP) # '&'

################################################################################
##############  CREATION OF boost, python AND doxygen DOCSTRINGS  ##############

# prefix for 'PyOpenFLUID.py' (for identation)
SET(DOXYGEN_DOC_PREFIX "    ${HASH} ")

# add a content into a var
# because CMake doesn't provide it (just set new content)
# exemple : 'var += content'
FUNCTION(ADDTOVAR NAMEVAR CONTENT)
  SET(${NAMEVAR} "${${NAMEVAR}}${CONTENT}" PARENT_SCOPE)
ENDFUNCTION()

# escape characters for doxygen
FUNCTION(PREPAREVAR_DOXYGEN NAMEVAR)
  STRING(REPLACE "," "\\," ${NAMEVAR} "${${NAMEVAR}}")
  STRING(REPLACE "${POURC}" "\\${POURC}" ${NAMEVAR} "${${NAMEVAR}}")
  SET(${NAMEVAR} "${${NAMEVAR}}" PARENT_SCOPE)
ENDFUNCTION()

# main function
FUNCTION(ADAPT_ADVANCED_DOCSTRING FUNCTIONNAME)
  # init
  SET(TMPBUFFER_BO "")
  SET(TMPBUFFER_PY "")
  SET(TMPBUFFER_DX "")

  # short/brief description
  SET(DESC_LENGTH -1)
  STRING(LENGTH "${DOCSTRINGRAW_SHORT_DESCRIPTION_${FUNCTIONNAME}}" DESC_LENGTH)
  IF (${DESC_LENGTH} GREATER 0)
    ADDTOVAR(TMPBUFFER_BO "${DOCSTRINGRAW_SHORT_DESCRIPTION_${FUNCTIONNAME}}")
    ADDTOVAR(TMPBUFFER_PY "${DOCSTRINGRAW_SHORT_DESCRIPTION_${FUNCTIONNAME}}")
    ADDTOVAR(TMPBUFFER_DX "\n@brief ${DOCSTRINGRAW_SHORT_DESCRIPTION_${FUNCTIONNAME}}")
  ENDIF (${DESC_LENGTH} GREATER 0)

  # long description and other infos
  SET(DESC_LENGTH -1)
  STRING(LENGTH "${DOCSTRINGRAW_LONG_DESCRIPTION_${FUNCTIONNAME}}" DESC_LENGTH)
  IF (${DESC_LENGTH} GREATER 0)
    ADDTOVAR(TMPBUFFER_BO "\\n\\n${DOCSTRINGRAW_LONG_DESCRIPTION_${FUNCTIONNAME}}")
    ADDTOVAR(TMPBUFFER_PY "\n\n${DOCSTRINGRAW_LONG_DESCRIPTION_${FUNCTIONNAME}}")
    ADDTOVAR(TMPBUFFER_DX "\n ${DOCSTRINGRAW_LONG_DESCRIPTION_${FUNCTIONNAME}}")
  ENDIF (${DESC_LENGTH} GREATER 0)

  # parameters
  SET(PARAMETERS_LENGTH -1)
  STRING(LENGTH "${DOCSTRINGRAW_PARAMETERS_${FUNCTIONNAME}}" PARAMETERS_LENGTH)
  IF (${PARAMETERS_LENGTH} GREATER 0)
    ADDTOVAR(TMPBUFFER_BO "\\n\\nKeyword arguments:")
    ADDTOVAR(TMPBUFFER_PY "\n\nKeyword arguments:")
    ADDTOVAR(TMPBUFFER_DX "\n")
  ENDIF (${PARAMETERS_LENGTH} GREATER 0)
  FOREACH(PARAMETER ${DOCSTRINGRAW_PARAMETERS_${FUNCTIONNAME}})
    ADDTOVAR(TMPBUFFER_BO "\\n${PARAMETER}")
    ADDTOVAR(TMPBUFFER_PY "\\n${PARAMETER}")
#    PREPAREVAR_DOXYGEN(PARAMETER)
    STRING(REPLACE "--" "  " PARAMETER_DX "${PARAMETER}")
    ADDTOVAR(TMPBUFFER_DX "\n@param ${PARAMETER_DX}")
  ENDFOREACH()

  # optional parameters
  SET(PARAMETERS_LENGTH -1)
  STRING(LENGTH "${DOCSTRINGRAW_OPTIONAL_PARAMETERS_${FUNCTIONNAME}}" PARAMETERS_LENGTH)
  IF (${PARAMETERS_LENGTH} GREATER 0)
    ADDTOVAR(TMPBUFFER_BO "\\n\\nOptional arguments:")
    ADDTOVAR(TMPBUFFER_PY "\n\nOptional arguments:")
    ADDTOVAR(TMPBUFFER_DX "\n\n@StartOptionalParam")
  ENDIF (${PARAMETERS_LENGTH} GREATER 0)
  FOREACH(PARAMETER ${DOCSTRINGRAW_OPTIONAL_PARAMETERS_${FUNCTIONNAME}})
    ADDTOVAR(TMPBUFFER_BO "\\n${PARAMETER}")
    ADDTOVAR(TMPBUFFER_PY "\\n${PARAMETER}")
    PREPAREVAR_DOXYGEN(PARAMETER)
    STRING(REPLACE "--" "," PARAMETER_DX "${PARAMETER}")
    ADDTOVAR(TMPBUFFER_DX "\n  @OptionalParam{${PARAMETER_DX}}")
  ENDFOREACH()
  IF (${PARAMETERS_LENGTH} GREATER 0)
    ADDTOVAR(TMPBUFFER_DX "\n@EndOptionalParam")
  ENDIF (${PARAMETERS_LENGTH} GREATER 0)

  # exceptions / errors
  SET(EXCEPTIONS_LENGTH -1)
  STRING(LENGTH "${DOCSTRINGRAW_EXCEPTIONS_${FUNCTIONNAME}}" EXCEPTIONS_LENGTH)
  IF (${EXCEPTIONS_LENGTH} GREATER 0)
    ADDTOVAR(TMPBUFFER_BO "\\n\\nExceptions:")
    ADDTOVAR(TMPBUFFER_PY "\n\nExceptions:")
    ADDTOVAR(TMPBUFFER_DX "\n")
  ENDIF (${EXCEPTIONS_LENGTH} GREATER 0)
  FOREACH(EXCEPTION ${DOCSTRINGRAW_EXCEPTIONS_${FUNCTIONNAME}})
    STRING(REPLACE "PyOpenFLUIDError" "PyOpenFluid.StandardError" EXCEPTION "${EXCEPTION}")
    ADDTOVAR(TMPBUFFER_BO "\\n${EXCEPTION}")
    ADDTOVAR(TMPBUFFER_PY "\\n${EXCEPTION}")
    STRING(REPLACE "--" "  " EXCEPTION_DX "${EXCEPTION}")
    ADDTOVAR(TMPBUFFER_DX "\n@exception ${EXCEPTION_DX}")
  ENDFOREACH()

  # return
  SET(RETURN_LENGTH -1)
  STRING(LENGTH "${DOCSTRINGRAW_RETURN_${FUNCTIONNAME}}" RETURN_LENGTH)
  IF (${RETURN_LENGTH} GREATER 0)
    ADDTOVAR(TMPBUFFER_BO "\\n\\nReturns:\\n${DOCSTRINGRAW_RETURN_${FUNCTIONNAME}}")
    ADDTOVAR(TMPBUFFER_PY "\n\nReturns:\n${DOCSTRINGRAW_RETURN_${FUNCTIONNAME}}")
    ADDTOVAR(TMPBUFFER_DX "\n\n@return ${DOCSTRINGRAW_RETURN_${FUNCTIONNAME}}")
  ENDIF (${RETURN_LENGTH} GREATER 0)

  # example (only boost/python)
  SET(EXAMPLES_LENGTH -1)
  STRING(LENGTH "${DOCSTRINGRAW_EXAMPLES_${FUNCTIONNAME}}" EXAMPLES_LENGTH)
  IF (${EXAMPLES_LENGTH} GREATER 0)
    ADDTOVAR(TMPBUFFER_BO "\\n\\nExamples:\n${DOCSTRINGRAW_EXAMPLES_${FUNCTIONNAME}}")
    ADDTOVAR(TMPBUFFER_PY "\n\nExamples:\n${DOCSTRINGRAW_EXAMPLES_${FUNCTIONNAME}}")
  ENDIF (${EXAMPLES_LENGTH} GREATER 0)

  # finalization
  STRING(REPLACE "\n" "\\n" TMPBUFFER_BO_FINAL "${TMPBUFFER_BO}")
  STRING(REPLACE "\n" "\\n" TMPBUFFER_PY_FINAL "${TMPBUFFER_PY}")
  STRING(REPLACE "\n" "\n${DOXYGEN_DOC_PREFIX}" TMPBUFFER_DX_FINAL "${TMPBUFFER_DX}")

  # settings final global vars
  SET(DOCSTRING_boost_${FUNCTIONNAME} "${TMPBUFFER_BO_FINAL}" CACHE INTERNAL "" FORCE)
  SET(DOCSTRING_python_${FUNCTIONNAME} "${TMPBUFFER_PY_FINAL}" CACHE INTERNAL "" FORCE)
  SET(DOCSTRING_doxygen_${FUNCTIONNAME} "${TMPBUFFER_DX_FINAL}" CACHE INTERNAL "" FORCE)
ENDFUNCTION()

# adapt all functions listed
FOREACH(FUNCTIONNAME ${DOCSTRING_ALL_FUNCTIONS_ADVANCED})
  ADAPT_ADVANCED_DOCSTRING("${FUNCTIONNAME}")
ENDFOREACH()
