#include "file.h"

long extra::file::get_file_size(const std::string& file_path) {
	FILE * file = fopen(file_path.c_str(), "rb");
	if (file == NULL) {
		return -1;
	}

	fseek(file, 0, SEEK_END); // �ƶ��ļ�ָ�뵽�ļ�ĩβ
	long fileSize = ftell(file); // ��ȡ�ļ�ָ���λ�ã����ļ���С

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