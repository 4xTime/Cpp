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
	//RSTR - Randomize get random char from "Chartable[53]".
	string RSTR(int String_lenght);

	//DEV_MENU display FB - FirstBuffer,SB - SecBuffer,SCO - Scount(all generated words),
	//NCO - Ncount(new wrods),SSCO - SScount(Skiped Words).
	void DEV_MENU(string& FB, string& SB, uint64_t& SCO, uint64_t& NCO, uint64_t& SSCO);
private:
	// Char table contains all usable chars
	char Chartable[CHAR_TABLE_MAX] = { 'a','b','c','d','f','g','h','j','k','l','z','x','c','v','b','n','m',
	'Q','W','E','R','T','Y','U','I','O','P','A','S','D','F','G','H','J','K','L','Z','X','C','V','B','N','M',
	'1','2','3','4','5','6','7','8','9','0','!','@','#','$','%','^','&','*','(',')',';','"',':','<','>','?'};
	string FirstBuffer;
	string skiped_word;

	uint64_t Scount = 0;
	uint64_t Ncount = 0;
	uint64_t SScount = 0;

	h_time t_End, t_Start;

	bool add_to_file = true;
public:
	RandContFile(const char* PATH, uint32_t HowManyWords, uint32_t String_Lenght, uint32_t DevMenuOn = 1);
	~RandContFile();
};