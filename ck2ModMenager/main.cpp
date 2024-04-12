#include <iostream>
#include "FileMenager.hpp"
#include "modMenager.hpp"
#include "Util.hpp"

int main(){
	modMenager MM("C:\\Users\\Admin\\Documents\\Paradox Interactive\\Crusader Kings II\\mod");

	while (true) {
		MM.start();
	}
    return 0;
}