#include <string>
#include <vector>
#include <boost/python.hpp>

namespace convert {

template<class T>
boost::python::list* cVectorToBoostList(const std::vector<T>* Vector)
{
	boost::python::list* List = new boost::python::list();

	typename std::vector<T>::iterator IteratorVector;
	for (IteratorVector = ((std::vector<T>*) Vector)->begin();
			IteratorVector != ((std::vector<T>*) Vector)->end();
			IteratorVector++)
	{
		List->append( *IteratorVector );
	}

	return List;
}

boost::python::list* cVectorToBoostListOfString(
			const std::vector<std::string>* Vector)
{
	return cVectorToBoostList<std::string>(Vector);
}

std::string* boostStrToCString (const boost::python::str* StrInput)
{
	char* CharStr = boost::python::extract<char*>(*StrInput);
	return new std::string(CharStr);
}

}
