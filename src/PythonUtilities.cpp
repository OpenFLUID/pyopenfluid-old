#include <string>
#include <vector>
#include <list>
#include <map>
#include <sstream>
#include <typeinfo>

#include <Python.h>
#include <boost/python.hpp>

#include "PythonUtilities.hpp"


namespace tools {

std::string stringFill (const std::string Input, const std::string StrFill,
    int MaxLength)
{
  std::string Res = std::string(Input);
  while (Res.length() < MaxLength)
    Res = StrFill + Res;
  return Res;
}


// =====================================================================
// =====================================================================


std::string zeroFill (const std::string Input, int MaxLength)
{
  return stringFill(Input, std::string("0"), MaxLength);
}

} // tools


// =====================================================================
// =====================================================================


namespace topython {

void printStdOut (std::string& Message, int EOL)
{
  int LenMsg = Message.length();

  if (LenMsg >= 1000)
  {
    int NFois = LenMsg / 999;
    std::string TmpString;
    int i;

    for (i=0; i<NFois; i++)
    {
      TmpString = Message.substr(i*999, 999);
      PySys_WriteStdout("%.999s", TmpString.c_str());
    }

    i = NFois*999;
    TmpString = Message.substr(i, (LenMsg-i));
    PySys_WriteStdout("%.999s", TmpString.c_str());
  }
  else
    PySys_WriteStdout("%.999s", Message.c_str());

  if (EOL)
    PySys_WriteStdout("\n");
}


// =====================================================================
// =====================================================================


void printStdErr (std::string& Message, int EOL)
{
  int LenMsg = Message.length();

  if (LenMsg >= 1000)
  {
    int NFois = LenMsg / 999;
    std::string TmpString;
    int i;

    for (i=0; i<NFois; i++)
    {
      TmpString = Message.substr(i*999, 999);
      PySys_WriteStderr("%.999s", TmpString.c_str());
    }

    i = NFois*999;
    TmpString = Message.substr(i, (LenMsg-i));
    PySys_WriteStderr("%.999s", TmpString.c_str());
  }
  else
    PySys_WriteStderr("%.999s", Message.c_str());

  if (EOL)
    PySys_WriteStderr("\n");
}


// =====================================================================
// =====================================================================


void printStdOut (const char* CharMessage, int EOL)
{
  std::string Message = std::string(CharMessage);
  printStdOut(Message, EOL);
}


// =====================================================================
// =====================================================================


void printStdErr (const char* CharMessage, int EOL)
{
  std::string Message = std::string(CharMessage);
  printStdOut(Message, EOL);
}


// =====================================================================
// =====================================================================


void printStdOut (std::stringstream& StringStream, int EOL)
{
  std::string Message = StringStream.str();
  printStdOut(Message, EOL);
}


// =====================================================================
// =====================================================================


void printStdErr (std::stringstream& StringStream, int EOL)
{
  std::string Message = StringStream.str();
  printStdOut(Message, EOL);
}


// =====================================================================
// =====================================================================


void printStdOut (std::iostream& IOStream, int EOL)
{
  std::string StringMessage;
  IOStream >> StringMessage;
  printStdOut(StringMessage, EOL);
}


// =====================================================================
// =====================================================================


void printStdErr (std::iostream& IOStream, int EOL)
{
  std::string StringMessage;
  IOStream >> StringMessage;
  printStdOut(StringMessage, EOL);
}


// =====================================================================
// =====================================================================


void printWarning (const char* CharMessage, PyObject *PyWarning)
{
  if (PyWarning != NULL)
    PyErr_WarnEx(PyWarning, CharMessage, 1);
  else
  {
    const char* name = "PyOpenFluid.PyOpenFluidWarning";
    PyObject* myException = PyErr_NewException((char*)name,
        PyExc_RuntimeWarning, NULL);
    PyErr_WarnEx(myException, CharMessage, 1);
  }
}


// =====================================================================
// =====================================================================


void printWarning (std::string& Message, PyObject *PyWarning)
{
  printWarning(Message.c_str(), PyWarning);
}

} // boost


// =====================================================================
// =====================================================================


namespace pyopenfluid { namespace rawfunction {


template <class InternalClass>
boost::python::object PythonRawFunctionWrapper_t<InternalClass>::operator()
    (boost::python::tuple BoTuple,
     boost::python::dict BoDict)
{
  PyObject* PyRes = this(BoTuple.ptr(), BoDict.ptr());
  Py_DECREF(PyRes);
  boost::python::object BoRes(
    boost::python::handle<>(boost::python::borrowed(PyRes)));
  return BoRes;
}


// =====================================================================
// =====================================================================


template <class InternalClass>
PyObject* PythonRawFunctionWrapper_t<InternalClass>::operator()
    (PyObject* InTuple, PyObject* InDict)
{
  while (1)
  {
    if (this->m_Function == NULL)
    {
      PyErr_SetString(PyExc_EnvironmentError, "PythonRawFunctionWrapper called\
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
      PyErr_SetString(PyExc_TypeError, "PythonRawFunctionWrapper called\
 without class associated");
      break;
    }
    InternalClass* GetClass = 
        boost::python::extract<InternalClass*>(PyTuple_GET_ITEM(InTuple, 0));
    if (!GetClass)
    {
      PyErr_SetString(PyExc_TypeError, "PythonRawFunctionWrapper called\
 without class associated");
      break;
    }
    InTuple = PyTuple_GetSlice(InTuple, 1, LenInTuple-1);

    /* call function */
    PyObject* Res = this->m_Function(InTuple, InDict);
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


template <class InternalClass>
PythonRawFunctionWrapper_t<InternalClass>::PythonRawFunctionWrapper_t
   (ClassFun InFunction)
{
  if (InFunction == NULL)
    PyErr_SetString(PyExc_EnvironmentError, "PythonRawFunctionWrapper\
 received null pointer");
  else
  {
    this->m_Function = InFunction;
  }
}


} // rawfunction
} // pyopenfluid
