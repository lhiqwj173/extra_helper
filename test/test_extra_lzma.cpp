#include <iostream>
#include <vector>
#include "extra_helper/lzma/lzma.h"
#include <ctime>

int main(int argc, char** argv) {
	auto t = time(0);

	// ԭʼ����
	std::string data = "here's something that should compress pretty well: abcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdef";
	std::cout << "ԭʼ���ݳ���: " << data.size() << std::endl;

	uint32_t outputSize;
	auto compressed_data = extra::lzma::compress_mem(data, outputSize, 9);
	std::cout << "ѹ�������ݳ���: " << outputSize << std::endl;
	
	auto decompressed_data = extra::lzma::decompress_mem(compressed_data.get(), outputSize, outputSize);
	std::cout << "��ѹ�����ݳ���: " << outputSize << std::endl;

	std::cout << "��ʱ: " << time(0) - t << "s" << std::endl;
}