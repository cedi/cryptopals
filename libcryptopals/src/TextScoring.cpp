#include <sstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <cctype>

#include "TextScoring.hpp"
#include "Hexadecimal.hpp"
#include "Base64.hpp"

using namespace std;

TextScoring::TextScoring(string input, DecodeFlags dFlags)
{
	switch(dFlags)
	{
	case DecodeFlags::DECODE_HEX:
		this->input = Hexadecimal::decode(input);
		break;

	default:
		stringstream ss;
		ss << "Invalid DecodeFlag: " << dFlags << endl;
		throw invalid_argument(ss.str());
	}
}

double TextScoring::analyze(AnalyzeFlags aFlags) const
{
	double score = 0;
	int analyzerCnt = 0;

	if((aFlags & AnalyzeFlags::PRINTABLE) == AnalyzeFlags::PRINTABLE)
	{
		score += analyzePrintables();
		analyzerCnt++;
	}

	return analyzerCnt ? (score / (double)analyzerCnt) : 0;
}

double TextScoring::analyzePrintables() const
{
	int printables = 0;

	for(uint8_t c : input)
	{
		if(isprint(static_cast<char>(c)))
		{
			printables++;
		}
	}

	return (double)printables / (double)input.size();
}
