#include <boost/python.hpp>
#include <boost/exception/all.hpp>
#include <exception>
#include "PyOpenFLUIDError.hpp"

// =====================================================================
// =====================================================================


PyOFException::PyOFException ()
{
  this->m_Message = new std::string("");
}


// =====================================================================
// =====================================================================


PyOFException::PyOFException (std::string* input)
{
  this->m_Message = input;
}


// =====================================================================
// =====================================================================


PyOFException::PyOFException (char* input)
{
  this->m_Message = new std::string(input);
}


// =====================================================================
// =====================================================================


PyOFException::PyOFException (const char* input)
{
  this->m_Message = new std::string(input);
}


// =====================================================================
// =====================================================================


PyOFException::~PyOFException () throw ()
{
  if (this->m_Message != NULL)
    delete this->m_Message;
}


// =====================================================================
// =====================================================================


const char* PyOFException::what() const throw()
{
  return this->m_Message->c_str();
}


// =====================================================================
// =====================================================================


void TranslatePyOFException (const PyOFException& e)
{
  // Use the Python 'C' API to set up an exception object
  const char* name = "PyOpenFluid.PyOFError";
  PyObject* myException = PyErr_NewException((char*)name,
      PyExc_RuntimeError, NULL);
  PyErr_SetString(PyExc_RuntimeError, e.what());
}
