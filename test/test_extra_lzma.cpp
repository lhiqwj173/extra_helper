#include <iostream>
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
}