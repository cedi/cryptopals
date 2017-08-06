#include <iostream>
#include <string>
#include <map>
#include <sstream>

#include "include/Hexadecimal.hpp"
#include "include/XOR.hpp"
#include "include/FrequencyCounter.hpp"

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

	auto singleChar = freq.getSingleCharFreq();

#if 0
  cout << "Single Character Occurrences:" << endl;
  printKV(singleChar);
  
	auto dualChar = freq.getDualCharFreq();
  cout << "Dual Character Occurrences:" << endl;
  printKV(dualChar);

	auto repeatingChar = freq.getRepeatingChars();
  cout << "Repeating Chars:" << endl;
  printKV(repeatingChar);
#endif

  cout << "Try to break it" << endl;
  string character;
  for(int i = 0; i < 256; i++)
  {
    stringstream ss;
    ss << (char)i;

    string encrypted = Hexadecimal::encode(XOR::encode(" ", ss.str()));
    if(encrypted == "78")
    {
      character = ss.str();
      cout << "Key seems to be: " << character << endl;
      break;
    }
  }

  string chipertext = Hexadecimal::decode(crypted);
  char* key = (char*)malloc(chipertext.size() + 1);
  memset(key, character.c_str()[0], chipertext.size());
  key[chipertext.size()] = '\0';

  cout << "Encrypted: " << chipertext.size() << ": '" << chipertext << "'" << endl;
  cout << "Key:       " << strlen(key) << ": '" << key << "'" << endl;

  string decoded = XOR::encode(chipertext, key);
  cout << "Decrypted: " << decoded.size() << ": '" << decoded << "'" << endl;


  return 0;
}


















