#pragma once

#include <vector>
#include <string>
#include <sstream>

class Utils
{
public:
	static std::vector<uint8_t> strToByteVec(std::string str)
	{
		std::vector<uint8_t> vec;
		for(char c : str)
		{
			vec.push_back(static_cast<uint8_t>(c));
		}
	
		return vec;
	}
	
	static std::string
		byteVecToStr(
			std::vector<uint8_t> v, 
			std::string separator = ","
		)
	{
		std::stringstream ss;
		for(size_t i = 0; i < v.size(); ++i)
		{
			if(i != 0)
				ss << separator;
			
			ss << v[i];
		}
	
		return ss.str();
	}
};
