#include <sstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <cctype>

#include "TextScoring.hpp"
#include "Hexadecimal.hpp"
#include "Base64.hpp"

using namespace std;

TextScoring::TextScoring(std::string input)
	: input(input)
{
}

double TextScoring::analyze(AnalyzeFlags aFlags, DecodeFlags dFlags) const
{
	double score = 0;
	int analyzerCnt = 0;
	string toAnalyze;

	switch(dFlags)
	{
	case DecodeFlags::NO_DECODE:
		toAnalyze = input;
		break;

	case DecodeFlags::DECODE_HEX:
		toAnalyze = Hexadecimal::decode(input);
		break;

	case DecodeFlags::DECODE_BASE64:
		toAnalyze = Base64::decode(input);
		break;

	default:
		stringstream ss;
		ss << "Invalid DecodeFlag: " << dFlags << endl;
		throw invalid_argument(ss.str());
	}

	if((aFlags & AnalyzeFlags::PRINTABLE) == AnalyzeFlags::PRINTABLE)
	{
		score += analyzePrintables(toAnalyze);
		analyzerCnt++;
	}

	return analyzerCnt ? (score / (double)analyzerCnt) : -0.5;
}

double TextScoring::analyzePrintables(string toAnalyze) const
{
	int printables = 0;

	for(char c : toAnalyze)
	{
		if(isprint(c))
		{
			printables++;
		}
	}

	return (double)printables / (double)toAnalyze.length();
}
