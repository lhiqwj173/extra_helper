#pragma once
#include "../defi.h"
#include <string>

namespace extra {
	namespace lzma {
		// ��ѹ���ļ�
		// ���ؽ�ѹ����ļ�·��
		MYLIB_API bool decompress(const std::string& file_path);

		// ѹ���ļ�
		// ����ѹ������ļ�·��
		MYLIB_API bool compress(const std::string& file_path, const int level=5);
	}
}