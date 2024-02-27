#include <iostream>
#include <vector>
#include "extra_helper/lzma/lzma.h"
#include <ctime>

int main(int argc, char** argv) {
	if (argc < 3) {
		std::cout << "Usage: " << argv[0] << "<type: 0压缩 / 1解压> <file>" << std::endl;
		return 1;
	}

	int type = std::stoi(argv[1]);
	std::string file = argv[2];

	//int type = 1;
	//std::string file = R"(C:\Users\lh\Desktop\temp\depth_1708942514987)";

	auto t = time(0);
	if (type == 0) {
		std::cout << "压缩文件: " << file << std::endl;
		extra::lzma::compress(file);
	}
	else {
		std::cout << "解压文件: " << file << std::endl;
		extra::lzma::decompress(file);
	}

	std::cout << "耗时: " << time(0) - t << "s" << std::endl;
}