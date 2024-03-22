#pragma once
#ifndef  H_EDEN_H
#define H_EDEN_H
#include <vector>
#include "AES\AES.h"
class EDEN {
private:
	const int BITSNUM = 16;
	const unsigned char padding_singe = '�';
	//const unsigned char padding_singe = 'A';
	AES aes;
	std::vector<unsigned char> c_key;

	std::vector<unsigned char> convert_data(std::string data);

public:
	EDEN(AESKeyLength AESKeyLenght, std::vector<unsigned char> key) {
		AES f_aes(AESKeyLenght);
		aes = f_aes;

		if (key.size() < 16) {
			fprintf(stderr, "Error: Key lenght\n");
			exit(EXIT_FAILURE);
		}
		c_key = key;
	}

	std::string GetEncryptedTextAsString(std::vector <std::vector<unsigned char>> data);

	std::string GetDecryptedTextAsString(std::vector <unsigned char> data);

	std::vector <std::vector<unsigned char>> EncryptText(std::string data);

	std::vector<unsigned char>  DecryptText(std::vector <std::vector<unsigned char>>vec_DATA);
	std::string RemovePaddingFromString(std::string DATA);
};
#endif