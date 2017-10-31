#pragma once

#include <string>
#include <vector>

class Hexadecimal
{
private:
  static const std::string table;

public:
  static std::string encode(const std::string& input);
  static std::string encode(const std::vector<uint8_t>& input);
  static std::vector<uint8_t> decode(const std::string& input);
};
