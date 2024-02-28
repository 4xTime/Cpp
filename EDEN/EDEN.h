#pragma once
#include <vector>
#include "AES\AES.h"
class EDEN {
private:
	const int BITSNUM = 16;
	const unsigned char padding_singe = '°';
	//const unsigned char padding_singe = 'A';
	AES aes;
	std::vector<unsigned char> key = {
	0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xEF, 0xFE, 0xDC,
	0xBA, 0x98, 0x76, 0x54, 0x32, 0x10, 0xAB, 0xCD, 0xEF, 0x00
	};

	std::vector<unsigned char> convert_data(std::string data);
public:
	EDEN(AESKeyLength AESKeyLenght) {
		AES f_aes(AESKeyLenght);
		aes = f_aes;
	}

	std::string GetEncryptedTextAsString(std::vector <std::vector<unsigned char>> data);

	std::string GetDecryptedTextAsString(std::vector <unsigned char> data);

	std::vector <std::vector<unsigned char>> EncryptText(std::string data);

	std::vector<unsigned char>  DecryptText(std::vector <std::vector<unsigned char>>vec_DATA);
	std::string RemovePaddingFromString(std::string DATA);
};