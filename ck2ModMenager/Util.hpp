#pragma once
#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>

enum LABLE {
	modPack = 0,
	mod = 1,
};

class Util {
protected:
	std::string ck2mConfigFile = std::filesystem::current_path().string() + "\\ck2mModFolder\\config.ini";
	std::string ck2mModFolder = std::filesystem::current_path().string() + "\\ck2mModFolder";
	std::string ck2ModFile = "C:\\Users\\Admin\\Documents\\Paradox Interactive\\Crusader Kings II\\settings.txt";

	bool checkIfDirExistOrCreate();
	bool checkIfModDataFolderExistOrCreate();
	void checkIfModsUsedLineExistIfNotCreate(std::string ck2ModFile);
};