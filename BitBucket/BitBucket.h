#ifndef BIT_BUCKET_H
#define BIT_BUCKET_H

#include <unordered_map>
#include <string>
#include <functional>

#include "Bit.h"

class BitBucket : public std::unordered_map<std::string, Bit> {
private:

public:
	BitBucket();
	BitBucket (std::string filePath);

	bool isSet(std::string key);

	void printBlank();
	void print();
	void print(std::function <bool (std::string key, Bit value)> predicate);
};

#endif