#include <stdexcept>

#include "XOR.hpp"

using namespace std;

string XOR::encode(string data, string key)
{
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
