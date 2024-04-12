#pragma once
#include <filesystem>
#include <fstream>
#include <string>

enum LABLE {
	modPack = 0,
	mod = 1,
};

class Util {
protected:
	std::string ck2mConfigFile = std::filesystem::current_path().string() + "\\ck2mModFolder\\config.ini";
	std::string ck2mModFolder = std::filesystem::current_path().string() + "\\ck2mModFolder";

	bool checkIfDirExistOrCreate();
	bool checkIfModDataFolderExistOrCreate();
};