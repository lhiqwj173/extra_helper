#include <iostream>
#include <vector>
#include "extra_helper/lzma/lzma.h"
#include <ctime>

int main(int argc, char** argv) {
	if (argc < 3) {
		std::cout << "Usage: " << argv[0] << "<type: 0ѹ�� / 1��ѹ> <file>" << std::endl;
		return 1;
	}

	int type = std::stoi(argv[1]);
	std::string file = argv[2];

	//int type = 1;
	//std::string file = R"(C:\Users\lh\Desktop\temp\depth_1708942514987)";

	auto t = time(0);
	if (type == 0) {
		std::cout << "ѹ���ļ�: " << file << std::endl;
		extra::lzma::compress(file);
	}
	else {
		std::cout << "��ѹ�ļ�: " << file << std::endl;
		extra::lzma::decompress(file);
	}

	std::cout << "��ʱ: " << time(0) - t << "s" << std::endl;
}