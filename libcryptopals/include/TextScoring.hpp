#pragma once

#include <map>
#include <string>
#include <vector>

class TextScoring
{
public:
	enum DecodeFlags 
	{
		DECODE_HEX
	};

	enum AnalyzeFlags 
	{
		PRINTABLE	= 0x01
	};

	TextScoring(std::string input, DecodeFlags dFlags);

	double analyze(AnalyzeFlags aFlags) const;

private:
	double analyzePrintables() const;

// Member Variables
private:
	std::vector<uint8_t> input;
};
