#pragma once
#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>
#include <map>

enum LABLE {
	modPack = 0,
	mod = 1,
};

class Util {
protected:
	const int ck2_mod_folder_path_lenght = 20;
	const int ck2_settings_folder_path = 25;

	const int ck2mModFolderNameSize = ck2mModFolder.size();
	const int ck2mModFileNameSize = ck2ModFile.size();

	const std::string modFolderPathPrefix="ck2_mod_folder_path=";
	const std::string settingsPathPrefix = "ck2_settings_folder_path=";

	std::string ck2mSettings = std::filesystem::current_path().string() + "\\ck2mModFolder\\ck2msettings.ini";
	std::string ck2mConfigFile = std::filesystem::current_path().string() + "\\ck2mModFolder\\config.ini";
	std::string ck2mModFolder = std::filesystem::current_path().string() + "\\ck2mModFolder";
	std::string ck2ModFile;
	std::string ck2ModFolder;

	bool checkIfDirExistOrCreate();
	bool checkIfModDataFolderExistOrCreate();
	void checkIfModsUsedLineExistIfNotCreate();
	bool checkIfck2mSettingsFileExistOrCreate();


	void clearFileData(std::string path);
	bool handleWrongPath();
	
	//-------- TEST FUNCTIONS MEY NOT WORK AS INTENDED IN SOME CASES ----------------
	bool checkIfck2mSettingsArePoulated();
	void getPathsFromCk2mSettgins();
	std::vector<std::string> lookForDeletedMods(std::vector<std::filesystem::path> mods);
};