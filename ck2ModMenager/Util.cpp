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

void Util::checkIfModsUsedLineExistIfNotCreate() {
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


bool Util::checkIfck2mSettingsFileExistOrCreate(){
	if (!std::filesystem::exists(ck2mSettings)) {
		std::ofstream File(ck2mSettings);
		if (!std::filesystem::exists(ck2mSettings))
			return false;

		File << modFolderPathPrefix+'\n';
		File << settingsPathPrefix+'\n';
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


void Util::getPathsFromCk2mSettgins() {
	std::ifstream File(ck2mSettings);
	if (File.is_open()) {
		std::string line;
		std::vector<std::string>lineBuffer;
		while (getline(File, line)) {
			lineBuffer.push_back(line);
		}
		lineBuffer[0].erase(lineBuffer[0].begin(),lineBuffer[0].begin()+ck2_mod_folder_path_lenght);
		lineBuffer[1].erase(lineBuffer[1].begin(), lineBuffer[1].begin() + ck2_settings_folder_path);

		ck2ModFolder = lineBuffer[0];
		ck2ModFile = lineBuffer[1];
	}
	else {
		std::cout << "something went wrong {getPathsFromCk2mSettgins}";
		exit(1);
	}
}

void Util::clearFileData(std::string path) {
	std::ofstream File(path, std::ios::out | std::ios::trunc);
	File.close();
}

bool Util::handleWrongPath() {
	//ModFolder must end with "mod"
	//ModFile must end with "settings.txt"
	std::size_t found = ck2ModFolder.find("mod");

	if (found != std::string::npos && std::filesystem::exists(ck2ModFolder)) {
		found = ck2ModFile.find("settings.txt");
		if (found != std::string::npos&& std::filesystem::exists(ck2ModFile)) {
			return true;
		}
	}

	
	return false;
}

std::vector<std::string> Util::lookForDeletedMods(std::vector<std::filesystem::path> mods){
	std::ifstream File(ck2mConfigFile);
	std::vector<std::string>deletedMods;

	if (File.is_open()) {
		std::vector<std::pair<int,std::string>>modsInModMenager;
		bool startRead = false;
			
		const int founded = 1;
		const int notFounded = 0;

		std::string line;

		while (getline(File, line)) {
			if (startRead == true) {
				modsInModMenager.push_back(std::make_pair(notFounded,line.erase(line.size()-2)));
			}
			if (line == "[Mods]")
				startRead = true;
		}
		for (size_t i = 0; i < modsInModMenager.size();i++) {
			for (size_t j = 0; j< mods.size(); j++) {
				size_t Found = modsInModMenager[i].second.find(mods[j].string());
				if (Found != std::string::npos) {
					modsInModMenager[i].first = founded;
					break;
				}
			}
		}
		std::sort(modsInModMenager.begin(), modsInModMenager.end());
		for (size_t i = 0; i < modsInModMenager.size(); i++) {
			if (modsInModMenager[i].first == 1)
				break;
			deletedMods.push_back(modsInModMenager[i].second);
		}
	}
	else {
		std::cout << "something wrong {lookForDeletedMods}";
		exit(1);
	}

	return deletedMods;
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
