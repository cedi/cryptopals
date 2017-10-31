#include <iostream>
#include <string>

#include "Hexadecimal.hpp"
#include "XOR.hpp"

using namespace std;

int main()
{
  auto plaintext = Hexadecimal::decode("1c0111001f010100061a024b53535009181c");
  auto key = Hexadecimal::decode("686974207468652062756c6c277320657965");

  string xored = XOR::encode(plaintext, key);

  cout << xored << endl;
  cout << "746865206b696420646f6e277420706c6179" << endl;

  return 0;
}
