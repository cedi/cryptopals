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

/**
 * Probe for possible keys
 *
 * @param crypted [in] the decrypted string
 * @param possibleKeys [out] the possible keys, inserted to a list
 */
void probePossibleKeys(const string& crypted, list<string>* possibleKeys)
{
	CharFreqCntr freq(crypted, 2);

	auto singleChar = freq.getFrequency(CharFreqCntr::SINGLE);

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
				possibleKeys->push_back(toProbe);
			}
		}
	}
}

/**
 * Decrypt a string using a list of possible keys, score them and return
 * everything by inserting the key, the decoded message and the score in a list
 *
 * @param crypted [in] the decrypted message 
 * @param possibleKeys [in] the possible keys 
 * @param decryptedNScored [out] the list in which the results are inserted.
 */
void decryptAndScore(
		const string& crypted, const list<string>& possibleKeys,
		list<tuple<string, string, double>>* decryptedNScored
	)
{
	// Now try to decrypt the encrypted text using the above calculated keys
	// and analyze every result using the TextScoring class
	string chipertext = Hexadecimal::decode(crypted);

	for(auto key : possibleKeys)
	{
		string decoded = XOR::encode(chipertext, key);
		TextScoring scoring(Hexadecimal::encode(decoded));
		double score = scoring.analyze(TextScoring::PRINTABLE, TextScoring::DECODE_HEX);

		decryptedNScored->push_back(make_tuple(key, decoded, score));
	}
}

/**
 * get the best match of a list containing the key, the decrypted string and the
 * score. The list is represented as
 * std::list<std::tuple<std::string, std::string, double>>
 *
 * @param decryptedNScored [in] the list with entrys from whitch the best
 * score should be determined and returned
 * 
 * @return the entry of the list with the highest score as 
 * std::tuple<std::string, std::string, double>
 */
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

/**
 * get the best match of a list containing the crypted string, the key, the
 * decrypted string and the score.
 * The list is represented as
 * std::list<std::tuple<std::string, std::string, std::string, double>>
 *
 * @param cryptedKeyDecryptedNScored [in] the list with entrys from whitch the best
 * score should be determined and returned
 * 
 * @return the entry of the list with the highest score as 
 * std::tuple<std::string, std::string, std::string, double>
 */
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

/**
 * try to crack a single byte xor string
 *
 * @param crypted [in] the crypted string, hexadecimal encoded
 *
 * @return key, decrypted, score as std::tuple<std::string, std::string, double>
 */
tuple<string, string, double> crack(const string& crypted)
{
	list<string> possibleKeys;
	probePossibleKeys(crypted, &possibleKeys);

	list<tuple<string, string, double>> decryptedNScored;
	decryptAndScore(crypted, possibleKeys, &decryptedNScored);

	auto bestMatch = getBestMatch(decryptedNScored);
	// cout << "Decrypted: " << get<1>(bestMatch) << endl;

	return bestMatch;
}

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
		auto cracked = crack(crypted);
		bestMatches.push_back(make_tuple(crypted, get<0>(cracked), get<1>(cracked), get<2>(cracked)));
	}
	
	auto bestMatch = getBestMatch(bestMatches);

	cout << "Encrypted String: '" << get<0>(bestMatch) << "'" << endl;
	cout << "Key:              '" << get<1>(bestMatch) << "'" << endl;
	cout << "Decrypted:        '" << get<2>(bestMatch) << "'" << endl;

	return 0;
}

