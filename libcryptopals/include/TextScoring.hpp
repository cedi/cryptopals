#pragma once

#include <map>
#include <string>

class TextScoring
{
public:
	TextScoring(std::string input);

	enum DecodeFlags 
	{
		NO_DECODE,
		DECODE_BASE64,
		DECODE_HEX
	};

	enum AnalyzeFlags 
	{
		PRINTABLE	= 0x01
	};

	double analyze(AnalyzeFlags aFlags, DecodeFlags dFlags) const;

private:
	double analyzePrintables(std::string toAnalyze) const;

// Member Variables
private:
	std::string input;
};
