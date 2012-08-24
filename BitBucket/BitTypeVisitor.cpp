#include "BitTypeVisitor.h"

std::string BitTypeVisitor::operator() (const boost::blank &type) const
{
	return "blank";
}

std::string BitTypeVisitor::operator() (const bool &type) const
{
	return "bool";
}

std::string BitTypeVisitor::operator() (const char &type) const
{
	return "char";
}

std::string BitTypeVisitor::operator() (const int &type) const
{
	return "int";
}

std::string BitTypeVisitor::operator() (const float &type) const
{
	return "float";
}

std::string BitTypeVisitor::operator() (const std::string &type) const
{
	return "string";
}