#ifndef BIT_BUCKET_H
#define BIT_BUCKET_H

#include <unordered_map>
#include <string>
#include <functional>

#include "Bit.h"

/**
	BitBucket is a hash map, where the keys are strings and the values are Bits.
	Specifically, BitBucket inherits from std::unordered_map, so you may use it as an STL container.
*/
class BitBucket : public std::unordered_map<std::string, Bit> {
private:

public:
	/**
		Default constructor.
	*/
	BitBucket();

	/**
		Initialize the Bit Bucket from a text file. The format is:
		<type> <name> <value>
		<type> <name> <value>
		...

		For example:
		int x 5
		float y 3.14
		string s Hello world!
		auto b false

		When using "auto" as a type the type of the variable will be deduced according to its value, much like the "auto" keyword in C++11.

		@param filePath - Path to the text file holding the data
	*/
	BitBucket (std::string filePath);

	/**
		Write the bucket's contents to a text file of the same format as described in BitBucket (std::string filePath).

		@param filePath - Path to the text file to write to
	*/
	void serialize(std::string filePath);

	/**
		Is there something in bucket[key]?
	*/
	bool isSet(std::string key);

	/**
		Print the entire bucket in the following format:

		<type> <name> <value>
	*/
	void print();

	/**
		Print all blank cells in the bucket. Blank cells can be created like so:
		int x = bucket["nonExistantCell"];
	*/
	void printBlank();

	/**
		Prints all cells that return true to the predicate/lambda passed in, to the output stream specified. std::cout is the default value.

		@param predicate - An std::function that accepts a keu and value and returns if the key/value pair should be printed
		@param out - An output stream
	*/
	void print(std::function <bool (std::string key, Bit value)> predicate, std::ostream &out = std::cout);
};

#endif