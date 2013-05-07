#include "PythonUtilities.hpp"

namespace pyopenfluid { 

namespace tools {

/* stringFill('text', 'pattern ', 14) = 'pattern pattern text'*/
/* stringFill('23', '0', 5) = '00023' */
std::string stringFill (const std::string Input, const std::string StrFill,
    unsigned int MaxLength)
{
  std::string Res = std::string(Input);
  while (Res.length() < MaxLength)
    Res = StrFill + Res;
  return Res;
}


// =====================================================================
// =====================================================================


std::string zeroFill (const std::string Input, unsigned int MaxLength)
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

  /* split message by 1000 char */
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

  /* split message by 1000 char */
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

} // topython

} // pyopenfluid
