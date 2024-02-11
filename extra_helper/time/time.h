#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <assert.h>

#ifndef _MY_LIB_ 
#define _MY_LIB_ 

#ifdef __unix__ || __unix 
#define MYLIB_API       extern 
#else 
#define MYLIB_API   __declspec(dllexport) 
#endif 

namespace extra {
	namespace time {

		using timestamp_ms = unsigned long long;

		// ������ʱ���ת��Ϊ�ַ���
		// Ĭ�ϸ�ʽ %Y-%m-%d %H:%M:%S.%f
		MYLIB_API std::string strftime(const timestamp_ms timestamp, const std::string& format = "%Y-%m-%d %H:%M:%S.%f");

		// ����ʱ���ת��Ϊ�ַ���
		MYLIB_API std::string strftime(const time_t timestamp, const std::string& format = "%Y-%m-%d %H:%M:%S");

		// ���ַ���ת��Ϊʱ��� ����
		MYLIB_API timestamp_ms strptime(const std::string& time_str, const std::string& format = "%Y-%m-%d %H:%M:%S");
	}
}


#endif  // _MY_LIB_ 
