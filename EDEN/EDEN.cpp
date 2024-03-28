#include "EDEN.h"

std::string EDEN::GetEncryptedTextAsString(vector2UC data) {
	std::string s_data;

	s_data.reserve(data.size() * data[0].size());

	for (const auto& motherVec : data) {
		for (const auto& childVec : motherVec) {
			s_data += childVec;
		}
	}
	return s_data;
}

std::string EDEN::GetDecryptedTextAsString(vectorUC data) {
	std::string s_data;

	s_data.reserve(data.size());

	for (auto& motherVec : data) {
		s_data += motherVec;
	}
	return s_data;
}

vector2UC EDEN::EncryptText(std::string data) {
	vector2UC enc;

	vectorUC encBuffer;

	// Reserve space
	encBuffer.reserve(BITSNUM);

	size_t pos = 0;

	while (pos < data.size()) {
		size_t chunkSize = std::min<size_t>(BITSNUM, data.size() - pos);
		std::string buffer_str = data.substr(pos, chunkSize);
		pos += chunkSize;

		if (buffer_str.size() < BITSNUM) {
			buffer_str.append(BITSNUM - buffer_str.size(), padding_singe);
		}

		for (size_t i = 0; i < buffer_str.size(); ++i) {
			encBuffer.push_back(buffer_str[i]);
		}

		switch (c_type)
		{
		case ECB:
			enc.push_back(aes.EncryptECB(encBuffer, c_key));
			break;
		case CBC:
			enc.push_back(aes.EncryptCBC(encBuffer, c_key, c_iv));
			break;
		case CFB:
			enc.push_back(aes.EncryptCFB(encBuffer, c_key, c_iv));
			break;
		default:
			break;
		}
		encBuffer.clear();
	}

	return enc;
}

vectorUC EDEN::DecryptText(vector2UC vecDATA) {
	vectorUC uchar_data;
	vectorUC decryptedVecUC;
	vector2UC decryptedChunkData2d;

	// Reserve space
	uchar_data.reserve(vecDATA.size() * vecDATA[0].size());
	decryptedVecUC.reserve(vecDATA.size() * vecDATA[0].size());
	decryptedChunkData2d.reserve(vecDATA.size());

	if (c_type == ECB) {
		for (char vec : GetEncryptedTextAsString(vecDATA)) {
			uchar_data.push_back(static_cast<unsigned char>(vec));
		}
		return aes.DecryptECB(uchar_data, c_key);
	}
	else if(c_type != ECB) {// (:
		size_t pos = 0;

		for (char vec : GetEncryptedTextAsString(vecDATA)) {
			uchar_data.push_back(static_cast<unsigned char>(vec));
		}

		std::string strData;
		for (auto i : uchar_data) {
			strData += i;
		}
		
		while (pos < uchar_data.size()) {
			size_t chunkSize = std::min<size_t>(BITSNUM, uchar_data.size() - pos);
			std::string buffer_str = strData.substr(pos, chunkSize);
			pos += chunkSize;

			std::vector<unsigned char> temp;
			if (buffer_str.size() <= BITSNUM) {
				for (char c : buffer_str) {
					temp.push_back(static_cast<unsigned char>(c));
				}
				switch (c_type)
				{
				case CBC:
					decryptedChunkData2d.push_back(aes.DecryptCBC(temp, c_key, c_iv));
					break;
				case CFB:
					decryptedChunkData2d.push_back(aes.DecryptCFB(temp, c_key, c_iv));
					break;
				default:
					break;
				}
			}
		}
		for (auto motherVec : decryptedChunkData2d) {
			for (auto childVec : motherVec) {
				decryptedVecUC.push_back(childVec);
			}
		}
		return decryptedVecUC;
	}
}

std::string EDEN::RemovePaddingFromString(std::string DATA) {

	size_t foundPos = DATA.find(padding_singe);

	while (foundPos != std::string::npos) {
		DATA.erase(foundPos, 1);
		foundPos = DATA.find(padding_singe, foundPos);
	}

	return DATA;
}