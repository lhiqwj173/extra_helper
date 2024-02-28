#include <memory>
#include <cstring>

#include "lzma.h"
#include "../path/path.h"
#include "../file/file.h"
#include "../sys/sys.h"

#include "7z/C/LzmaEnc.h"
#include "7z/C/LzmaDec.h"

//////////////////////////////
// ����7z��ѹ���ļ�
//////////////////////////////
// win
#ifdef _WIN32
const char * fiel7z = "C:/Windows/7z.exe";
#else
const char * fiel7z = "/usr/bin/7z";
#endif // DEBUG

// ��ѹ���ļ�
// ���سɹ����
bool _decompress(const std::string& file_path, const int level, bool compress = true) {
	// ����ļ�
	std::string out_file_path = file_path + ".temp";

	// ��ʱ�ļ���
	std::string temp_folder;

	// ִ��������
	std::string cmd = fiel7z;
	std::string r;
	// ����������ִ��ѹ��ָ��
	if (compress) {
		cmd += " a -mx" + std::to_string(level) + " " + out_file_path + " " + file_path;
	}
	if (!compress) {
		std::string folder;
		std::string filename;
		extra::file::split_file_name_folder(file_path, &folder, &filename);
		temp_folder = folder + "/temp/";
		extra::path::check_create_folder(temp_folder);
		cmd += " e " + file_path + " -o" + temp_folder;
		out_file_path = temp_folder + filename;
	}

	// ִ��������
	system(cmd.c_str());

	// �滻ԭ�ļ�
	remove(file_path.c_str());
	rename(out_file_path.c_str(), file_path.c_str());

	return true;
}

// ��ѹ���ļ�
bool extra::lzma::decompress(const std::string& file_path) {
	return _decompress(file_path, -1, false);
}

// ѹ���ļ�
bool extra::lzma::compress(const std::string& file_path, const int level) {
	return _decompress(file_path, level);
}


//////////////////////////////
// lzma sdk ��ѹ��
//////////////////////////////

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

std::unique_ptr<uint8_t[]> lzmaCompress(const uint8_t* input, uint32_t inputSize, uint32_t* outputSize, const int level) {
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

std::unique_ptr<uint8_t[]> lzmaDecompress(const uint8_t *input, uint32_t inputSize, uint32_t *outputSize) {
	if (inputSize < 13)
		return NULL; // invalid header!

	// extract the size from the header
	UInt64 size = 0;
	for (int i = 0; i < 8; i++)
		size |= (input[5 + i] << (i * 8));

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

// ��ѹ���ڴ�����
std::unique_ptr<uint8_t[]> extra::lzma::decompress_mem(const std::string& data, uint32_t& outputSize) {
	return lzmaDecompress((const uint8_t*)data.data(), data.size(), &outputSize);
}

// ��ѹ���ڴ�����
std::unique_ptr<uint8_t[]> extra::lzma::decompress_mem(const char* data, const uint32_t length, uint32_t& outputSize) {
	return lzmaDecompress((const uint8_t*)data, length, &outputSize);
}

// ��ѹ���ڴ�����
std::unique_ptr<uint8_t[]> extra::lzma::decompress_mem(const uint8_t* data, const uint32_t length, uint32_t& outputSize) {
	return lzmaDecompress(data, length, &outputSize);
}

// ѹ���ڴ�����
std::unique_ptr<uint8_t[]> extra::lzma::compress_mem(const std::string& data, uint32_t& outputSize, const int level){
	return lzmaCompress((const uint8_t*)data.data(), data.size(), &outputSize, level);
}