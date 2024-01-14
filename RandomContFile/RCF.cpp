#include "RCF.h"

RandContFile::RandContFile(const char* PATH, uint32_t String_Lenght, uint32_t DevMenuOn) {
	t_Start = std::chrono::steady_clock::now();
	
	double number_of_used_combination = number_of_used_combinations(PATH);
	double number_of_posible_combination = pow(CHAR_TABLE_MAX,String_Lenght);

	double number_of_remaining_possible_combinations = (number_of_posible_combination - number_of_used_combination);

	std::fstream File(PATH);
	std::string line;

	if (File.good()) {
		srand(time(NULL));
		for (int i = 0; i < number_of_remaining_possible_combinations; i++) {
			add_to_file = true;

			File.close();
			File.open(PATH, std::ios::in);

			FirstBuffer = RSTR(String_Lenght);


			while (std::getline(File, line)) {
				if (FirstBuffer == line) {
					add_to_file = false;
					number_of_words_skiped++;
					break;
				}
			}

			if (add_to_file == true) {
				number_of_new_words++;
				number_of_used_combination++;
				number_of_remaining_possible_combinations--;
				File.close();
				File.open(PATH, std::ios::out | std::ios::app);
				File << FirstBuffer << std::endl;
			}

			if (DevMenuOn == 1 && add_to_file == true) {
				DEV_MENU(FirstBuffer, number_of_remaining_possible_combinations, number_of_used_combination, number_of_new_words, number_of_words_skiped);
			}
			FirstBuffer.clear();
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

void RandContFile::DEV_MENU(string& combination_send_to_file, double& number_of_remaining_possible_combinations, double& summary_combinations, uint64_t& number_of_new_words, uint64_t& number_of_words_skiped) {
	std::cout << "-------------------DEV-MENU-------------------------" << std::endl;
	std::cout << "SEND TO FILE - " << combination_send_to_file << std::endl;
	std::cout << "SUMMARY COMBINATIONS - " << summary_combinations << std::endl;
	std::cout << "NEW WORDS - " << number_of_new_words << std::endl;
	std::cout << "SKIPED WORDS - " << number_of_words_skiped << std::endl;
	std::cout << "NUMBER OF REMAINING COMBINATIONS - " << number_of_remaining_possible_combinations << std::endl;
	std::cout << "-------------------DEV-MENU-------------------------" << std::endl;
}

double RandContFile::number_of_used_combinations(const char* PATH) {
	double sum = 0;
	std::fstream f_File(PATH, std::ios::in);
	
	std::string f_line;

	if (f_File.is_open()) {
		while (std::getline(f_File, f_line)) {
			sum++;
		}
		f_File.close();
		return sum;
	}
	else {
		std::cout << "file is can't be open";
	}
	f_File.close();
	return 0;
}