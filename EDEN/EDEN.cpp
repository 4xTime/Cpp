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


std::vector <std::vector<unsigned char>> EDEN::EncryptText(std::string data) {
	std::string text = data;
	std::string buffer_str;

	std::vector <std::vector<unsigned char>>enc;

	while (text.size() != 0) {
		if (text.size() >= 16) {
			for (int i = 0; i < 16; i++) {
				buffer_str += text[i];
			}

			text.erase(0, 16);
		}
		else if (text.size() != text.empty() && buffer_str.size() < 16) {
			int minChank = std::min(static_cast<int>(text.size()), 16);
			for (int i = 0; i < minChank; i++) {
				buffer_str += text[i];
			}
			text.erase(0, minChank);
		}
		if (buffer_str.size() < 16) {
			int spacesToAdd = 16 - buffer_str.size();
			for (int i = 0; i < spacesToAdd; i++) {
				buffer_str += padding_singe;
			}
			text.erase(0, spacesToAdd);
		}
		enc.push_back(aes.EncryptECB(convert_data(buffer_str), key));
		buffer_str.clear();
	}
	return enc;
}

std::vector<unsigned char> EDEN::DecryptText(std::vector <std::vector<unsigned char>>vec_DATA) {
	std::string DATA = GetEncryptedTextAsString(vec_DATA);

	std::vector<unsigned char> uchar_data;

	// Convert string to unsigned char array
	for (char c : DATA) {
		unsigned char uchar = static_cast<unsigned char>(c);
		uchar_data.push_back(uchar);
	}

	return aes.DecryptECB(uchar_data, key);
}

std::string EDEN::RemovePaddingFromString(std::string DATA) {

	size_t foundPos = DATA.find(padding_singe);

	while (foundPos != std::string::npos) {
		DATA.erase(foundPos, 1);
		foundPos = DATA.find(padding_singe, foundPos);
	}

	return DATA;
}