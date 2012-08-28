#ifndef BIT_H
#define BIT_H

#include <string>
#include <boost/variant.hpp>
#include <boost/blank.hpp>
#include <boost/lexical_cast.hpp>

#include "StackPrinter.h"

typedef boost::variant<boost::blank, bool, char, int, float, std::string> Variant;

class Bit {
private:
	Variant variant;

	// Private init function used by the public constructor that accepts string type, string value
	template <class T>
	Variant init(std::string requestedType, std::string typeText, T type, std::string value)
	{
		if(requestedType == typeText)
		{
			try
			{
				return boost::lexical_cast<T> (value);
			}
			catch (boost::bad_lexical_cast e)
			{
				std::cout << "Invalid type/value combination or bad data " << requestedType << " " << value << std::endl;
				return boost::blank();
			}
		}

		return boost::blank();
	}

public:
	Bit();
	Bit(Variant variant);
	Bit(const char *text); // Required so that you may initialize Bit from a string literal. The templated version gives a compile error when initializing from a string literal.
	Bit(std::string type, std::string value);

	std::string type();

	template <class T>
	Bit(T t)
	{
		variant = t;
	}

	friend std::ostream& operator<<(std::ostream &out, const Bit& bit);

	template <class T>
	operator T() 
	{
		switch(variant.which())
		{
			// bool
			case 1:
				return boost::get<bool>(variant);
			break;

			// char
			case 2:
				return boost::get<char>(variant);
			break;

			// int
			case 3:
				return boost::get<int>(variant);
			break;

			// float
			case 4:
				return boost::get<float>(variant);
			break;

			// string
			case 5:
				try
				{
					return boost::lexical_cast<T>(variant);
				}
				catch(boost::bad_lexical_cast e)
				{
					std::cout << "Failed to convert Bit " << boost::get<std::string>(variant) << " from a string to another type" << std::endl;
					StackPrinter sp;
					sp.print();
					return T();
				}	
			break;

			case 0:
			default:
				StackPrinter sp;
				sp.print();
				return T();
			break;
		}
	}

	// Conversion to strings needs specialized behavior
	operator std::string()
	{
		// If the requested conversion is a string, and the variant is actually a string - Just do it
		if(variant.type() == typeid(std::string))
			return boost::get<std::string>(variant);
		else
		{
			// If the variant is not a string, try to convert it to one
			try
			{
				return boost::lexical_cast<std::string>(variant);
			}
			// Hard to think of a case where you cannot convert a bool/char/int/float to a string, but if the conversion failed, return an empty string
			catch(boost::bad_lexical_cast e)
			{
				StackPrinter sp;
				sp.print();
				return "";
			}	
		}
	}

	Bit operator= (const Bit &other);
};

std::ostream& operator << (std::ostream &out, const Bit &bit);

typedef Bit var;

#endif