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
	const int ck2_mod_folder_path_lenght = 20;
	const int ck2_settings_folder_path = 25;

	std::string ck2mSettings = std::filesystem::current_path().string() + "\\ck2mModFolder\\ck2msettings.ini";
	std::string ck2mConfigFile = std::filesystem::current_path().string() + "\\ck2mModFolder\\config.ini";
	std::string ck2mModFolder = std::filesystem::current_path().string() + "\\ck2mModFolder";
	std::string ck2ModFile;
	std::string ck2ModFolder;

	void firstRunSettings(std::string f_ck2mConfigFile,std::string f_ck2mModFolder,std::string
	f_ck2ModFile);
	bool checkIfDirExistOrCreate();
	bool checkIfModDataFolderExistOrCreate();
	void checkIfModsUsedLineExistIfNotCreate(std::string ck2ModFile);
	bool checkIfck2mSettingsFileExistOrCreate();
	//-------- TEST FUNCTIONS MEY NOT WORK AS INTENDED IN SOME CASES ----------------
	bool checkIfck2mSettingsArePoulated();
	void populateck2mSettings(std::string ck2modFile, std::string ck2modFolder);
	void getPathsFromCk2mSettgins();
};