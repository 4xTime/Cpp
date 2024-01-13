#include "RCF.h"

RandContFile::RandContFile(const char* PATH, uint32_t HowManyWords, uint32_t String_Lenght, uint32_t DevMenuOn) {
	t_Start = std::chrono::steady_clock::now();
	std::fstream File(PATH);
	std::string line;

	if (File.good()) {
		srand(time(NULL));
		for (int i = 0; i < HowManyWords; i++) {
			add_to_file = true;

			File.close();
			File.open(PATH, std::ios::in);

			FirstBuffer = RSTR(String_Lenght);
			

			while (std::getline(File, line)) {
				if (FirstBuffer == line) {
					skiped_word = FirstBuffer;
					add_to_file = false;
					SScount++;
					Scount++;
					HowManyWords++;
					break;
				}
			}

			if (add_to_file == true) {
				Ncount++;
				Scount++;
				HowManyWords++;

				File.close();
				File.open(PATH, std::ios::out | std::ios::app);
				File << FirstBuffer << std::endl;
			}

			if (DevMenuOn == 1 && add_to_file == true) {
				DEV_MENU(FirstBuffer, skiped_word, Scount, Ncount, SScount);
			}
			FirstBuffer.clear();
			skiped_word.clear();
		}

	}
	else {
		std::cout << "file is can't be open";
	}
}

RandContFile::~RandContFile() {
	t_End = std::chrono::steady_clock::now();
	std::cout << "Time count - " << std::chrono::duration_cast<std::chrono::seconds>(t_End - t_Start).count() << "." << std::chrono::duration_cast<std::chrono::milliseconds>(t_End - t_Start).count() << std::endl;
}

string RandContFile::RSTR(int String_lenght) {
	string ARG;
	for (int i = 0; i < String_lenght; i++) {
		ARG += RandContFile::Chartable[rand() % CHAR_TABLE_MAX];
	}
	return ARG;
}


void RandContFile::DEV_MENU(string& FB, string& SB, uint64_t& SCO, uint64_t& NCO, uint64_t& SSCO) {
	std::cout << "-------------------DEV-MENU-------------------------" << std::endl;
	std::cout << "SEND TO FILE - " << FB << std::endl;
	std::cout << "SKIPED - " << SB << std::endl;
	std::cout << "SUMMARY WORDS - " << SCO << std::endl;
	std::cout << "NEW WORDS - " << NCO << std::endl;
	std::cout << "SKIPED WORDS - " << SSCO << std::endl;
	std::cout << "-------------------DEV-MENU-------------------------" << std::endl;
}
