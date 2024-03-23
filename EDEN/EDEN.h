#pragma once
#ifndef H_EDEN_H
#define H_EDEN_H
#include <vector>
#include "AES\AES.h"

typedef std::vector<std::vector<unsigned char>> vector2UC;
typedef std::vector<unsigned char> vectorUC;

class EDEN {
private:
	const unsigned int BITSNUM = 16;
	const unsigned char padding_singe = '�';
	//const unsigned char padding_singe = 'A';
	AES aes;
	std::vector<unsigned char> c_key;

public:
	EDEN(AESKeyLength AESKeyLenght, std::vector<unsigned char> key) {
		AES f_aes(AESKeyLenght);
		aes = f_aes;

		if (key.size() < BITSNUM) {
			fprintf(stderr, "Error: Key lenght\n");
			exit(EXIT_FAILURE);
		}
		c_key = key;
	}

	std::string GetEncryptedTextAsString(std::vector <std::vector<unsigned char>> data);
	vector2UC EncryptText(std::string data);

	std::string GetDecryptedTextAsString(std::vector <unsigned char> data);
	vectorUC  DecryptText(std::vector <std::vector<unsigned char>>vecDATA);

	std::string RemovePaddingFromString(std::string DATA);
};
#endif