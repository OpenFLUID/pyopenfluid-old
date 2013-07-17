#ifndef __PYOPENFLUIDERROR_HPP_
#define __PYOPENFLUIDERROR_HPP_

#include <Python.h>
#include <string>
#include <exception>

#define HANDLE_EXCEPTION \
catch (openfluid::base::Exception& E) \
{ \
  throw PyApplicationException(E.what()); \
} \
catch (std::bad_alloc& E) \
{ \
  throw PyApplicationException(std::string("MEMORY ALLOCATION ERROR, ") \
      + std::string(E.what()) \
      + std::string(". Possibly not enough memory available"), \
      PyExc_MemoryError); \
} \
catch (PyApplicationException& E) \
{ \
  throw E; \
} \
catch (std::exception& E) \
{ \
  throw PyApplicationException(std::string("SYSTEM ERROR, ") + std::string(E.what()), \
      PyExc_SystemError); \
} \
catch (...) \
{ \
  throw PyApplicationException("UNKNOWN ERROR", PyExc_RuntimeError); \
}


#define HANDLE_APPLICATIONEXCEPTION \
catch (openfluid::base::ApplicationException& E) \
{ \
  throw PyApplicationException(E.what()); \
}


#define WARNING_EXCEPTION \
catch (openfluid::base::Exception& E) \
{ \
  pyopenfluid::topython::printWarning(E.what()); \
}


// =====================================================================
// ====================      GENERAL EXCEPTION      ====================


class PyApplicationException : std::exception
{
  public :

    PyApplicationException (PyObject* PyExcType = NULL);


// =====================================================================
// =====================================================================


    PyApplicationException (std::string InputMsg, PyObject* PyExcType = NULL);


// =====================================================================
// =====================================================================


    PyApplicationException (char* InputMsg, PyObject* PyExcType = NULL);


// =====================================================================
// =====================================================================


    PyApplicationException (const char* InputMsg, PyObject* PyExcType = NULL);


// =====================================================================
// =====================================================================


    inline virtual ~PyApplicationException () throw () {};


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
// ===================      EXCEPTION TRANSLATOR     ===================


void TranslatePyApplicationException (const PyApplicationException& e);

#endif // __PYOPENFLUIDERROR_HPP_
