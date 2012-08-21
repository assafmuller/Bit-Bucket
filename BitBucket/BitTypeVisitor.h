#ifndef BIT_TYPE_VISITOR
#define BIT_TYPE_VISITOR

#include <boost/variant.hpp>
#include <string>

using namespace std;

class BitTypeVisitor : public boost::static_visitor<std::string> {
public:
    std::string operator() (const boost::blank &type) const;
	std::string operator() (const bool &type) const;
	std::string operator() (const char &type) const;
	std::string operator() (const int &type) const;
	std::string operator() (const float &type) const;
	std::string operator() (const string &type) const;
};

#endif