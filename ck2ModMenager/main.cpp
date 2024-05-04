#include <iostream>
#include "FileMenager.hpp"
#include "modMenager.hpp"
#include "Util.hpp"

//IN INIT STATE SEARCH CK2 SETTINGS FOR MOD THAT IS ENABLE AND CHANGE STATE IN MENAGER
//IF MOD IS NOT PRESENT IN CK2 MOD FOLDER DELETE
//BUG WITH DUPLICATE SETTINGS WHILE REMOVING MOD
//MAKE DELETE BUTTON FOR MODPACK
//MAKE MEYBE SOME CONFIG FOLDER FOR MENAGER THAT CAN STORE PATHS
	// AND IN FIRST RUN POP UP THAT TAKE PATHS FROM USER
int main(){
	modMenager MM("C:\\Users\\Admin\\Documents\\Paradox Interactive\\Crusader Kings II\\mod");

	while (true) {
		MM.start();
	}
    return 0;
}