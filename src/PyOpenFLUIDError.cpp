#include <Python.h>
#include <string>
#include <exception>
#include "PyOpenFLUIDError.hpp"

// =====================================================================
// ====================      GENERAL EXCEPTION      ====================


PyOFException::PyOFException (PyObject* PyExcType /*= NULL*/)
{
  this->m_Message = std::string("");
  this->m_Type = PyExcType;
}


// =====================================================================
// =====================================================================


PyOFException::PyOFException (std::string InputMsg, PyObject* PyExcType)
{
  this->m_Message = InputMsg;
  this->m_Type = PyExcType;
}


// =====================================================================
// =====================================================================


PyOFException::PyOFException (char* InputMsg, PyObject* PyExcType)
{
  this->m_Message = std::string(InputMsg);
  this->m_Type = PyExcType;
}


// =====================================================================
// =====================================================================


PyOFException::PyOFException (const char* InputMsg, PyObject* PyExcType)
{
  this->m_Message = std::string(InputMsg);
  this->m_Type = PyExcType;
}


// =====================================================================
// ===================      TRANSLATOR EXCEPTION      ==================


void TranslatePyOFException (const PyOFException& e)
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


// =====================================================================
// =====================================================================


//void TranslatePyOFExc_TypeError (const PyOFExc_TypeError& e)
//{
//  PyErr_SetString(PyExc_TypeError, e.what());
//}
