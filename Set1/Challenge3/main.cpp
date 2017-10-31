#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <cstring>

#include "Hexadecimal.hpp"
#include "XOR.hpp"
#include "FrequencyCounter.hpp"
#include "TextScoring.hpp"
#include "Utils.hpp"

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

	auto result = XOR::crack(crypted);
	auto key = get<0>(result);
	auto decrypted = Hexadecimal::decode(get<1>(result));

	cout << "Key is:    '" << key << "'" << endl;
	cout << "Encrypted: '" << crypted << "'" << endl;
	cout << "Decrypted: '" << Utils::byteVecToStr(decrypted, "") << "'" << endl;
	return 0;
}


















