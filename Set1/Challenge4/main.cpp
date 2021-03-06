#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <cstring>
#include <tuple>
#include <list>
#include <fstream>

#include "Hexadecimal.hpp"
#include "XOR.hpp"
#include "FrequencyCounter.hpp"
#include "TextScoring.hpp"
#include "Utils.hpp"

using namespace std;

/**
 * Read a file, containing hexadecimal encoded strings and try to crack them.
 *
 * According to the level description only one string is propery encrypted.
 * Therefore output only the one with the highest score after decrypting
 */
int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		cerr << "Usage: ./programm filename" << endl;
		return 1;
	}

	ifstream infile(argv[1]);

	list<tuple<string, string, string, double>> bestMatches;

	string crypted;
	while(getline(infile, crypted))
	{
		// cout << "Try: " << crypted << endl;
		auto cracked = XOR::crack(crypted);
		bestMatches.push_back(make_tuple(crypted, get<0>(cracked), get<1>(cracked), get<2>(cracked)));
	}
	
	auto bestMatch = XOR::getBestMatch(bestMatches);

	auto encrypted = get<0>(bestMatch);
	auto key = get<1>(bestMatch);
	auto decrypted = Hexadecimal::decode(get<2>(bestMatch));

	cout << "Key is:    '" << key << "'" << endl;
	cout << "Encrypted: '" << encrypted << "'" << endl;
	cout << "Decrypted: '" << Utils::byteVecToStr(decrypted, "") << "'" << endl;

	return 0;
}

