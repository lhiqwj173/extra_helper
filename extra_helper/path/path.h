#pragma once
#include <filesystem>
#include <algorithm>

namespace extra {
	namespace path {
		MYLIB_API void check_create_folder(const std::string& folder);

		// ��ȡ�ļ����µ������ļ�
		// �������files
		// ģ�� list / vector
		template <typename T>
		MYLIB_API void get_folder_files(const std::filesystem::path& dir_path, T& files) {
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
		MYLIB_API void get_folder_folders(const std::filesystem::path& dir_path, T& folders) {
			// ����Ŀ¼�е������ļ����ļ���
			for (const auto& entry : std::filesystem::directory_iterator(dir_path)) {
				// �ж��Ƿ����ļ�
				if (!std::filesystem::is_regular_file(entry)) {
					folders.push_back(entry.path().filename().string());
				}
			}
		}

	}
}