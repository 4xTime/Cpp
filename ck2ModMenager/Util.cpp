#include "Util.hpp"

bool Util::checkIfDirExistOrCreate() {
	if (std::filesystem::is_directory(std::filesystem::path(ck2mModFolder))) {
		return true;
	}
	else {
		if (std::filesystem::create_directory(ck2mModFolder))
			return true;
		return false;
	}
	return false;
}

bool Util:: checkIfModDataFolderExistOrCreate() {
	if (!std::filesystem::exists(ck2mConfigFile)) {
		std::ofstream File(ck2mConfigFile, std::ios::out);

		if (!std::filesystem::exists(ck2mConfigFile)) {
			return false;
		}

		File << "[Mods Packs]\n";
		File << "\n[Mods]\n";
		return true;
	}
	return true;
}