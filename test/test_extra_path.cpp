#include <iostream>
#include <vector>
#include "../extra_helper/path/path.h"

int main() {
	extra::path::check_create_folder(R"(C:\Users\lh\Desktop\temp\AAA)");

	std::vector<std::string> files;
	extra::path::get_folder_files<std::vector<std::string>> (R"(C:\Users\lh\Desktop\temp\)", files);
	for (auto& file : files) {
		std::cout << file << std::endl;
	}

	std::vector<std::string> folders;
	extra::path::get_folder_folders<std::vector<std::string>>(R"(C:\Users\lh\Desktop\temp\)", folders);
	for (auto& folder : folders) {
		std::cout << folder << std::endl;
	}

}