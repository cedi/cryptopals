#pragma once

#include <string>

class Base64
{
private:
  static const char lookupTable[65];
  static const char reverseLookupTable[128];

  // Private constructor to prevent instantiation of the class
  Base64() {}

public:
  static std::string encode(const std::string &bindata)
  static std::string decode(const std::string &ascdata)
};
