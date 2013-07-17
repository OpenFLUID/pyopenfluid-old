#include "PyOpenFLUIDError.hpp"

// =====================================================================
// ====================      GENERAL EXCEPTION      ====================


PyApplicationException::PyApplicationException (PyObject* PyExcType /*= NULL*/)
{
  this->m_Message = std::string("");
  this->m_Type = PyExcType;
}


// =====================================================================
// =====================================================================


PyApplicationException::PyApplicationException (std::string InputMsg, PyObject* PyExcType)
{
  this->m_Message = InputMsg;
  this->m_Type = PyExcType;
}


// =====================================================================
// =====================================================================


PyApplicationException::PyApplicationException (char* InputMsg, PyObject* PyExcType)
{
  this->m_Message = std::string(InputMsg);
  this->m_Type = PyExcType;
}


// =====================================================================
// =====================================================================


PyApplicationException::PyApplicationException (const char* InputMsg, PyObject* PyExcType)
{
  this->m_Message = std::string(InputMsg);
  this->m_Type = PyExcType;
}


// =====================================================================
// ===================      TRANSLATOR EXCEPTION      ==================


void TranslatePyApplicationException (const PyApplicationException& e)
{
  // Use the Python 'C' API to set up an exception object
  // if type error is specified
  if (e.errorType() != NULL)
    PyErr_SetString(e.errorType(), e.what());
  // else : exception PyOpenFLUID (with StandardError indicated users
  // which error is it)
  else
  {
    const char* name = "PyOpenFluid.StandardError";
    PyObject* myException = PyErr_NewException((char*)name,
        PyExc_StandardError, NULL);
    PyErr_SetString(myException, e.what());
  }
}
