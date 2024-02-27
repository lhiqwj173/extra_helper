#pragma once
#include "../defi.h"
#include <string>

namespace extra {
	namespace lzma {
		// 解压缩文件
		// 返回解压后的文件路径
		MYLIB_API bool decompress(const std::string& file_path);

		// 压缩文件
		// 返回压缩后的文件路径
		MYLIB_API bool compress(const std::string& file_path, const int level=5);
	}
}