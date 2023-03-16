#pragma once
#include "FileIO.h"

class ReadProcessList : public FileIO{
public:
	int ProcessQueue(std::wstring process, std::vector<std::wstring>Founded, int NumOfElementsInVector);
	bool FindRunningProcess(std::wstring process);
	void KeepTrackOfMyProcess(std::vector<std::wstring>Founded, std::vector<std::wstring>ProcessName, int NumOfElementsInVector);
	void GetInfoAboutMyProcFromProcFile();
};
