#include "path.h"

void extra::path::check_create_folder(const std::string& folder) {
	// ����ļ����Ƿ����
	if (!std::filesystem::exists(folder)) {
		std::filesystem::create_directories(folder);
	}
}