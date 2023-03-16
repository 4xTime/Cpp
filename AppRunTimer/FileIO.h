#pragma once
#include "IncludeLib.h"

class FileIO {
public:
	int GetTimeFromTxtFile(std::wstring Procname, std::string PATH);
	bool SaveTimeInTxtFile(long long hms, std::wstring Procname);
	std::vector<std::wstring> GetProcessListFromFile();
	bool CheckIfTxtFileExist(std::string FileName);
	bool CheckIfFileExist(std::string FolderName);
};