#ifndef __CONVERT_HPP__
#define __CONVERT_HPP__

#include <string>
#include <vector>
#include <boost/python.hpp>

namespace convert {

template<class T>
boost::python::list* cVectorToBoostList(const std::vector<T>* Vector);

boost::python::list* cVectorToBoostListOfString(const std::vector<std::string>* Vector);

std::string* boostStrToCString (const boost::python::str* StrInput);

}

#endif // __CONVERT_HPP__
