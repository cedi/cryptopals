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
	CharFreqCntr freq(crypted, 2);

	auto singleChar = freq.getFrequency(CharFreqCntr::SINGLE);

#if 0
	cout << "Single Character Occurrences:" << endl;
	printKV(singleChar);
	
	auto dualChar = freq.getFrequency(CharFreqCntr::DUAL);
	cout << "Dual Character Occurrences:" << endl;
	printKV(dualChar);

	auto repeatingChar = freq.getFrequency(CharFreqCntr::REPEATING);
	cout << "Repeating Chars:" << endl;
	printKV(repeatingChar);
#endif

	cout << "Try to break it" << endl;
	const string mostCurrentPossibilities = "ETAOIN SHRDLU";
	map<string, double> possibleKeys;

	// get possible key as character by probing every ASCII character
	// This means try to XOR every ASCII character with one of the possible
	// chars from mostCurrentPossibilities and compare it against the most
	// current char of the analyzed text. The matches are potential keys
	for(int i = 0; i < 256; i++)
	{
		string toProbe(1, (char)i);

		for(auto possibleCurrentChar : mostCurrentPossibilities)
		{
			string encrypted = Hexadecimal::encode(XOR::encode(string(1, possibleCurrentChar), toProbe));
			if(encrypted == freq.getMostOccurent(CharFreqCntr::SINGLE))
			{
				//cout << "Key seems to be: '" << toProbe << "'" << endl;
				possibleKeys.insert(make_pair(toProbe, 0));
				break;
			}
		}
	}

	// Now try to decrypt the encrypted text using the above calculated keys
	// and analyze every result using the TextScoring class
	string chipertext = Hexadecimal::decode(crypted);

	for(auto iter : possibleKeys)
	{
		string character = iter.first;

		char* key = (char*)malloc(chipertext.size() + 1);
		memset(key, character.c_str()[0], chipertext.size());
		key[chipertext.size()] = '\0';

		string decoded = XOR::encode(chipertext, key);
		TextScoring score(Hexadecimal::encode(decoded));

		possibleKeys[character] = score.analyze(TextScoring::PRINTABLE, TextScoring::DECODE_HEX);

		//cout << "Trying key: '" << key << "'" << endl;
	}

	double score = 0;
	string character;
	for(auto iter : possibleKeys)
	{
		if(score < iter.second)
		{
			score = iter.second;
			character = iter.first;
		}
	}

	cout << "Key is: '" << character << "'" << endl;

	char* key = (char*)malloc(chipertext.size() + 1);
	memset(key, character.c_str()[0], chipertext.size());
	key[chipertext.size()] = '\0';

	string decoded = XOR::encode(chipertext, key);

	cout << "Encrypted:	" << chipertext.size() << ": '" << chipertext << "'" << endl;
	cout << "Decrypted:	" << decoded.size() << ": '" << decoded << "'" << endl;
	return 0;
}


















