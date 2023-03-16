#include "FileIO.h"

bool FileIO::CheckIfFileExist(std::string FolderName) {
    if (std::filesystem::exists(FolderName)) {
        return 1;
    }
    else { std::filesystem::create_directories(FolderName); return 0; }
}

bool FileIO::CheckIfTxtFileExist(std::string FileName) {
    std::ofstream File(FileName,std::ios::app);
    if (File.is_open()) {
        std::ifstream file(FileName,std::ios::app);
        std::string ARG;
        file >> ARG;
        if (ARG.empty()) { std::cout << FileName << " is empty" << std::endl; }

        file.close();
        File.close();
        return 1;
    }
    else {
        std::ifstream file(FileName);
        std::cout << FileName << " is empty" << std::endl;

        File.close();
        file.close();
        return 0;
    }
}

int FileIO::GetTimeFromTxtFile(std::wstring Procname, std::string PATH) {
    std::string Sprocname = PATH;
    Sprocname += std::string(Procname.begin(), Procname.end()) += ".txt";
    std::ifstream File(Sprocname);
    std::string FileContent;
    if (File.is_open()) {
        File >> FileContent;
        File.close();
        return std::stoi(FileContent);
    }

    return 0;
}

bool FileIO::SaveTimeInTxtFile(long long hms, std::wstring Procname) {
    std::chrono::hh_mm_ss time{std::chrono::seconds(hms)};

    std::string Sprocname = "MyTime\\";
    Sprocname += std::string(Procname.begin(), Procname.end()) += ".txt";
    std::ofstream File(Sprocname);
    if (File.is_open()) {
        File << hms << std::endl;
        File << "----------------------" << std::endl;
        File << "Total Time-> " << time.hours() << ":" << time.minutes() << ":" << time.seconds() << std::endl;
        File.close();
    }
    else {
        std::cout << "Error cannot measure time" << std::endl;
        std::cout << "Cannot open a file->"<<Sprocname<< std::endl;
        exit(1);
    }

    return 0;
}

std::vector<std::wstring> FileIO::GetProcessListFromFile() {
    std::ifstream File("ProcessList.txt");
    std::string fileSTR;
    std::vector<std::wstring>ProcStorage;
    if (File.is_open()) {
        while (std::getline(File, fileSTR)) {
            std::wstring wfileSTR = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(fileSTR);
            ProcStorage.push_back(wfileSTR);
        }
    }
    else {std::cout << "Cannot open a file->ProcessList.txt"<<std::endl;}
    File.close();
    return ProcStorage;
}
