#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstring>
#include "extra_helper/lzma/lzma.h"

void test(std::string filepath) {
	std::string data;

	// read file_
	std::fstream file(filepath, std::ios::in | std::ios::binary);
	if (file.is_open()) {
		file.seekg(0, std::ios::end);
		data.resize(file.tellg());
		file.seekg(0, std::ios::beg);
		file.read(&data[0], data.size());
		file.close();
	}
	else return;

	// 输出
	printf("原始数据: %d \n", (int)data.size());
	extra::lzma::hexdump((uint8_t *)data.data(), 8);

	// compress
	uint32_t outputSize;
	auto compressed_data = extra::lzma::compress_mem(data, outputSize, 9);
	printf("压缩数据: %d \n", outputSize);
	extra::lzma::hexdump((uint8_t*)compressed_data.get(), outputSize);

	//// decompress
	//uint32_t outputSize_de;
	//auto decompressed_data = extra::lzma::decompress_mem(compressed_data.get(), outputSize, outputSize_de);
	//printf("压缩后解压数据: % d \n", outputSize_de);
	//extra::lzma::hexdump(decompressed_data.get(), 8);

	//// decompress_mem_thread
	//extra::lzma::decompress_mem_thread(compressed_data.get(), outputSize, [&](std::unique_ptr<uint8_t[]> res, uint32_t size) {
	//	printf("线程解压数据: % d \n", size);
	//	extra::lzma::hexdump(res.get(), 8);
	//});

	// compress_mem_thread
	extra::lzma::compress_mem_thread(data.data(), data.size(), 9, [&](std::unique_ptr<uint8_t[]> res, uint32_t size) {
		printf("线程压缩数据: %d \n", size);
		extra::lzma::hexdump(res.get(), size);

		// decompress
		uint32_t outputSize_de2;
		auto decompressed_data2 = extra::lzma::decompress_mem(res.get(), size, outputSize_de2);

		// 输出
		printf("线程压缩后解压数据: % d \n", outputSize_de2);
		extra::lzma::hexdump(decompressed_data2.get(), 8);
	});
	getchar();

	std::shared_ptr<char[]> data_2(new char[data.size()]);
	memcpy(data_2.get(), data.data(), data.size());

	// compress_mem_thread
	extra::lzma::compress_mem_thread(data_2, data.size(), 9, [&](std::unique_ptr<uint8_t[]> res, uint32_t size) {
		printf("线程压缩数据: %d \n", size);
		extra::lzma::hexdump(res.get(), size);

		// decompress
		uint32_t outputSize_de3;
		auto decompressed_data3 = extra::lzma::decompress_mem(res.get(), size, outputSize_de3);

		// 输出
		printf("线程压缩后解压数据: % d \n", outputSize_de3);
		extra::lzma::hexdump(decompressed_data3.get(), 8);
	});

	getchar();
}

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

	std::string raw_file = R"(D:\wsl_ubuntu\rootfs\home\lh\projects\c_market_data\bin\x64\Debug\market_d\raw)";
	test(raw_file);

	getchar();
}