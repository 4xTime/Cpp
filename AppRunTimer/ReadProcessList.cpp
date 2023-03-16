#include "ReadProcessList.h"

int ReadProcessList::ProcessQueue(std::wstring process, std::vector<std::wstring>Founded, int NumOfElementsInVector) {
    for (auto& i : Founded) {
        if (i == process) {
            return 1;
        }
        else {
            if (FindRunningProcess(process) == true) {
                Founded.push_back(process);

                long long hms = 0;
                int TimeFromFile = GetTimeFromTxtFile(process, "MyTime\\");

                if (TimeFromFile != 0) {
                    hms = TimeFromFile;
                }
                hms = hms + 1;
                SaveTimeInTxtFile(hms, process);
            }
            return 0;
        }
    }
    return 0;
}

void ReadProcessList::KeepTrackOfMyProcess(std::vector<std::wstring>Founded, std::vector<std::wstring>ProcessName, int NumOfElementsInVector) {
    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        for (auto& i : ProcessName) {
            ProcessQueue(i, Founded, NumOfElementsInVector);
        }
    }
}

void ReadProcessList::GetInfoAboutMyProcFromProcFile() {
    std::vector<std::wstring>ProcessName = GetProcessListFromFile();
    std::vector<std::wstring> Founded;
    Founded.push_back(L"0");

    int NumberOfElementsInVector = 0;
    for (auto& i : ProcessName) { NumberOfElementsInVector++; }

    //KeepTrackOfMyProcess(Founded, ProcessName, NumberOfElementsInVector);

    std::thread Thread(&ReadProcessList::KeepTrackOfMyProcess,this,Founded, ProcessName, NumberOfElementsInVector);
    Thread.join();
}


bool ReadProcessList::FindRunningProcess(std::wstring process) {
    WCHAR* compare;
    bool procRunning = false;

    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        procRunning = false;
    }
    else {
        pe32.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(hProcessSnap, &pe32)) {
            if (pe32.szExeFile == process) {
                procRunning = true;
                return true;
            }
            else {
                while (Process32Next(hProcessSnap, &pe32)) {
                    compare = pe32.szExeFile;
                    if (compare == process) {
                        procRunning = true;
                        return true;
                        break;
                    }
                }
            }
            CloseHandle(hProcessSnap);
        }
    }

    return false;
}