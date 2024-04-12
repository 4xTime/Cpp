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
			}
		}
		return FileConfigPos(modPos, modName, modStatus);
	}
	std::cout << "cant open a config" << std::endl;
	exit(1);
}