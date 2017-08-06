#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdint>

#include "Hexadecimal.hpp"

using namespace std;

const string Hexadecimal::table = "0123456789ABCDEF";

string Hexadecimal::encode(const string& input)
{
  stringstream ss;
  
  ss << hex << setfill('0');
  for(size_t i = 0; input.length() > i; ++i)
  {
    ss << setw(2) << static_cast<unsigned int>(static_cast<unsigned char>(input[i]));
  }
  
  return ss.str(); 
}

string Hexadecimal::decode(const string& input)
{
  string output;
  
  if((input.length() % 2) != 0)
  {
    throw runtime_error("String is not valid length ...");
  }
  
  size_t cnt = input.length() / 2;
  
  for(size_t i = 0; cnt > i; ++i)
  {
    uint32_t s = 0;
    stringstream ss;
    ss << hex << input.substr(i * 2, 2);
    ss >> s;
    output.push_back(static_cast<unsigned char>(s));
  }
  
  return output;
}

