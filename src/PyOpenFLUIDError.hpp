#ifndef __PYOPENFLUIDERROR_HPP_
#define __PYOPENFLUIDERROR_HPP_

#include <Python.h>
#include <string>
#include <exception>


// =====================================================================
// ====================      GENERAL EXCEPTION      ====================


class PyOFException : std::exception
{
  public :

    PyOFException (PyObject* PyExcType = NULL);


// =====================================================================
// =====================================================================


    PyOFException (std::string InputMsg, PyObject* PyExcType = NULL);


// =====================================================================
// =====================================================================


    PyOFException (char* InputMsg, PyObject* PyExcType = NULL);


// =====================================================================
// =====================================================================


    PyOFException (const char* InputMsg, PyObject* PyExcType = NULL);


// =====================================================================
// =====================================================================


    inline virtual ~PyOFException () throw () {};


// =====================================================================
// =====================================================================


    inline const char* what() const throw() { return this->m_Message.c_str(); };


// =====================================================================
// =====================================================================


    inline PyObject* errorType() const { return this->m_Type; };


// =====================================================================
// =====================================================================


  private :
    std::string m_Message;
    PyObject* m_Type;
};


// =====================================================================
// ===================      TRANSLATOR EXCEPTION      ==================


void TranslatePyOFException (const PyOFException& e);

#endif // __PYOPENFLUIDERROR_HPP_
