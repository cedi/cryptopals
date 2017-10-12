#pragma once

#include <string>
#include <tuple>
#include <list>

class XOR
{
public:

	/**
	 * crypt some data with a key
	 *
	 * @param data the data which should be crypted
	 * 
	 * @param key the key whitch is used to encrypt the data
	 *
	 * @note if the key is shorter than data, the key is repeated.
	 * So please make sure, you always pass in a key with the same size than
	 * data in order to get a safe result...
	 * If the key is longer than data, the key is trimed to the right length.
	 */
	static std::string
		encode(const std::string& data, const std::string& key);

	/**
	 * try to crack a single byte xor string
	 *
	 * @param crypted [in] the crypted string, hexadecimal encoded
	 *
	 * @return key, decrypted, score as std::tuple<std::string, std::string, double>
	 */
	static std::tuple<std::string, std::string, double>
		crack(const std::string& crypted);

	/**
	 * get the best match of a list containing the key, the decrypted string and the
	 * score. The list is represented as
	 * std::list<std::tuple<std::string, std::string, double>>
	 *
	 * @param decryptedNScored [in] the list with entrys from whitch the best
	 * score should be determined and returned
	 * 
	 * @return the entry of the list with the highest score as 
	 * std::tuple<std::string, std::string, double>
	 */
	static std::tuple<std::string, std::string, double>
		getBestMatch(
				const std::list<std::tuple<std::string, std::string, double>>& decryptedNScored
			);
	/**
	 * get the best match of a list containing the crypted string, the key, the
	 * decrypted string and the score.
	 * The list is represented as
	 * std::list<std::tuple<std::string, std::string, std::string, double>>
	 *
	 * @param cryptedKeyDecryptedNScored [in] the list with entrys from whitch the best
	 * score should be determined and returned
	 * 
	 * @return the entry of the list with the highest score as 
	 * std::tuple<std::string, std::string, std::string, double>
	 */
	static std::tuple<std::string, std::string, std::string, double>
		getBestMatch(
				const std::list<std::tuple<std::string, std::string, std::string, double>>& cryptedKeyDecryptedNScored
			);


private:
	/**
	 * Decrypt a string using a list of possible keys, score them and return
	 * everything by inserting the key, the decoded message and the score in a list
	 *
	 * @param crypted [in] the decrypted message 
	 * @param possibleKeys [in] the possible keys 
	 * @param decryptedNScored [out] the list in which the results are inserted.
	 */
	static void decryptAndScore(
		const std::string& crypted, const std::list<std::string>& possibleKeys,
		std::list<std::tuple<std::string, std::string, double>>* decryptedNScored
	);
	
	/**
 	* Probe for possible keys
 	*
 	* @param crypted [in] the decrypted string
 	* @param possibleKeys [out] the possible keys, inserted to a list
 	*/
	static void probePossibleKeys(
			const std::string& crypted, std::list<std::string>* possibleKeys
		);
};
