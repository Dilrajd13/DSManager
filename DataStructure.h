// DataStructure base class
// Every data structure inherits from this so the terminal can run the same commands on all of them
#pragma once
#include <string>
#include <iostream>
#include <cstdlib>

class DataStructure {
public:
	virtual ~DataStructure() {}

	virtual std::string typeName() = 0;
	virtual int size() = 0;
	virtual void add(std::string data) = 0;
	virtual bool remove(std::string data) = 0;
	virtual bool search(std::string data) = 0;
	virtual void view() = 0;

	// Linked list and tree remove a chosen value, the others always remove their next element
	virtual bool removeNeedsValue() { return false; }

	// Stack and queue only touch their ends so they don't allow editing
	virtual bool canEdit() { return false; }
	virtual bool edit(std::string oldData, std::string newData) { return false; }
};

// Puts the value in number and returns true if the whole string is a real number
inline bool toNumber(const std::string& text, double& number) {
	char* end;
	number = std::strtod(text.c_str(), &end);
	return *end == '\0' && number == number;
}

// Compares as numbers when both values are numbers so 9 comes before 10, numbers come before text, text compares normally
inline bool valueLess(const std::string& a, const std::string& b) {
	double numA;
	double numB;
	bool aIsNumber = toNumber(a, numA);
	bool bIsNumber = toNumber(b, numB);

	if (aIsNumber && bIsNumber) {
		return numA < numB;
	}
	if (aIsNumber != bIsNumber) {
		return aIsNumber;
	}
	return a < b;
}
