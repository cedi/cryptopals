#pragma once

#include "string"

class HammingDistance
{
private:
    HammingDistance() {} // private constructor, prevent from creating a object
    ~HammingDistance() {} // private destructor

public:
    /// calculate the hamming distance between two strings
    /// 
    /// @param left the first string
    /// @param right the second string to compare against
    ///
    /// @details The string is passed byte by byte to 
    /// static int calc(unsigned left, unsigned right)
    /// in order to calculate the HD. Thats because
    /// hd(s1, s2) = ∑[c] hd(s1[c], s2[c]);
    ///
    /// @return the number of different bits
	static int calc(std::string left, std::string right);

    /// calculate the hamming distance
    /// 
    /// @param left the first byte
    /// @param right the second byte to compare against
    ///
    /// @return the number of different bits
	static int calc(unsigned left, unsigned right);
};
