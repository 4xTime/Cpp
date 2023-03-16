#include "ReadProcessList.h"
int main() {
	ReadProcessList RPL;
	RPL.CheckIfTxtFileExist("ProcessList.txt");
	RPL.CheckIfFileExist("MyTime");
	RPL.GetInfoAboutMyProcFromProcFile();
}