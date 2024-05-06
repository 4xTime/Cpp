#include <iostream>
#include "FileMenager.hpp"
#include "modMenager.hpp"
#include "Util.hpp"

//search for mods that is enable in menager file and chagne it in ck2 settings file
//IF MOD IS NOT PRESENT IN CK2 MOD FOLDER DELETE
//BUG WITH DUPLICATE SETTINGS WHILE REMOVING MOD
//MAKE DELETE BUTTON FOR MODPACK
//text need to appear for more then 1 sec
int main(){
	modMenager MM;

	while (true) {
		MM.start();
	}
    return 0;
}