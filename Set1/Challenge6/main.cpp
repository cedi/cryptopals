#include <iostream>
#include <string>

#include "HammingDistance.hpp"
#include "Utils.hpp"

using namespace std;

int main()
{
	cout << "*****************************************" << endl;
	cout << "*        Break Repeating key XOR        *" << endl;
	cout << "*****************************************" << endl << endl;

	int hd = HammingDistance::calc("this is a test", "wokka wokka!!!");
	cout << "Hamming Distance between 'this is a test' and 'wokka wokka!!!' is: " << hd << endl;
}
