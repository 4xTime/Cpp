#include "EDEN.h"

std::vector<unsigned char> EDEN::convert_data(std::string data) {
	std::vector<unsigned char> v_data;
	for (int i = 0; i < data.size(); ++i) {
		v_data.push_back(data[i]);
	}
	return v_data;
}

std::string EDEN::GetEncryptedTextAsString(std::vector <std::vector<unsigned char>> data) {
	std::string s_data;
	for (auto& mother_vec : data) {
		for (auto& child_vec : mother_vec) {
			s_data += child_vec;
		}
	}
	return s_data;
}

std::string EDEN::GetDecryptedTextAsString(std::vector <unsigned char> data) {
	std::string s_data;
	for (auto& mother_vec : data) {
		s_data += mother_vec;
	}
	return s_data;
}


std::vector<std::vector<unsigned char>> EDEN::EncryptText(std::string data) {
	std::vector<std::vector<unsigned char>> enc;
	size_t pos = 0;

	while (pos < data.size()) {
		size_t chunkSize = std::min<size_t>(16, data.size() - pos);
		std::string buffer_str = data.substr(pos, chunkSize);
		pos += chunkSize;

		if (buffer_str.size() < 16) {
			buffer_str.append(16 - buffer_str.size(), padding_singe);
		}

		enc.push_back(aes.EncryptECB(convert_data(buffer_str), c_key));
	}

	return enc;
}

std::vector<unsigned char> EDEN::DecryptText(std::vector <std::vector<unsigned char>>vec_DATA) {
	std::string DATA = GetEncryptedTextAsString(vec_DATA);

	std::vector<unsigned char> uchar_data;

	// Convert string to unsigned char array
	for (char Char : DATA) {
		uchar_data.push_back(static_cast<unsigned char>(Char));
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