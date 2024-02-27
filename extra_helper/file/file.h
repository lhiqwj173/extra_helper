#pragma once
#include "../defi.h"
#include <string>

namespace extra {
	namespace file {
		// �����ļ���С
		MYLIB_API long get_file_size(const std::string& file);

		MYLIB_API void split_file_name_folder(const std::string& filepath, std::string* folder, std::string* filename);
	}
}