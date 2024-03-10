#include "path.h"

void extra::path::check_create_folder(const std::string& folder) {
	// 检查文件夹是否存在
	if (!std::filesystem::exists(folder)) {
		std::filesystem::create_directories(folder);
	}
}