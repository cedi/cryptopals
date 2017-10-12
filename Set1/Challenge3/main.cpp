#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <cstring>

#include "Hexadecimal.hpp"
#include "XOR.hpp"
#include "FrequencyCounter.hpp"
#include "TextScoring.hpp"

using namespace std;

void printKV(const map<string, double> occurrence)
{
	for(auto x : occurrence)
	{
		cout << x.first << ": " << x.second << endl;
	}
}

int main()
{
	string crypted = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

	auto cracked = XOR::crack(crypted);

	cout << "Key is:    '" << get<0>(cracked) << "'" << endl;
	cout << "Encrypted: '" << crypted << "'" << endl;
	cout << "Decrypted: '" << get<1>(cracked) << "'" << endl;
	return 0;
}


















