#ifndef BIT_BUCKET_H
#define BIT_BUCKET_H

#include <unordered_map>
#include <string>

#include "Bit.h"

using namespace std;

class BitBucket : public unordered_map<string, Bit> {
private:
	std::string errorKey;
	void init();

public:
	BitBucket();
	BitBucket (std::string filePath);

	//Bit& operator [] (std::string key);
	bool isSet(std::string key);

	void print();
};

#endif