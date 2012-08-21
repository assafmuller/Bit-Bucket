#include "BitBucket.h"
#include <fstream>
#include <iostream>
#include <boost/lexical_cast.hpp>

using namespace std;

void BitBucket::init()
{
	errorKey = "__BitBucketError";
	(*this)[errorKey] = boost::blank();
}

BitBucket::BitBucket()
{
	init();
}

BitBucket::BitBucket (std::string filePath)
{
	init();

	ifstream file (filePath);
	if(!file.is_open()) 
	{
		cout << "Error, cannot open file " << filePath << endl;
		return;
	}

	string line;
	while(!file.eof()) 
	{
		getline (file, line);
		
		/*
		 *	Format is:
		 *	type name value
		 */
		  
		// Find first space, everything up to that is the type
		int spaceIndex = line.find_first_of(' ');
		string type = line.substr(0, spaceIndex);

		// Cut what we already found from the string, continue with "name value". Everything up to the first space is the name
		line = line.substr(spaceIndex + 1);
		spaceIndex = line.find_first_of(' ');
		string key = line.substr(0, spaceIndex);

		// Cut everything before the value, and use that
		line = line.substr(spaceIndex + 1);
		string value = line;

		(*this)[key] = Bit(type, value);
	}

	file.close();
}

bool BitBucket::isSet(std::string key)
{
	return find(key) != end();
}

void BitBucket::print()
{
	for(auto i = begin(); i != end(); ++i)
	{
		if(i->first == errorKey)
			continue;

		cout << i->second.type() << " " << i->first << " " << i->second << endl;
	}
}