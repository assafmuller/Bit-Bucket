#ifndef BIT_H
#define BIT_H

#include <string>
#include <boost/variant.hpp>
#include <boost/blank.hpp>

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
		try
		{
			return boost::get<T>(variant);
		}
		catch(boost::bad_get)
		{
			static StackPrinter sp; // Print the stack trace
			sp.print();
			return T(); // Return a default initialized type. int() gives 0, bool() gives false, etc.
		}	
	}

	Bit operator= (const Bit &other);
};

std::ostream& operator << (std::ostream &out, const Bit &bit);

#endif