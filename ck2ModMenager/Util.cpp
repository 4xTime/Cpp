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
		std::ofstream File(ck2mSettings);
		if (!std::filesystem::exists(ck2mSettings))
			return false;

		File << "ck2_mod_folder_path=\n";
		File << "ck2_settings_folder_path=\n";
		return true;
	}
	return true;
}

bool Util::checkIfck2mSettingsArePoulated() {
	std::ifstream File(ck2mSettings);
	if (File.is_open()) {
		std::string line;
		while (getline(File, line)) {
			//FOR NOW SOLUTION 
			if (line.length() <= ck2_mod_folder_path_lenght)
				return false;
		}
	}
	else {
		std::cout << "something went wrong {checkIfck2mSettingsArePoulated}";
		exit(1);
	}

	return true;
}

void Util::populateck2mSettings(std::string ck2modFile,std::string ck2modFolder) {
	std::fstream File(ck2mSettings, std::ios::in | std::ios::out);
	if (File.is_open()) {

		std::string line;
		std::vector<std::string> LineBuffer;
		while (getline(File, line)) {
			LineBuffer.push_back(line);
		}
		if (LineBuffer[0].length() > ck2_mod_folder_path_lenght) {
			//20 is lenght of ck2_mod_folder_path
			LineBuffer[0].erase(ck2_mod_folder_path_lenght + LineBuffer[0].length() - ck2_mod_folder_path_lenght);
		}
		if (LineBuffer[1].length() > ck2_settings_folder_path) {
			LineBuffer[1].erase(ck2_settings_folder_path + LineBuffer[1].length() - ck2_settings_folder_path);
		}
		LineBuffer[0] += ck2modFolder;
		LineBuffer[1] += ck2modFile;

		File.clear();
		File.seekp(0, std::ios::beg);
		for (int i = 0; i < LineBuffer.size(); i++) {
			File << LineBuffer[i] + '\n';
		}
	}
	else {
		std::cout << "something went wrong {populateck2mSettings}";
		exit(1);
	}
}

/*
void Util::populateck2mSettings(std::string ck2modFile,std::string ck2modFolder) {
	std::fstream File(ck2ModFile, std::ios::in | std::ios::out);
	if (File.is_open()) {

		std::string line;
		std::vector<std::string> LineBuffer;
		while (getline(File, line)) {
			LineBuffer.push_back(line);
		}
		for (int i = 0; i < LineBuffer.size(); i++) {
			if (LineBuffer[i] == "ck2_mod_folder_path=") {

			}
			if (LineBuffer[i] == "ck2_settings_folder_path=") {

			}
		}
	}
	else {
		std::cout << "something went wrong {populateck2mSettings}";
		exit(1);
	}
}
*/
