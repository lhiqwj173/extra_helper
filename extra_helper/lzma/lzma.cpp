#include <memory>
#include <cstring>

#include "lzma.h"
#include "../path/path.h"
#include "../file/file.h"
#include "../sys/sys.h"

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
// ���ؽ�ѹ����ļ�·��
bool extra::lzma::decompress(const std::string& file_path) {
	return _decompress(file_path, -1, false);
}

// ѹ���ļ�
// ����ѹ������ļ�·��
bool extra::lzma::compress(const std::string& file_path, const int level) {
	return _decompress(file_path, level);
}