#include "Util.hpp"

bool Util::checkIfDirExistOrCreate() {
	if (std::filesystem::is_directory(std::filesystem::path(ck2mModFolder))) {
		return true;
	}
	else {
		if (std::filesystem::create_directory(ck2mModFolder))
			return true;
		return false;
	}
	return false;
}

bool Util:: checkIfModDataFolderExistOrCreate() {
	if (!std::filesystem::exists(ck2mConfigFile)) {
		std::ofstream File(ck2mConfigFile, std::ios::out);

		if (!std::filesystem::exists(ck2mConfigFile)) {
			return false;
		}

		File << "[Mods Packs]\n";
		File << "\n[Mods]\n";
		return true;
	}
	return true;
}

void Util::checkIfModsUsedLineExistIfNotCreate(std::string ck2ModFile) {
	std::fstream FileCk2ModFile(ck2ModFile, std::ios::in | std::ios::out);
	int lineItteratr = 0;
	std::string line;
	std::vector<std::string>fileLinesBuffer;
	if (FileCk2ModFile.is_open()) {
		while (std::getline(FileCk2ModFile, line)) {
			lineItteratr++;
			fileLinesBuffer.push_back(line);
		}
		bool lastModsFound = false;
		for (int i = 0; i < lineItteratr; i++) {
			std::size_t found = fileLinesBuffer[i].find("last_mods=");
			if (found != std::string::npos) {
				lastModsFound = true;
			}
		}
		if (!lastModsFound) {
			fileLinesBuffer.push_back("last_mods=\n{\n}");
			lineItteratr++;
			FileCk2ModFile.clear();
			FileCk2ModFile.seekp(0, std::ios::beg);
			for (int i = 0; i < lineItteratr; i++) {
				FileCk2ModFile << fileLinesBuffer[i] + '\n';
			}
		}
	}
	else {
		std::cout << "cannot open settings file for mods in paradox dir";
		exit(1);
	}
}

void Util::firstRunSettings(std::string f_ck2mConfigFile, std::string f_ck2mModFolder, std::string
	f_ck2ModFile) {

}

bool Util::checkIfck2mSettingsFileExistOrCreate(){
	if (!std::filesystem::exists(ck2mSettings)) {
		std::ofstream File(ck2mSettings, std::ios::out);
		if (!std::filesystem::exists(ck2mSettings)) {
			return false;
		}
		return true;
	}
	return true;
}