#pragma once

#include <string>
#include <vector>

class Base64
{
private:
  static const char lookupTable[65];
  static const char reverseLookupTable[128];
  
  // Private constructor to prevent instantiation of the class
  Base64() {}

public:
  static std::string encode(const std::vector<uint8_t> &bindata);
  static std::vector<uint8_t> decode(const std::string &ascdata);
};
