#pragma once

#include <string>

class Hexadecimal
{
private:
  static const std::string table;

public:
  static std::string encode(const std::string& input);
  static std::string decode(const std::string& input);
};
