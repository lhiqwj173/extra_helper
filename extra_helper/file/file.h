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

// ��ȡ�ļ����µ������ļ�
// �������files
// ģ�� list / vector
template <typename T>
void get_folder_files(const std::filesystem::path& dir_path, T& files) {
	// ����Ŀ¼�е������ļ����ļ���
	for (const auto& entry : std::filesystem::directory_iterator(dir_path)) {
		// �ж��Ƿ����ļ�
		if (std::filesystem::is_regular_file(entry)) {
			files.push_back(entry.path().filename().string());
		}
	}
}

// ��ȡ�ļ����µ������ļ�����
// �������folders
// ģ�� list / vector
template <typename T>
void get_folder_folders(const std::filesystem::path& dir_path, T& folders) {
	// ����Ŀ¼�е������ļ����ļ���
	for (const auto& entry : std::filesystem::directory_iterator(dir_path)) {
		// �ж��Ƿ����ļ�
		if (!std::filesystem::is_regular_file(entry)) {
			folders.push_back(entry.path().filename().string());
		}
	}
}

#endif  // _MY_LIB_ 
