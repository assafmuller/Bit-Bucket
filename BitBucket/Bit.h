#ifndef BIT_H
#define BIT_H

#include <string>
#include <boost/variant.hpp>
#include <boost/blank.hpp>

class Bit {
private:
	boost::variant<boost::blank, bool, char, int, float, std::string> bit;
	
public:
	Bit();
	Bit(boost::variant<boost::blank, bool, char, int, float, std::string> bit);
	Bit(const char *text);
	Bit(std::string type, std::string value);

	std::string type();

	template <class T>
	Bit(T t)
	{
		bit = t;
	}

	friend std::ostream& operator<<(std::ostream &out, const Bit& bit);

	template <class T>
	operator T() 
	{
		try
		{
			return boost::get<T>(bit);
		}
		catch(boost::bad_get)
		{
			return T();
		}	
	}

	Bit operator= (const Bit &other);
};

std::ostream& operator << (std::ostream &out, const Bit &bit);

#endif