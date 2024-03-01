#pragma once
#include "../defi.h"
#include <string>
#include <memory>

namespace extra {
	namespace lzma {
		// 解压缩文件
		MYLIB_API bool decompress(const std::string& file_path);

		// 压缩文件
		MYLIB_API bool compress(const std::string& file_path, const int level=5);

		// 解压缩内存数据
		MYLIB_API std::unique_ptr<uint8_t[]> decompress_mem(const std::string& data, uint32_t& outputSize);

		// 解压缩内存数据
		MYLIB_API  std::unique_ptr<uint8_t[]> decompress_mem(const char* data, const uint32_t length, uint32_t& outputSize);
		MYLIB_API  std::unique_ptr<uint8_t[]> decompress_mem(const uint8_t* data, const uint32_t length, uint32_t& outputSize);

		// 压缩内存数据
		MYLIB_API std::unique_ptr<uint8_t[]> compress_mem(const std::string& data, uint32_t& outputSize, const int level = 5);
	}
}