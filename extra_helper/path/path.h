#pragma once
#include "../defi.h"

#include <filesystem>
#include <algorithm>
#include <string>


namespace extra {
	namespace path {
		MYLIB_API void check_create_folder(const std::string& folder);

		MYLIB_API void clear_folder(const std::string& folder);

		#ifdef _WIN32
			#ifndef EXPORT
				template <typename T>
				MYLIB_IN_API void get_folder_files(const std::filesystem::path& dir_path, T& files);

				template <typename T>
				MYLIB_IN_API void get_folder_folders(const std::filesystem::path& dir_path, T& folders);

			#endif // !EXPORT
		#endif // _WIN32

		// 获取文件夹下的所有文件
		// 不会清空files
		// 模板 list / vector
		template <typename T>
		MYLIB_OUT_API void get_folder_files(const std::filesystem::path& dir_path, T& files) {
			// 遍历目录中的所有文件和文件夹
			for (const auto& entry : std::filesystem::directory_iterator(dir_path)) {
				// 判断是否是文件
				if (std::filesystem::is_regular_file(entry)) {
					files.push_back(entry.path().filename().string());
				}
			}
		}

		// 获取文件夹下的所有文件夹名
		// 不会清空folders
		// 模板 list / vector
		template <typename T>
		MYLIB_OUT_API void get_folder_folders(const std::filesystem::path& dir_path, T& folders) {
			// 遍历目录中的所有文件和文件夹
			for (const auto& entry : std::filesystem::directory_iterator(dir_path)) {
				// 判断是否是文件
				if (!std::filesystem::is_regular_file(entry)) {
					folders.push_back(entry.path().filename().string());
				}
			}
		}

	}
}