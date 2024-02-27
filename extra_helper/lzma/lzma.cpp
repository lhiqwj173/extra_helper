#include <memory>

#include "lzma.h"
#include "LzmaEnc.h"
#include "LzmaDec.h"

long get_file_size(FILE* file) {
	fseek(file, 0, SEEK_END); // 移动文件指针到文件末尾
	long fileSize = ftell(file); // 获取文件指针的位置，即文件大小

	// 移动文件指针到文件开头
	fseek(file, 0, SEEK_SET);

	return fileSize;
}

static void* _lzmaAlloc(ISzAllocPtr, size_t size) {
	return new uint8_t[size];
}
static void _lzmaFree(ISzAllocPtr, void* addr) {
	if (!addr)
		return;

	delete[] reinterpret_cast<uint8_t*>(addr);
}

static ISzAlloc _allocFuncs = {
	_lzmaAlloc, _lzmaFree
};

std::unique_ptr<uint8_t[]> lzmaCompress(const uint8_t* input, uint32_t inputSize, uint32_t* outputSize, const int level = -1) {
	std::unique_ptr<uint8_t[]> result;

	// set up properties
	CLzmaEncProps props;
	LzmaEncProps_Init(&props);
	if (inputSize >= (1 << 20))
		props.dictSize = 1 << 20; // 1mb dictionary
	else
		props.dictSize = inputSize; // smaller dictionary = faster!
	props.fb = 40;
	if (level >= 0) props.level = level;

	// prepare space for the encoded properties
	SizeT propsSize = 5;
	uint8_t propsEncoded[5];

	// allocate some space for the compression output
	// this is way more than necessary in most cases...
	// but better safe than sorry
	//   (a smarter implementation would use a growing buffer,
	//    but this requires a bunch of fuckery that is out of
	///   scope for this simple example)
	SizeT outputSize64 = inputSize * 1.5;
	if (outputSize64 < 1024)
		outputSize64 = 1024;
	auto output = std::make_unique<uint8_t[]>(outputSize64);

	int lzmaStatus = LzmaEncode(
		output.get(), &outputSize64, input, inputSize,
		&props, propsEncoded, &propsSize, 0,
		NULL,
		&_allocFuncs, &_allocFuncs);

	*outputSize = outputSize64 + 13;
	if (lzmaStatus == SZ_OK) {
		// tricky: we have to generate the LZMA header
		// 5 bytes properties + 8 byte uncompressed size
		result = std::make_unique<uint8_t[]>(outputSize64 + 13);
		uint8_t* resultData = result.get();

		memcpy(resultData, propsEncoded, 5);
		for (int i = 0; i < 8; i++)
			resultData[5 + i] = (inputSize >> (i * 8)) & 0xFF;
		memcpy(resultData + 13, output.get(), outputSize64);
	}

	return result;
}

std::unique_ptr<uint8_t[]> lzmaDecompress(const uint8_t* input, uint32_t inputSize, uint32_t* outputSize) {
	if (inputSize < 13)
		return NULL; // invalid header!

	// extract the size from the header
	UInt64 size = 0;
	for (int i = 0; i < 8; i++)
		size |= (input[5 + i] << (i * 8));

	//if (size <= (256 * 1024 * 1024)) {
	//	auto blob = std::make_unique<uint8_t[]>(size);

	//	ELzmaStatus lzmaStatus;
	//	SizeT procOutSize = size, procInSize = inputSize - 13;
	//	int status = LzmaDecode(blob.get(), &procOutSize, &input[13], &procInSize, input, 5, LZMA_FINISH_END, &lzmaStatus, &_allocFuncs);

	//	if (status == SZ_OK && procOutSize == size) {
	//		*outputSize = size;
	//		return blob;
	//	}
	//}

	auto blob = std::make_unique<uint8_t[]>(size);

	ELzmaStatus lzmaStatus;
	SizeT procOutSize = size, procInSize = inputSize - 13;
	int status = LzmaDecode(blob.get(), &procOutSize, &input[13], &procInSize, input, 5, LZMA_FINISH_END, &lzmaStatus, &_allocFuncs);

	if (status == SZ_OK && procOutSize == size) {
		*outputSize = size;
		return blob;
	}

	return NULL;
}

// 解压缩文件
// 返回成功与否
bool _decompress(const std::string& file_path, const int level, bool compress = true) {
	FILE* file = fopen(file_path.c_str(), "rb");
	if (file) {
		// 获取文件大小
		auto file_size = get_file_size(file);

		// 读取数据
		std::unique_ptr<uint8_t[]> buffer(new uint8_t[file_size]);
		size_t read_size = fread(buffer.get(), 1, file_size, file);

		// 压缩数据
		uint32_t compressedSize;
		std::unique_ptr<uint8_t[]> compressedBlob;
		if (compress) {
			compressedBlob = lzmaCompress(buffer.get(), read_size, &compressedSize, level);
		}
		else {
			compressedBlob = lzmaDecompress(buffer.get(), read_size, &compressedSize);
		}

		fclose(file);

		// 写入文件
		std::string out_file_path = file_path + ".temp";
		file = fopen(out_file_path.c_str(), "wb");
		if (file) {
			fwrite(compressedBlob.get(), 1, compressedSize, file);
			fclose(file);
		}

		// 替换原文件
		remove(file_path.c_str());
		rename(out_file_path.c_str(), file_path.c_str());

		return true;
	}
	return false;
}


// 解压缩文件
// 返回解压后的文件路径
bool extra::lzma::decompress(const std::string& file_path) {
	return _decompress(file_path, -1, false);
}

// 压缩文件
// 返回压缩后的文件路径
bool extra::lzma::compress(const std::string& file_path, const int level) {
	return _decompress(file_path, level);
}