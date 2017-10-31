#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdint>

#include "Hexadecimal.hpp"
#include "Utils.hpp"

using namespace std;

const string Hexadecimal::table = "0123456789ABCDEF";

string Hexadecimal::encode(const string& input)
{
	vector<uint8_t> vec;
	for(char c : input)
	{
		vec.push_back(static_cast<uint8_t>(c));
	}

	return encode(Utils::strToByteVec(input));
}

string Hexadecimal::encode(const vector<uint8_t>& input)
{
  stringstream ss;
  
  ss << hex << setfill('0');
  for(size_t i = 0; input.size() > i; ++i)
  {
    ss << setw(2) << static_cast<unsigned int>(input[i]);
  }
  
  return ss.str(); 
}

vector<uint8_t> Hexadecimal::decode(const string& input)
{
  
  if((input.length() % 2) != 0)
  {
    throw runtime_error("String is not valid length ...");
  }
  
  vector<uint8_t> output;
  size_t cnt = input.length() / 2;
  
  for(size_t i = 0; cnt > i; ++i)
  {
    uint32_t s = 0;
    stringstream ss;
    ss << hex << input.substr(i * 2, 2);
    ss >> s;
    output.push_back(static_cast<uint8_t>(s));
  }
  
  return output;
}

