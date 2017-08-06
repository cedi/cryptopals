#pragma once

#include <map>
#include <string>

class CharFreqCntr
{
public:
  CharFreqCntr(std::string input, int charWidth);

  std::map<std::string, double> getSingleCharFreq();
  std::map<std::string, double> getDualCharFreq();
  std::map<std::string, double> getRepeatingChars();

private:
  std::string getChar(int offset);

// Member Variables
private:
  std::string input;
  int charWidth;
};
