#include <iostream>
#include <string>
#include "Hexadecimal.hpp"
#include "XOR.hpp"

using namespace std;

int main()
{
	cout << "***********************************" << endl;
	cout << "*        Repeating key XOR        *" << endl;
	cout << "***********************************" << endl << endl;
	string line1 = "Burning 'em, if you ain't quick and nimble";
	string line2 = "I go crazy when I hear a cymbal";
	
	string key = "ICE";

	string crypted1 = Hexadecimal::encode(XOR::encode(line1, key));

	cout << "Is crypted:  ";
	cout << crypted1 <<  endl;
	cout << "Should be:   ";
	cout << "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272" << endl;

	cout << endl;

	string crypted2 = Hexadecimal::encode(XOR::encode(line2, key));
	cout << "Is crypted:  ";
	cout << crypted2 <<  endl;
	cout << "Should be:   ";
	cout << "a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f" << endl;
}
