#include <algorithm>
#include <stdexcept>

#include "Hexadecimal.hpp"

using namespace std;

const char* const Hexadecimal::table = "0123456789ABCDEF";

string Hexadecimal::encode(const std::string& input)
{
    size_t len = input.length();

    std::string output;
    output.reserve(2 * len);
    for(size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(table[c >> 4]);
        output.push_back(table[c & 15]);
    }
    return output;
}

string Hexadecimal::decode(const std::string& input)
{
    size_t len = input.length();
    if(len & 1) 
    {
      throw std::invalid_argument("odd length");
    }

    std::string output;
    output.reserve(len / 2);
    for(size_t i = 0; i < len; i += 2)
    {
        char a = input[i];
        const char* p = std::lower_bound(table, table + 16, a);
        if(*p != a)
        {
          throw std::invalid_argument("not a hex digit");
        }

        char b = input[i + 1];
        const char* q = std::lower_bound(table, table + 16, b);
        if(*q != b)
        {
          throw std::invalid_argument("not a hex digit");
        }

        output.push_back(((p - table) << 4) | (q - table));
    }

    return output;
}


