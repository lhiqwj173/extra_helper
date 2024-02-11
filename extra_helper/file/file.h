#include <filesystem>
#include <algorithm>

#ifndef _MY_LIB_ 
#define _MY_LIB_ 

#ifdef __unix__
#define MYLIB_API       extern 
#elif defined(__unix)
#define MYLIB_API       extern 
#else 
#define MYLIB_API   __declspec(dllexport) 
#endif 

// 获取文件夹下的所有文件
// 不会清空files
// 模板 list / vector
template <typename T>
void get_folder_files(const std::filesystem::path& dir_path, T& files) {
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
void get_folder_folders(const std::filesystem::path& dir_path, T& folders) {
	// 遍历目录中的所有文件和文件夹
	for (const auto& entry : std::filesystem::directory_iterator(dir_path)) {
		// 判断是否是文件
		if (!std::filesystem::is_regular_file(entry)) {
			folders.push_back(entry.path().filename().string());
		}
	}
}

#endif  // _MY_LIB_ 
