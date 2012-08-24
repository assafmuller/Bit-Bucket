#include <iostream>
#include <boost/lexical_cast.hpp>
#include <string>

#include "Bit.h"
#include "BitTypeVisitor.h"

Bit::Bit()
{
	this->bit = boost::blank();
}

Bit::Bit(boost::variant<boost::blank, bool, char, int, float, std::string> bit)
{
	this->bit = bit;
}

Bit::Bit(const char *text)
{
	this->bit = std::string(text);
}

#define INIT_BIT(TYPE_STRING, TYPE, VALUE) \
if(type == TYPE_STRING) \
{ \
	try \
	{ \
		bit = boost::lexical_cast<TYPE> (VALUE); \
		return; \
	} \
	catch (boost::bad_lexical_cast e) \
	{ \
		bit = TYPE(); \
		std::cout << "Invalid type/value combination " << type << " " << value << std::endl; \
		return; \
	} \
}

Bit::Bit(std::string type, std::string value)
{
	if(type == "bool")
	{
		if(value == "false")
		{
			bit = false;
			return;
		}

		if(value == "true")
		{
			bit = true;
			return;
		}

		// The type written is bool, but the value is invalid
		bit = bool();
		std::cout << "Invalid type/value combination " << type << " " << value << std::endl;
		return;
	}

	INIT_BIT("char", char, value)
	INIT_BIT("int", int, value)
	INIT_BIT("float", float, value)
	INIT_BIT("string", std::string, value)

	if(type == "auto")
	{
		// BOOL
		if(value == "true")
		{
			bit = true;
			return;
		}

		if(value == "false")
		{
			bit = false;
			return;
		}

		// INT
		try
		{
			int test = boost::lexical_cast<int> (value);
			bit = test;
			return;
		}
		catch (boost::bad_lexical_cast e)
		{
			// FLOAT
			try
			{
				float test = boost::lexical_cast<float> (value);
				bit = test;
				return;
			}
			catch (boost::bad_lexical_cast e)
			{
				// CHAR
				try
				{
					char test = boost::lexical_cast<char> (value);
					bit = test;
					return;
				}
				catch (boost::bad_lexical_cast e)
				{
					// STRING
					bit = value;
					return;
				}
			}
		}
	}

	// If the type is not a known POD or auto
	else
	{
		bit = boost::blank();
		std::cout << "Invalid type/value combination " << type << " " << value << std::endl;
		return;
	}
}

std::string Bit::type()
{
	return boost::apply_visitor(BitTypeVisitor(), bit);
}

#define OUT(X) 	if(bit.bit.type() == typeid(X)) \
{ \
	out << boost::get<X>(bit.bit); \
}

std::ostream& operator<<(std::ostream &out, const Bit &bit)
{
	OUT(int)
	OUT(float)
	OUT(bool)
	OUT(char)
	OUT(std::string)

	return out;
}

Bit Bit::operator= (const Bit &other)
{
	bit = other.bit;
	return *this;
}