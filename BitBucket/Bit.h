#ifndef BIT_H
#define BIT_H

#include <string>
#include <boost/variant.hpp>
#include <boost/blank.hpp>
#include <boost/lexical_cast.hpp>

#include "StackPrinter.h"

typedef boost::variant<boost::blank, bool, char, int, float, std::string> Variant;

/**
	The Bit class is a variant, able to hold bool, char, int, float or string at any given time.
*/
class Bit {
private:
	Variant variant; /// boost::variant, where we actually hold the variant's data

	/**
		Private init function used by the public constructor

		@param requestedType The type this variant should be initialized to
		@param typeText The type we're trying to initialize in textual form
		@param type The type we're trying to initialize in template form
		@param value The value the variant should hold

		@return Type T with the correct value, or blank if failed
	*/
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

	/**
		Default constructor. Sets the Bit to blank.
	*/
	Bit();

	/**
		Copy constructor.
	*/
	Bit(Variant variant);

	/**
		Required so that you may initialize Bit from a string literal. The templated version gives a compile error when initializing from a string literal.
	*/
	Bit(const char *text);

	/**
		Used when initializing from a text file or another exterior resource.

		@param type - Can be bool, char, int, float, string or auto
		@param value - The value this variant will initially hold
	*/
	Bit(std::string type, std::string value);


	/**
		Returns the current type of the variant in a textual format ("int", "float", ...)
	*/
	std::string type();

	/**
		Constructor used when initializing from an intrinsic variable. IE: Bit bit = 5;
	*/
	template <class T>
	Bit(T t)
	{
		variant = t;
	}

	/**
		Allows the Bit class to be streamed
	*/
	friend std::ostream& operator<<(std::ostream &out, const Bit& bit);

	/**
		Conversion to all intrinsic types but string, which has a specialization.
		If the variant is not a string, then it simply returns the value of the variant, in its current type.
		I then let a possible implicit conversion occur - This is the desired behavior.
		If the variant is a string, and (as mentioned before) we're converting to a type that's not a string,
		then try to lexically cast the string to the requested type. If unsuccessful, will return a default-initialized
		of the requested type.
	*/
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

	/**
		Specialized casting function, when converting the variant to a string.
		If the variant is a string, just return it. Otherwise, try to cast it to a string. If unsuccessful, returns an empty string.
	*/
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

/**
	Syntatic sugar to make this class more usable to programmers of many other languages.
*/
typedef Bit var;

#endif