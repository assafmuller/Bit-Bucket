#include <fstream>
#include <iostream>
#include <boost/lexical_cast.hpp>

#include "BitBucket.h"

BitBucket::BitBucket()
{

}

BitBucket::BitBucket (std::string filePath)
{
	std::ifstream file (filePath);
	if(!file.is_open()) 
	{
		std::cout << "Error, cannot open file " << filePath << std::endl;
		return;
	}

	std::string line;
	while(!file.eof()) 
	{
		getline (file, line);
		
		/*
		 *	Format is:
		 *	type name value
		 *	type name value
		 *	...
		 */
		  
		// Find first space, everything up to that is the type
		int spaceIndex = line.find_first_of(' ');
		std::string type = line.substr(0, spaceIndex);

		// Cut what we already found from the string, continue with "name value". Everything up to the first space is the name
		line = line.substr(spaceIndex + 1);
		spaceIndex = line.find_first_of(' ');
		std::string key = line.substr(0, spaceIndex);

		// Cut everything before the value, and use that
		line = line.substr(spaceIndex + 1);
		std::string value = line;

		(*this)[key] = Bit(type, value);
	}

	file.close();
}

bool BitBucket::isSet(std::string key)
{
	return count(key);
}

void BitBucket::print()
{
	print([this] (std::string key, Bit value) 
	{
		return true;
	});
}

void BitBucket::printBlank()
{
	print([this] (std::string key, Bit value) 
	{
		return value.type() == "blank";
	});
}

void BitBucket::print(std::function <bool (std::string key, Bit value)> predicate)
{
	for(auto i = begin(); i != end(); ++i)
	{
		if(predicate(i->first, i->second))
			std::cout << i->second.type() << " " << i->first << " " << i->second << std::endl;
	}
}