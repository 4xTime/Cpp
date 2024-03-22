#include "EDEN.h"

std::string EDEN::GetEncryptedTextAsString(std::vector <std::vector<unsigned char>> data) {
	std::string s_data;

	s_data.reserve(data.size() * data[0].size());

	for (const auto& mother_vec : data) {
		for (const auto& child_vec : mother_vec) {
			s_data += child_vec;
		}
	}
	return s_data;
}

std::string EDEN::GetDecryptedTextAsString(std::vector <unsigned char> data) {
	std::string s_data;
	
	s_data.reserve(data.size());

	for (auto& mother_vec : data) {
		s_data += mother_vec;
	}
	return s_data;
}

std::vector<std::vector<unsigned char>> EDEN::EncryptText(std::string data) {
	std::vector<std::vector<unsigned char>> enc;

	std::vector<unsigned char>encBuffer;

	// Reserve space
	encBuffer.reserve(16);

	size_t pos = 0;

	while (pos < data.size()) {
		size_t chunkSize = std::min<size_t>(16, data.size() - pos);
		std::string buffer_str = data.substr(pos, chunkSize);
		pos += chunkSize;

		if (buffer_str.size() < 16) {
			buffer_str.append(16 - buffer_str.size(), padding_singe);
		}

		for (size_t i = 0; i < buffer_str.size(); ++i) {
			encBuffer.push_back(buffer_str[i]);
		}

		enc.push_back(aes.EncryptECB(encBuffer, c_key));
		encBuffer.clear();
	}

	return enc;
}

std::vector<unsigned char> EDEN::DecryptText(std::vector <std::vector<unsigned char>>vec_DATA) {
	std::vector<unsigned char> uchar_data;
	
	// Reserve space
	uchar_data.reserve(vec_DATA.size() * vec_DATA[0].size());

	// Converte data to unsigned char 
	for (char vec : GetEncryptedTextAsString(vec_DATA)) {
		uchar_data.push_back(static_cast<unsigned char>(vec));
	}
	
	return aes.DecryptECB(uchar_data, c_key);
}

std::string EDEN::RemovePaddingFromString(std::string DATA) {

	size_t foundPos = DATA.find(padding_singe);

	while (foundPos != std::string::npos) {
		DATA.erase(foundPos, 1);
		foundPos = DATA.find(padding_singe, foundPos);
	}

	return DATA;
}