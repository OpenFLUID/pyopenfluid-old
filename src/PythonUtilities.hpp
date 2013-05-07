#ifndef __PYTHONUTILITIES_HPP__
#define __PYTHONUTILITIES_HPP__
/* standard library c++ */
#include <string>
#include <sstream>
#include <iostream>
/* python */
#include <Python.h>
/* boost.python */
#include <boost/python/str.hpp>
#include <boost/python/dict.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/object.hpp>
#include <boost/python/extract.hpp>


namespace pyopenfluid { 

namespace tools {


std::string stringFill (const std::string Input, const std::string StrFill,
    unsigned int MaxLength);


// =====================================================================
// =====================================================================


std::string zeroFill (const std::string Input, unsigned int MaxLength);

} // tools


// =====================================================================
// =====================================================================


namespace topython {

void printStdOut (std::string& CharMessage, int EOL=0);


// =====================================================================
// =====================================================================


void printStdOut (const char* CharMessage, int EOL=0);


// =====================================================================
// =====================================================================


void printStdOut (std::stringstream& StringStream, int EOL=0);


// =====================================================================
// =====================================================================


void printStdOut (std::iostream& IOStream, int EOL=0);


// =====================================================================
// =====================================================================


void printStdErr (std::string& CharMessage, int EOL=0);


// =====================================================================
// =====================================================================


void printStdErr (const char* CharMessage, int EOL=0);


// =====================================================================
// =====================================================================


void printStdErr (std::stringstream& StringStream, int EOL=0);


// =====================================================================
// =====================================================================


void printStdErr (std::iostream& IOStream, int EOL=0);


// =====================================================================
// =====================================================================


void printWarning (const char* CharMessage, PyObject *PyWarning = NULL);


// =====================================================================
// =====================================================================


void printWarning (std::string& Message, PyObject *PyWarning = NULL);


} // topython


// =====================================================================
// =====================================================================


namespace rawfunction {


template <class InternalClass>
struct PythonRawFunctionWrapper_t
{
  public :

    typedef PyObject*(InternalClass::*ClassFun)(PyObject*, PyObject*, PyObject*);


// =====================================================================
// =====================================================================


    PyObject* operator() (PyObject* InTuple,
                          PyObject* InDict)
    {
      while (1)
      {
        if (this->m_Function == NULL)
        {
          PyErr_SetString(PyExc_TypeError, "PythonRawFunctionWrapper called\
     but had null pointer function");
          break;
        }

        /* check type */
        if (!PyTuple_CheckExact(InTuple))
        {
          PyErr_SetString(PyExc_TypeError, "PythonRawFunctionWrapper called\
 without tuple or tuple subtype");
          break;
        }
        else if (!PyDict_CheckExact(InDict))
        {
          PyErr_SetString(PyExc_TypeError, "PythonRawFunctionWrapper called\
 without dict or dict subtype");
          break;
        }

        /* check class */
        int LenInTuple = PyTuple_Size(InTuple);
        if (LenInTuple <= 0)
        {
          PyErr_SetString(PyExc_EnvironmentError, "PythonRawFunctionWrapper\
 called without class associated");
          break;
        }
        PyObject* PyObSelf = PyTuple_GET_ITEM(InTuple, 0);
        boost::python::extract<InternalClass*> GetClass(PyObSelf);
        if (!GetClass)
        {
          PyErr_SetString(PyExc_EnvironmentError, "PythonRawFunctionWrapper\
 called with wrong class associated");
          break;
        }
        InternalClass* ObjectClass = GetClass();
        /* pop the class from the tuple */
        InTuple = PyTuple_GetSlice(InTuple, 1, LenInTuple);

        /* call function */
        PyObject* Res = (ObjectClass->*(this->m_Function))(PyObSelf, InTuple, InDict);
        if (Res != NULL)
        {
          Py_INCREF(Res);
          return Res;
        }

        break;
      }

      /* return result NONE */
      Py_INCREF(Py_None);
      return Py_None;
    }


// =====================================================================
// =====================================================================


    boost::python::object operator() (boost::python::tuple BoTuple,
                                      boost::python::dict BoDict)
    {
      PyObject* PyRes = this->operator()(BoTuple.ptr(), BoDict.ptr());
      /* decrement because boost::python::raw_function will increase
         automatically the pyobject pointer */
      Py_DECREF(PyRes);
      /* allows re-use of the same pyobject pointer */
      boost::python::object BoRes(
        boost::python::handle<>(boost::python::borrowed(PyRes)));
      return BoRes;
    }


// =====================================================================
// =====================================================================


    PythonRawFunctionWrapper_t (ClassFun InFunction)
    {
      if (InFunction == NULL)
        PyErr_SetString(PyExc_TypeError, "PythonRawFunctionWrapper\
 received null pointer");
      else
        this->m_Function = InFunction;
    }


// =====================================================================
// =====================================================================


  private :
    ClassFun m_Function;
};


} // rawfunction


} // pyopenfluid


#endif // __PYTHONUTILITIES_HPP__
