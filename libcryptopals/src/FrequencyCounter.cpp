#include <sstream>
#include "iostream"

#include "FrequencyCounter.hpp"

using namespace std;

CharFreqCntr::CharFreqCntr(std::string input, int charWidth)
	: input(input)
	, charWidth(charWidth)
{
}

map<string, double> CharFreqCntr::getSingleCharFreq(bool force)
{
	if(force || singleCharFreq.empty())
	{
		analyzeSinglecharFreq();
	}

	return singleCharFreq;
}

map<string, double> CharFreqCntr::getDualCharFreq(bool force)
{
	if(force || dualCharFreq.empty())
	{
		analyzeDualCharFreq();
	}

	return dualCharFreq;
}

map<string, double> CharFreqCntr::getRepeatingChars(bool force)
{
	if(force || repeatingCharFreq.empty())
	{
		analyzeRepeatingChars();
	}

	return repeatingCharFreq;
}


void CharFreqCntr::analyzeSinglecharFreq()
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

	singleCharFreq = occurrences;
}

void CharFreqCntr::analyzeDualCharFreq()
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

	dualCharFreq = occurrences;
}

void CharFreqCntr::analyzeRepeatingChars()
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

	repeatingCharFreq = occurrences;
}


string CharFreqCntr::getChar(int offset)
{
	return string(input, offset, charWidth);
}
