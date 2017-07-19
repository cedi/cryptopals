#include <cassert>
#include <limits>
#include <stdexcept>
#include <cctype>

#include "Base64.hpp"

using namespace std;

const char Base64::lookupTable[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

const char Base64::reverseLookupTable[128] =
{
   64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
   64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
     64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
   52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
   64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
   15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
   64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
   41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64
};

string Base64::encode(const string &bindata)
{
  if(bindata.size() > (numeric_limits<string::size_type>::max() / 4u) * 3u)
  {
     throw length_error("Converting too large a string to base64.");
  }

  const size_t binlen = bindata.size();

  // Use = signs so the end is properly padded.
  string retval((((binlen + 2) / 3) * 4), '=');
  size_t outpos = 0;
  int bits_collected = 0;
  unsigned int accumulator = 0;
  const string::const_iterator binend = bindata.end();

  for(string::const_iterator i = bindata.begin(); i != binend; ++i) 
  {
    accumulator = (accumulator << 8) | (*i & 0xffu);
    bits_collected += 8;
    while(bits_collected >= 6) 
     {
       bits_collected -= 6;
       retval[outpos++] = lookupTable[(accumulator >> bits_collected) & 0x3fu];
     }
  }
  
  // Any trailing bits that are missing.
  if(bits_collected > 0)
  {
    accumulator <<= 6 - bits_collected;
    retval[outpos++] = lookupTable[accumulator & 0x3fu];
  }

  return retval;
}

string Base64::decode(const string &ascdata)
{
  string retval;
  const string::const_iterator last = ascdata.end();
  int bits_collected = 0;
  unsigned int accumulator = 0;

  for (string::const_iterator i = ascdata.begin(); i != last; ++i)
  {
    const int c = *i;
    
    // Skip whitespace and padding. Be liberal in what you accept.
    if(isspace(c) || c == '=')
    {
      continue;
    }

    if((c > 127) || (c < 0) || (reverseLookupTable[c] > 63))
    {
      throw invalid_argument("This contains characters not legal in a base64 encoded string.");
    }

    accumulator = (accumulator << 6) | reverseLookupTable[c];
    bits_collected += 6;
    if(bits_collected >= 8)
    {
      bits_collected -= 8;
      retval += (char)((accumulator >> bits_collected) & 0xffu);
    }
  }

  return retval;
}

