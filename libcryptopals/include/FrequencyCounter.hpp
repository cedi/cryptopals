#pragma once

#include <map>
#include <string>

class CharFreqCntr
{
public:
	CharFreqCntr(std::string input, int charWidth);

	std::map<std::string, double> getSingleCharFreq(bool force=false);
	std::map<std::string, double> getDualCharFreq(bool force=false);
	std::map<std::string, double> getRepeatingChars(bool force=false);

protected:
	void analyzeSinglecharFreq();
	void analyzeDualCharFreq();
	void analyzeRepeatingChars();

private:
	std::string getChar(int offset);

// Member Variables
private:
	std::string input;
	int charWidth;

	std::map<std::string, double> singleCharFreq;
	std::map<std::string, double> dualCharFreq;
	std::map<std::string, double> repeatingCharFreq;
};
