#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include<string>
#define CHAR_TABLE_MAX 69
typedef std::string string;
typedef std::chrono::steady_clock::time_point h_time;

class RandContFile {
protected:
	void DEV_MENU(string& combination_send_to_file, double& number_of_remaining_possible_combinations, double& summary_combinations, uint64_t& number_of_new_words, uint64_t& number_of_words_skiped);
private:
	// Char table contains all usable chars
	char Chartable[CHAR_TABLE_MAX] = { 'a','b','c','d','f','g','h','j','k','l','z','x','c','v','b','n','m',
	'Q','W','E','R','T','Y','U','I','O','P','A','S','D','F','G','H','J','K','L','Z','X','C','V','B','N','M',
	'1','2','3','4','5','6','7','8','9','0','!','@','#','$','%','^','&','*','(',')',';','"',':','<','>','?' };
	string FirstBuffer;

	uint64_t number_of_new_words = 0;
	uint64_t number_of_words_skiped = 0;

	h_time t_End, t_Start;

	bool add_to_file = true;

	double number_of_used_combinations(const char* PATH);

	//RSTR - Randomize get random char from "Chartable[69]".
	string RSTR(int String_lenght);

public:
	RandContFile(const char* PATH,uint32_t String_Lenght, uint32_t DevMenuOn = 1);
	~RandContFile();
};