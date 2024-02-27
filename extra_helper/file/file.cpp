#include "file.h"

long extra::file::get_file_size(const std::string& file_path) {
	FILE * file = fopen(file_path.c_str(), "rb");
	if (file == NULL) {
		return -1;
	}

	fseek(file, 0, SEEK_END); // 移动文件指针到文件末尾
	long fileSize = ftell(file); // 获取文件指针的位置，即文件大小

	fclose(file);
	return fileSize;
}

void extra::file::split_file_name_folder(const std::string& filepath, std::string* folder, std::string* filename) {
	auto pos = filepath.find_last_of("\\/");
	if (pos != std::string::npos) {
		if (filename) {
			*filename = filepath.substr(pos + 1);
		}

		if (folder) {
			*folder = filepath.substr(0, pos);
		}
	}
	else {
		if (filename) {
			*filename = "";
		}

		if (folder) {
			*folder = "";
		}
	}
}