#pragma once
#include <vector>
#include <string>
#include "Util.hpp"
#include <map>
#include <iostream>

struct Files {
	std::vector<std::filesystem::path> mods;
	int numberOfMods;
	Files(std::vector<std::filesystem::path> mods= std::vector<std::filesystem::path>(0), int numberOfMods = 0) :mods(mods), numberOfMods(numberOfMods) {}
};
//NOT USED RIGHT NOW
struct FileConfigPos {
	std::vector<int> modPos;
	std::vector<char> status;
	std::vector<std::string> name;
	FileConfigPos(std::vector<int> modPos, std::vector<std::string> name, std::vector<char> status) : modPos(modPos), name(name),status(status) {}
};


//CPP 17
class fileMenager : public Util {
protected:
	Files file;
	int OldNumOfMods;
	bool* modState;
	bool* modStateForModpack;
	bool* modPackState;

	Files serachForMod(std::string modFolder);
	int checkIfModIsInFile(std::string configFile, std::string searchMod, LABLE lable);
	void appedNewModInFile(std::string configFile, std::string searchMod, LABLE lable, int line);
	char readStateOfMod(std::string configFile, int line);
	void chagneStateOfMod(std::string configFile, int lineNum, bool state);
	int getModPosInFile(std::string configFile,std::string searchMod);
	void saveModPackInFile(std::string configFile, std::string modPackName, std::vector<int>linePosOfMods);
	FileConfigPos getModPackPosNameStatus(std::string configFile);
};