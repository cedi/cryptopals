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

void decryptAndScore(const string& crypted, const map<string, double>& possibleKeys, list<tuple<string, string, double>>* decryptedNScored)
{
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

		decryptedNScored->push_back(make_tuple(key, decoded, score.analyze(TextScoring::PRINTABLE, TextScoring::DECODE_HEX)));
	}
}

tuple<string, string, double> getBestMatch(const list<tuple<string, string, double>>& decryptedNScored)
{
	tuple<string, string, double> bestMatch;

	for(auto result : decryptedNScored)
	{
		if(get<2>(bestMatch) < get<2>(result))
		{
			bestMatch = result;
		}
	}

	return bestMatch;
}

tuple<string, string, string, double> getBestMatch(const list<tuple<string, string, string, double>>& cryptedKeyDecryptedNScored)
{
	tuple<string, string, string, double> bestMatch;

	for(auto result : cryptedKeyDecryptedNScored)
	{
		if(get<2>(bestMatch) < get<2>(result))
		{
			bestMatch = result;
		}
	}

	return bestMatch;
}

tuple<string, string, double> crack(string crypted)
{
	map<string, double> possibleKeys;
	probePossibleKeys(crypted, &possibleKeys);

	list<tuple<string, string, double>> decryptedNScored;
	decryptAndScore(crypted, possibleKeys, &decryptedNScored);

	auto bestMatch = getBestMatch(decryptedNScored);
	cout << "Decrypted: " << get<1>(bestMatch) << endl;

	return bestMatch;
}

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
		cout << "Try: " << crypted << endl;
		auto cracked = crack(crypted);
		bestMatches.push_back(make_tuple(crypted, get<0>(cracked), get<1>(cracked), get<2>(cracked)));
	}
	
	auto bestMatch = getBestMatch(bestMatches);

	cout << "Encrypted String: '" << get<0>(bestMatch) << "'" << endl;
	cout << "Key:              '" << get<1>(bestMatch) << "'" << endl;
	cout << "Decrypted:        '" << get<2>(bestMatch) << "'" << endl;

	return 0;
}

