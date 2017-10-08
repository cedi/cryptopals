#include <sstream>
#include "iostream"

#include "FrequencyCounter.hpp"

using namespace std;

CharFreqCntr::CharFreqCntr(std::string input, int charWidth)
  : input(input)
  , charWidth(charWidth)
{
}

map<string, double> CharFreqCntr::getSingleCharFreq()
{
  if((input.size() % 2) != 0)
  {
    throw invalid_argument("StringLen not correct padded");
  }

  map<string, double> occurrences;
  for(int i = 0; i < input.size(); i += charWidth)
  {
    string myChar = getChar(i);
    
    auto ret = occurrences.insert(make_pair(myChar, 1));
    if(ret.second == false)
    {
      int count = ret.first->second;
      count++;
      ret.first->second = count;
    }
  }

  return occurrences;
}

map<string, double> CharFreqCntr::getDualCharFreq()
{
  if((input.size() % 2) != 0)
  {
    throw invalid_argument("StringLen not correct padded");
  }

  map<string, double> occurrences;
  for(int i = 0; i < input.size(); i += charWidth * 2)
  {
    string myChar;
    {
      string myChar1 = getChar(i);
      string myChar2 = getChar(i + charWidth);
      myChar = myChar1 + myChar2;
    }
    
    auto ret = occurrences.insert(make_pair(myChar, 1));
    if(ret.second == false)
    {
      int count = ret.first->second;
      count++;
      ret.first->second = count;
    }
  }

  return occurrences;
}

map<string, double> CharFreqCntr::getRepeatingChars()
{
  if((input.size() % 4) != 0)
  {
    throw invalid_argument("StringLen not correct padded");
  }

  map<string, double> occurrences;
  for(int i = 0; i < input.size(); i += charWidth)
  {
    string myChar1 = getChar(i);
    string myChar2 = getChar(i + charWidth);

    if(myChar1 != myChar2)
    {
      continue;
    }
    
    auto ret = occurrences.insert(make_pair(myChar1, 1));
    if(ret.second == false)
    {
      int count = ret.first->second;
      count++;
      ret.first->second = count;
    }
  }

  return occurrences;
}


string CharFreqCntr::getChar(int offset)
{
  return string(input, offset, charWidth);
}
