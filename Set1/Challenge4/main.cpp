#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <cstring>
#include <tuple>
#include <list>

#include "Hexadecimal.hpp"
#include "XOR.hpp"
#include "FrequencyCounter.hpp"
#include "TextScoring.hpp"

using namespace std;


void probePossibleKeys(const string& crypted, map<string, double>* possibleKeys)
{
	CharFreqCntr freq(crypted, 2);

	auto singleChar = freq.getFrequency(CharFreqCntr::SINGLE);

	cout << "Try to break it" << endl;
	const string mostCurrentPossibilities = "ETAOIN SHRDLU";

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
				possibleKeys->insert(make_pair(toProbe, 0));
			}
		}
	}

}

int main()
{
	string crypted = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

	map<string, double> possibleKeys;
	probePossibleKeys(crypted, &possibleKeys);
	
	// Now try to decrypt the encrypted text using the above calculated keys
	// and analyze every result using the TextScoring class
	string chipertext = Hexadecimal::decode(crypted);

	list<tuple<string, string, double>> decryptedNScored;

	for(auto iter : possibleKeys)
	{
		string character = iter.first;

		char* key = (char*)malloc(chipertext.size() + 1);
		memset(key, character.c_str()[0], chipertext.size());
		key[chipertext.size()] = '\0';

		string decoded = XOR::encode(chipertext, key);
		TextScoring score(Hexadecimal::encode(decoded));

		decryptedNScored.push_back(make_tuple(key, decoded, score.analyze(TextScoring::PRINTABLE, TextScoring::DECODE_HEX)));
	}

	double score = 0;
	string key;
	string decrypted;
	for(auto result : decryptedNScored)
	{
		if(score < get<2>(result))
		{
			key = get<0>(result);
			decrypted = get<1>(result);
			score = get<2>(result);
		}
	}

	cout << "Key is:    '" << key << "'" << endl;
	cout << "Encrypted: '" << chipertext << "'" << endl;
	cout << "Decrypted: '" << decrypted << "'" << endl;
	return 0;
}

