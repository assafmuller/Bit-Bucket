#include <iostream>
#include <boost/lexical_cast.hpp>
#include <string>

#include "Bit.h"
#include "BitTypeVisitor.h"

Bit::Bit()
{
	this->variant = boost::blank();
}

Bit::Bit(Variant variant)
{
	this->variant = variant;
}

Bit::Bit(const char *text)
{
	this->variant = std::string(text);
}

Bit::Bit(std::string type, std::string value)
{
	if(type == "bool")
	{
		if(value == "false")
		{
			variant = false;
			return;
		}

		if(value == "true")
		{
			variant = true;
			return;
		}

		// The type written is bool, but the value is invalid
		variant = bool();
		std::cout << "Invalid type/value combination " << type << " " << value << std::endl;
		return;
	}

	variant = init(type, "char", char(), value);
	if(variant.type() != typeid(boost::blank))
		return;

	variant = init(type, "int", int(), value);
	if(variant.type() != typeid(boost::blank))
		return;

	variant = init(type, "float", float(), value);
	if(variant.type() != typeid(boost::blank))
		return;

	variant = init(type, "string", std::string(), value);
	if(variant.type() != typeid(boost::blank))
		return;

	if(type == "auto")
	{
		// BOOL
		if(value == "true")
		{
			variant = true;
			return;
		}

		if(value == "false")
		{
			variant = false;
			return;
		}

		// INT
		try
		{
			variant = boost::lexical_cast<int> (value);
			return;
		}
		catch (boost::bad_lexical_cast e)
		{
			// FLOAT
			try
			{
				variant = boost::lexical_cast<float> (value);
				return;
			}
			catch (boost::bad_lexical_cast e)
			{
				// CHAR
				try
				{
					variant = boost::lexical_cast<char> (value);
					return;
				}
				catch (boost::bad_lexical_cast e)
				{
					// STRING
					variant = value;
					return;
				}
			}
		}
	}

	// If the type is not a known POD or auto
	else
	{
		variant = boost::blank();
		std::cout << "Invalid type " << type << " " << value << std::endl;
		return;
	}
}

std::string Bit::type()
{
	return boost::apply_visitor(BitTypeVisitor(), variant);
}

std::ostream& operator<<(std::ostream &out, const Bit &bit)
{
	out << bit.variant;

	return out;
}

Bit Bit::operator= (const Bit &other)
{
	variant = other.variant;
	return *this;
}