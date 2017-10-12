#include <stdexcept>

#include "XOR.hpp"
#include "Hexadecimal.hpp"
#include "FrequencyCounter.hpp"
#include "TextScoring.hpp"

using namespace std;

string XOR::encode(const string& data, const string& inputKey)
{
	string key = inputKey;
	while(key.length() < data.length())
	{
		key += inputKey;
	}

	if(key.length() > data.length())
	{
		key = key.substr(0, data.length());
	}

	if(data.length() != key.length())
	{
		throw length_error("data and length aren't equal");
	}

	size_t strLen = data.length();
	string encoded;

	for(int i = 0; i < strLen; ++i)
	{
		auto s = static_cast<char>(data[i] ^ key[i]);
		encoded.append(1, s);
	}

	return encoded;
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

tuple<string, string, double> XOR::getBestMatch(const list<tuple<string, string, double>>& decryptedNScored)
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

tuple<string, string, string, double> XOR::getBestMatch(const list<tuple<string, string, string, double>>& cryptedKeyDecryptedNScored)
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
	string chipertext = Hexadecimal::decode(crypted);

	for(auto key : possibleKeys)
	{
		string decoded = XOR::encode(chipertext, key);
		TextScoring scoring(Hexadecimal::encode(decoded));
		double score = scoring.analyze(TextScoring::PRINTABLE, TextScoring::DECODE_HEX);

		decryptedNScored->push_back(make_tuple(key, decoded, score));
	}
}

void XOR::probePossibleKeys(const string& crypted, list<string>* possibleKeys)
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

