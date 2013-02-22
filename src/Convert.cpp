#include <string>
#include <vector>
#include <list>
#include <map>
#include <boost/python.hpp>

namespace convert {


// =====================================================================
// =====================================================================


std::string boostStrToCString (const boost::python::str StrInput)
{
	char* CharStr = boost::python::extract<char*>(StrInput);
	return std::string(CharStr);
}


// =====================================================================
// =====================================================================


} // namespace
