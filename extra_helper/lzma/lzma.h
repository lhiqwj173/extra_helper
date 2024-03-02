#pragma once
#include "../defi.h"
#include <string>
#include <memory>
#include <functional>

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
		MYLIB_API std::unique_ptr<uint8_t[]> compress_mem(const char* data, const uint32_t length, uint32_t& outputSize, const int level = 5);

		// 在另外的线程中解压缩文件
		MYLIB_API void decompress_thread(const std::string& file_path, std::function<void(bool)> cb);
		MYLIB_API void compress_thread(const std::string& file_path, const int level, std::function<void(bool)> cb);
		MYLIB_API void decompress_mem_thread(const std::string& data, std::function<void(std::unique_ptr<uint8_t[]>, uint32_t)> cb);
		MYLIB_API void decompress_mem_thread(const char* data, const uint32_t length, std::function<void(std::unique_ptr<uint8_t[]>, uint32_t)> cb);
		MYLIB_API void decompress_mem_thread(const uint8_t* data, const uint32_t length, std::function<void(std::unique_ptr<uint8_t[]>, uint32_t)> cb);
		MYLIB_API void compress_mem_thread(const std::string& data, const int level, std::function<void(std::unique_ptr<uint8_t[]>, uint32_t)> cb);
		MYLIB_API void compress_mem_thread(const char* data, const uint32_t length, const int level, std::function<void(std::unique_ptr<uint8_t[]>, uint32_t)> cb);
	}
}