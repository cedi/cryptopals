#include <cassert>
#include "HammingDistance.hpp"

using namespace std;

int HammingDistance::calc(string left, string right)
{
	assert(left.length() == right.length());

	int distance = 0;

	int length = left.length();
	for(int i = 0; i < length; i++)
	{
		distance += calc(left[i], right[i]);
	}

	return distance;
}

int HammingDistance::calc(unsigned left, unsigned right)
{
	int distance = 0;

	// XOR the two bytes, cause if two bits are the same, they become 0, if they
	// are different they become 1
	unsigned xored = left ^ right;

	// count bits
	// if the strings are the same, they have 0 different bits, so exit the loop
	while(xored != 0)
	{
		// if a bit is set increment count and clear the bit
		distance++;

		// set the bit to zero
		xored &= (xored - 1);
	}

	return distance;
}
