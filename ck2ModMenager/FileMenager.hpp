#pragma once
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "misc/cpp/imgui_stdlib.h"
#include <d3d9.h>
#include <vector>
#include <string>
#include "Util.hpp"
#include <map>

struct Files {
	std::vector<std::filesystem::path> mods;
	int numberOfMods;
	Files(std::vector<std::filesystem::path> mods= std::vector<std::filesystem::path>(0), int numberOfMods = 0) :mods(mods), numberOfMods(numberOfMods) {}
};

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
	std::vector<int> posVec;

	Files serachForMod();
	int checkIfModIsInFile(std::string searchMod, LABLE lable);
	int getModPosInFile(std::string searchMod);
	FileConfigPos getModPackPosNameStatus();
	char readStateOfMod(int line);
	void appedNewModInFile(std::string searchMod, LABLE lable, int line);
	void chagneStateOfMod(int lineNum, bool state);
	void enableDisableModCK2(int lineNum, LABLE lable, bool state);
	void saveModPackInFile(std::string modPackName, std::vector<int>linePosOfMods);
	void populateck2mSettings();
	
	void checkDeletedModsAndRemoveFromCk2ModMenager();
	void deleteModFromCk2Menager(const int lineNum);

	void deleteModFromModpack(const int lineNum, std::string modPackName = "");

	bool allocateMem();
	void startUpActions();

	void changeSettings(bool firstRun);
private:
	std::vector<int> getVectroOfModPos(std::string posString);
};