#ifndef __PYTHONUTILITIES_HPP__
#define __PYTHONUTILITIES_HPP__

#include <string>
#include <vector>
#include <list>
#include <map>
#include <boost/python.hpp>
#include <sstream>
#include <iostream>


namespace tools {

std::string stringFill (const std::string Input, const std::string StrFill,
    int MaxLength);


// =====================================================================
// =====================================================================


std::string zeroFill (const std::string Input, int MaxLength);

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


namespace pyopenfluid { namespace rawfunction {


template <class InternalClass>
struct PythonRawFunctionWrapper_t
{
  typedef PyObject*(InternalClass::*ClassFun)(PyObject*, PyObject*);

  boost::python::object operator() (boost::python::tuple BoTuple,
                                    boost::python::dict BoDict);

  PyObject* operator() (PyObject* InTuple,
                        PyObject* InDict);

  PythonRawFunctionWrapper_t (ClassFun InFunction);

  private :
    ClassFun m_Function;
};


} // rawfunction
} // pyopenfluid


#endif // __PYTHONUTILITIES_HPP__
