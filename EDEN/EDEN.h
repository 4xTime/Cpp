#pragma once
#ifndef H_EDEN_H
#define H_EDEN_H
#include <vector>
#include "AES\AES.h"

typedef std::vector<std::vector<unsigned char>> vector2UC;
typedef std::vector<unsigned char> vectorUC;

enum edenType {
	ECB = 1,
	CBC = 2,
	CFB=3,
};

class EDEN {
private:
	const unsigned int BITSNUM = 16;
	const unsigned char padding_singe = '�';
	//const unsigned char padding_singe = 'A';
	AES aes;
	
	vectorUC c_key;
	vectorUC c_iv;
	edenType c_type;
public:
	EDEN(AESKeyLength AESKeyLenght, vectorUC key, edenType EDEN_TYPE, vectorUC iv = vectorUC(0)) {
		AES f_aes(AESKeyLenght);
		aes = f_aes;

		c_key = key;
		c_iv = iv;
		c_type = EDEN_TYPE;
	}

	vector2UC EncryptText(std::string data);
	vectorUC  DecryptText(vector2UC vecDATA);

	std::string GetEncryptedTextAsString(vector2UC data);
	std::string GetDecryptedTextAsString(vectorUC data);

	std::string RemovePaddingFromString(std::string DATA);
};
#endif