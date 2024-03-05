#include <iostream>
#include <fstream>
#include <vector>
#include "extra_helper/lzma/lzma.h"
#include <ctime>

int main(int argc, char** argv) {
	auto t = time(0);
	
	// 原始数据
	std::string data = "here's something that should compress pretty well: abcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdef";
	std::cout << "原始数据长度: " << data.size() << std::endl;

	uint32_t outputSize;
	auto compressed_data = extra::lzma::compress_mem(data, outputSize, 9);
	std::cout << "压缩后数据长度: " << outputSize << std::endl;
	
	auto decompressed_data = extra::lzma::decompress_mem(compressed_data.get(), outputSize, outputSize);
	std::cout << "解压后数据长度: " << outputSize << std::endl;

	std::cout << "耗时: " << time(0) - t << "s" << std::endl;

	// 读取二进制数据
	std::fstream file(R"(D:\wsl_ubuntu\rootfs\home\lh\projects\c_market_data\bin\x64\Debug\market\raw)", std::ios::in | std::ios::binary);
	std::string raw;
	char buffer[1024] = {0};
	if (file.is_open()) {
		while (!file.eof()) {
			file.read(buffer, 1024);
			raw.append(buffer, file.gcount());
		}
	}

	auto decompressed_raw = extra::lzma::decompress_mem(raw, outputSize);
	std::cout << "解压后数据长度: " << outputSize << std::endl;

	extra::lzma::decompress_mem_thread(raw, [](std::unique_ptr<uint8_t[]> res, uint32_t size) {
		std::cout << "解压后数据长度: " << size << std::endl;
		});

	getchar();
}