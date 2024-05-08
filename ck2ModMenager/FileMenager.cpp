#include "FileMenager.hpp"

Files fileMenager::serachForMod(std::string modFolder) {
	std::vector<std::filesystem::path>mods;

	for (const auto& entry : std::filesystem::recursive_directory_iterator(modFolder)) {
		if (entry.path().extension() == ".mod") {
			std::string modName;
			int modNameLenght = 0;
			int modNameItter = 0;
			for (int i = entry.path().string().length(); i != 0; i--) {
				if (entry.path().string()[i] == '\\'){
					modName = entry.path().string().substr(i+1, entry.path().string().length());
					mods.push_back(modName);
					break;
				}
			}
		}
	}
	return Files(mods, mods.size());
}

int fileMenager::checkIfModIsInFile(std::string configFile, std::string searchMod, LABLE lable) {
	std::ifstream File(configFile);
	std::string line;

	bool allowToPass = true;
	int linePos = 0;

	//[MOCDS PACK AND MOD :(
	if (File.is_open()) {
		while (getline(File, line)) {
			if ((line.length() >= 2 && line != "[Mods Packs]") || (line.length() >= 2 && line != "[Mods]")) {
				line.erase(line.length() - 2, 2);
			}

			linePos++;
			if (lable == LABLE::mod) {
				if (line == "[Mods Pack") {
					allowToPass = false;
				}
				if (allowToPass == false) {
					if (line == searchMod) {
						return -1;
					}
				}
			}
			else if (lable == LABLE::modPack) {
				if (line == "[Mod") {
					return linePos -1;
				}
				if (line == searchMod) {
					return -1;

				}
			}
		}
		return linePos+1;

	}
	std::cout << "cannot open : " << configFile.c_str() << std::endl;
	exit(1);
}

void fileMenager::appedNewModInFile(std::string configFile, std::string searchMod, LABLE lable, int line) {
	std::ofstream File(configFile,std::ios::app|std::ios::out);

	File.seekp(line);
	File << searchMod + "=0" + "\n";
}

char fileMenager::readStateOfMod(std::string configFile, int lineNum) {
	std::ifstream File(configFile);
	std::string line;
	int linePos=0;

	while(getline(File, line)) {
		linePos++;
		if (linePos == lineNum) {
			return line.back();
		}
	}
	return '0';
}
//BUGS!
void fileMenager::chagneStateOfMod(std::string configFile, int lineNum, bool state) {
	std::fstream File(configFile, std::ios::in | std::ios::out);
	std::vector<std::string> lines;
	std::string line;

	int linePos = 0;
	std::vector<int>linePosVector;

	char stateChar;
	if (File.is_open()) {
		if (state)
			stateChar = '1';
		else
			stateChar = '0';

		while (getline(File, line)) {
			linePos++;
			linePosVector.push_back(linePos);
			lines.push_back(line);
		}
		for (int i = 0; i < linePos; i++) {
			if (!lines[lineNum].empty() && linePosVector[i] == lineNum) {
				lines[lineNum].back() = stateChar;
			}
		}

		File.clear();
		File.seekp(0, std::ios::beg);
		for (const auto& line : lines) {
			File << line << '\n';
		}
	}
	else {
		std::cout << "cannot open config file" << std::endl;
		exit(1);
	}
}

int fileMenager::getModPosInFile(std::string configFile, std::string searchMod) {
	std::ifstream File(configFile);
	std::string line;
	
	int linePos=0;
	if (File.is_open()) {
		while (getline(File, line)) {
			linePos++;
			if ((line.length() >= 2 && line != "[Mods Packs]") || (line.length() >= 2 && line != "[Mods]")) {
				line.erase(line.length() - 2, 2);

				if (line == searchMod) {
					return linePos;
				}
			}
		}
		return -1;
	}
	std::cout << "cannot open : "<<configFile.c_str() << std::endl;
	exit(1);
}

void fileMenager::saveModPackInFile(std::string configFile, std::string modPackName, std::vector<int>linePosOfMods) {
	std::fstream File(configFile, std::ios::in | std::ios::out);

	std::map<int,std::string> lines;
	std::string line;
	std::string linePosOfModsString;

	bool allowToWrite = false;

	int itterator=0;
	if (File.is_open()) {
		for (auto i : linePosOfMods) {
			linePosOfModsString += std::to_string(i) + ".";
		}
		while (getline(File, line)) {
			itterator++;
			lines[itterator] = line;
		}
		for (int i = 0; i < itterator;i++) {
			if (lines[i] == "[Mods Packs]")
				allowToWrite = true;
			if (allowToWrite&&lines[i].empty()&&lines[i] != "[Mods Packs]") {
				lines[i] = modPackName +"." + linePosOfModsString+"=0" + "\n";
				break;
			}
		}

		File.clear();
		File.seekp(0, std::ios::beg);
		for (int i = 0; i < itterator;i++) {
			File << lines[i] << '\n';
		}
	}
	else { std::cout << "error with config"<<std::endl; }
}
FileConfigPos fileMenager::getModPackPosNameStatus(std::string configFile) {
	std::ifstream File(configFile);
	std::vector<int> modPos;
	std::vector<char> modStatus;
	std::vector<std::string>modName;


	std::string line;
	std::string modNameBuffer;

	int linePos = 0;
	if (File.is_open()) {
		while (getline(File, line)) {
			linePos++;
			if (line == "[Mods]") { break; }
			if (line != "[Mods Packs]"&&!line.empty()&&line!="[Mods]") {
				modStatus.push_back(line.back());
				modPos.push_back(linePos-1);
				for (int i = 0; i < line.length(); i++) {
					if (line[i] == '.') {
						break;
					}
					modNameBuffer += line[i];
				}
				modName.push_back(modNameBuffer);
				modNameBuffer.clear();
			}
		}
		return FileConfigPos(modPos, modName, modStatus);
	}
	std::cout << "cant open a config" << std::endl;
	exit(1);
}


void fileMenager::enableDisableModCK2(std::string configFile, std::string ck2ModFile, int lineNum, LABLE lable,bool state) {
	std::fstream FileModMenagerConfig(configFile, std::ios::in | std::ios::out);
	std::fstream FileCk2ModFile(ck2ModFile, std::ios::in | std::ios::out);

	std::map<int, std::string> lines;
	std::map<int, std::string> linesCK2SETTGINS;

	std::vector<int>modPackModsToActiveLineNum;
	std::vector<int>modPosList;

	std::string lineCk2ModFile;
	std::string lineModMenagerFile;
	std::string modPackModToActive;
	std::string modPackName;

	bool startRead = false;

	int itterator = 0;
	int linePos = 0;
	if (FileModMenagerConfig.is_open()) {
		while (getline(FileModMenagerConfig, lineModMenagerFile)) {
			if (linePos == lineNum) {
				if (lable == LABLE::mod) {
					lineModMenagerFile.erase(lineModMenagerFile.length() - 2, 2);
					lines[itterator] = "\"mod/" + lineModMenagerFile + '\"';
					//itterator jest bezsensu mozemy zast¹piæ zwyk³ym stringem i tak funkcje wykona sie raz
					//dla jednego moda CHANGE IT!
					itterator++;
				}
				else if (lable == LABLE::modPack) {
					lines[itterator] = lineModMenagerFile;
					modPackName = lineModMenagerFile;
					for (int i = 0; i < lines[itterator].length(); i++) {
						if (lines[itterator][i] == '.') {
							startRead = true;
						}
						if (startRead) {
							modPackModToActive += lines[itterator][i];
						}
					}
					modPackModToActive.erase(modPackModToActive.length() - 2, 2);
					modPosList = getVectroOfModPos(modPackModToActive);
					for (const auto a : modPosList) {
						enableDisableModCK2(configFile, ck2ModFile, a, LABLE::mod, state);
					}
				}
			}
			linePos++;
		}
	}
	else {
		std::cout << "Config file cannot open" << std::endl;
		exit(1);
	}

	int itteratorCK2SETTGINS = 0;
	
	//WHILE DELETING SOME LINE FROM SETTGINS DUPLICATE!
	if (FileCk2ModFile.is_open()) {
		if (state) {
			//FIX FOR ADDING MOD PACK NAME IN CK2 SETTINGS
			if (lines[0] != modPackName) {
				std::string modPayload = lines[0];
				bool canWrite = false;
				while (getline(FileCk2ModFile, lineCk2ModFile)) {
					linesCK2SETTGINS[itteratorCK2SETTGINS] = lineCk2ModFile;
					itteratorCK2SETTGINS++;
				}
				for (int i = 0; i < itteratorCK2SETTGINS; i++) {
					if (linesCK2SETTGINS[i] == "last_mods=" && linesCK2SETTGINS[i + 2] != "}") {
						linesCK2SETTGINS[i + 2] += " " + modPayload;
					}
					else if (linesCK2SETTGINS[i] == "last_mods=" && linesCK2SETTGINS[i + 2] == "}") {
						linesCK2SETTGINS[i + 1] += "\n" + modPayload;
					}
				}
				FileCk2ModFile.clear();
				FileCk2ModFile.seekp(0, std::ios::beg);
				for (int i = 0; i < itteratorCK2SETTGINS; i++) {
					FileCk2ModFile << linesCK2SETTGINS[i] + "\n";
				}
			}
		}
		else if (!state) {
			if (lines[0] != modPackName) {
				std::string modPayload = lines[0]; 
				std::vector<std::string>writeBuffer;
				bool canWrite = false;
				while (getline(FileCk2ModFile, lineCk2ModFile)) {
					linesCK2SETTGINS[itteratorCK2SETTGINS] = lineCk2ModFile;
					itteratorCK2SETTGINS++;
				}

				for (int i = 0; i < itteratorCK2SETTGINS; i++) {
					std::size_t found = linesCK2SETTGINS[i].find(modPayload);
					if (found != std::string::npos) {
						linesCK2SETTGINS[i].erase(found, linesCK2SETTGINS[i].length());
					}
				}

				FileCk2ModFile.clear();
				FileCk2ModFile.seekp(0, std::ios::beg);
				for (int i = 0; i < itteratorCK2SETTGINS; i++) {
					FileCk2ModFile << linesCK2SETTGINS[i] + "\n";
				}
			}
		}
	}
	
}

std::vector<int> fileMenager::getVectroOfModPos(std::string posString) {
	std::vector<int> pos;
	std::string StringIntBuffer;
	for (int i = 0; i < posString.length(); i++) {
		if (posString[i] != '.' ) {
			StringIntBuffer += posString[i];
		}
		if (posString[i] == '.' && i != posString.length()) {
			pos.push_back(std::atoi(StringIntBuffer.c_str()));
			StringIntBuffer.clear();
		}
	}
	pos.erase(pos.begin());
	return pos;
}

void fileMenager::startUpActions(){
	if (!checkIfDirExistOrCreate()) {
		std::cout << "Cannot create ck2m mod folder" << std::endl;
	}
	if (!checkIfModDataFolderExistOrCreate()) {
		std::cout << "Cannot create config.ini" << std::endl;
		exit(1);
	}

	checkIfModsUsedLineExistIfNotCreate(ck2ModFile);
	for (int i = 0; i < file.numberOfMods; i++) {
		modStateForModpack[i] = false;
		int pos = checkIfModIsInFile(ck2mConfigFile, file.mods[i].string(), LABLE::mod);

		if (pos != -1) {
			appedNewModInFile(ck2mConfigFile, file.mods[i].string(), LABLE::mod, pos);
		}
		//GET FILE LINE AND CHECK MOD STATE
		if (pos == -1) {
			int modPos = getModPosInFile(ck2mConfigFile, file.mods[i].string());
			if (modPos != -1) {
				posVec.push_back(modPos);
				char modStateChar = readStateOfMod(ck2mConfigFile, modPos);
				if (modStateChar == '0') {
					modState[i] = false;
				}
				if (modStateChar == '1') {
					modState[i] = true;
				}
			}
			else if (modPos == -1) { std::cout << "modPos unknown"; exit(1); }
		}
	}
	FileConfigPos modInfo = getModPackPosNameStatus(ck2mConfigFile);
	for (int i = 0; i < modInfo.modPos.size(); i++) {
		if (modInfo.status[i] == '1') {
			modPackState[i] = true;
		}
		else if (modInfo.status[i] == '0') {
			modPackState[i] = false;
		}
	}
}

bool fileMenager::allocateMem() {
	file = serachForMod(ck2ModFolder);
	modState = (bool*)malloc(file.numberOfMods * sizeof(bool));
	modStateForModpack = (bool*)malloc(file.numberOfMods * sizeof(bool));
	modPackState = (bool*)malloc(100 * sizeof(bool));

	if (modState == NULL) {
		std::cout << "MODS IS NULL" << std::endl;
		return false;
	}
	if (modPackState == NULL) {
		std::cout << "MODPACK IS NULL" << std::endl;
		return false;
	}
	if (modPackState == NULL) {
		std::cout << "MOD STATE FOR MODPACK IS NULL" << std::endl;
		return false;
	}
	return true;
}

void fileMenager::changeSettings(bool firstRun) {
	ImGui::Begin("Settings");
	ImGui::Text("Type ck2 mod folder path");
	ImGui::InputText("##folder", &ck2ModFolder, 256);
	ImGui::Text("Type ck2 settings path u can find it in {Documents\Paradox Interactive\Crusader Kings II}");
	ImGui::InputText("##file", &ck2ModFile, 256);
	if (ImGui::Button("append")) {
		bool rightPath = handleWrongPath(ck2ModFolder, ck2ModFile);
		if (ck2ModFolder.length() > 1 && ck2ModFile.length() > 1 && rightPath) {
			populateck2mSettings(ck2ModFile, ck2ModFolder);
			//IF RUN FIRST TIME...
			if (checkIfck2mSettingsArePoulated() && firstRun) {
				checkDeletedModsAndRemoveFromCk2ModMenager();
				if (allocateMem()) {
					startUpActions();
				}
				else {
					std::cout << "mem alloc went wrong {allocateMem}";
					exit(1);
				}
			}
		}
		else {
			ImGui::Text("Wrong path");
		}
	}
}

void fileMenager::populateck2mSettings(std::string ck2modFile, std::string ck2modFolder) {
	std::fstream File(ck2mSettings, std::ios::in | std::ios::out);
	if (File.is_open()) {

		std::string line;
		std::vector<std::string> lineBuffer;
		while (getline(File, line)) {
			lineBuffer.push_back(line);
		}
		if (lineBuffer[0].length() > ck2_mod_folder_path_lenght || lineBuffer[1].length() > ck2_settings_folder_path) {
			//20 is lenght of ck2_mod_folder_path
			lineBuffer[0] = modFolderPathPrefix + ck2modFolder;
			lineBuffer[1] = settingsPathPrefix + ck2modFile;
			clearFileData(ck2mSettings);
		}
		else {
			lineBuffer[0] += ck2modFolder;
			lineBuffer[1] += ck2modFile;
		}
		File.clear();
		File.seekp(0, std::ios::beg);
		for (int i = 0; i < lineBuffer.size(); i++) {
			File << lineBuffer[i] + '\n';
		}
	}
	else {
		std::cout << "something went wrong {populateck2mSettings}";
		exit(1);
	}
}

void fileMenager::deleteModFromCk2Menager(const int lineNum) {
	//delete from modpacks too
}

void fileMenager::checkDeletedModsAndRemoveFromCk2ModMenager() {
	Files mods = serachForMod(ck2ModFolder);
	std::vector<std::string> DeletedMods = lookForDeletedMods(mods.mods);
	
	for (const auto i : DeletedMods) {
		deleteModFromCk2Menager(getModPosInFile(ck2mConfigFile, i));
	}
	//exit(1);
	//make function that delete mods from mod menager
}

void fileMenager::deleteModFromModpack(const int lineNum,std::string modPackName) {
	std::ifstream File(ck2mConfigFile);
	if (File.is_open()) {

	}
	else {
		std::cout << "something went wrong {deleteModFromModpack}";
		exit(1);
	}
}