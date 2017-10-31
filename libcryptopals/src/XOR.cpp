#include <stdexcept>
#include <iostream>
#include <vector>

#include "XOR.hpp"
#include "Hexadecimal.hpp"
#include "FrequencyCounter.hpp"
#include "TextScoring.hpp"
#include "Utils.hpp"

using namespace std;

string XOR::encode(const vector<uint8_t>& data, const vector<uint8_t>& inputKey)
{
	vector<uint8_t> key = inputKey;
	while(key.size() < data.size())
	{
		key.insert(end(key), begin(inputKey), end(inputKey));
	}

	if(key.size() > data.size())
	{
		key.erase(begin(key) + data.size(), end(key));
	}

	if(data.size() != key.size())
	{
		throw length_error("data and length aren't equal");
	}

	cout << "Data: " << Utils::byteVecToStr(data, "") << endl;
	cout << "Key:  " << Utils::byteVecToStr(key, "") << endl;

	size_t strLen = data.size();
	vector<uint8_t> encoded;

	for(int i = 0; i < strLen; ++i)
	{
		auto s = data[i] ^ key[i];
		encoded.push_back(s);
	}

	return Hexadecimal::encode(encoded);
}

tuple<string, string, double> XOR::crack(const string& crypted)
{
	list<string> possibleKeys;
	probePossibleKeys(crypted, &possibleKeys);

	list<tuple<string, string, double>> decryptedNScored;
	decryptAndScore(crypted, possibleKeys, &decryptedNScored);

	auto bestMatch = getBestMatch(decryptedNScored);
	// cout << "Decrypted: " << get<1>(bestMatch) << endl;

	return bestMatch;
}

tuple<string, string, double>
		XOR::getBestMatch(
			const list<tuple<string, string, double>>& decryptedNScored
		)
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

tuple<string, string, string, double>
		XOR::getBestMatch(
				const list<tuple<string, string, string, double>>& cryptedKeyDecryptedNScored
			)
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


void XOR::decryptAndScore(
		const string& crypted, const list<string>& possibleKeys,
		list<tuple<string, string, double>>* decryptedNScored
	)
{
	// Now try to decrypt the encrypted text using the above calculated keys
	// and analyze every result using the TextScoring class
	auto chipertext = Hexadecimal::decode(crypted);

	for(auto key : possibleKeys)
	{
		auto decoded = XOR::encode(chipertext, Utils::strToByteVec(key));

		TextScoring scoring(decoded, TextScoring::DECODE_HEX);
		double score = scoring.analyze(TextScoring::PRINTABLE);

		decryptedNScored->push_back(make_tuple(key, decoded, score));
	}
}

void XOR::probePossibleKeys(const string& crypted, list<string>* possibleKeys)
{
	CharFreqCntr freq(crypted, 2);
	freq.getFrequency(CharFreqCntr::SINGLE);

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
			string encrypted = XOR::encode(Utils::strToByteVec(string(1, possibleCurrentChar)), Utils::strToByteVec(toProbe));

			if(encrypted == freq.getMostOccurent(CharFreqCntr::SINGLE))
			{
				possibleKeys->push_back(toProbe);
			}
		}
	}
}

