#include <iostream>
#include <vector>
#include "extra_helper/path/path.h"

int main() {
	std::cout << "\n生成 AAA 目录" << std::endl;
	extra::path::check_create_folder(R"(AAA)");

	std::cout << "\n当前目录文件:" << std::endl;
	std::vector<std::string> files;
	extra::path::get_folder_files<std::vector<std::string>> (R"(\)", files);
	for (auto& file : files) {
		std::cout << file << std::endl;
	}

	std::cout << "\n当前目录文件夹:" << std::endl;
	std::vector<std::string> folders;
	extra::path::get_folder_folders<std::vector<std::string>>(R"(\)", folders);
	for (auto& folder : folders) {
		std::cout << folder << std::endl;
	}

}