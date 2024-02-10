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

#ifdef LINUX 
#define MYLIB_API       extern 
#else 
#define MYLIB_API   __declspec(dllexport) 
#endif 

namespace extra {
	namespace time {

		using timestamp_ms = unsigned long long;

		// 将毫秒时间戳转换为字符串
		// 默认格式 %Y-%m-%d %H:%M:%S.%f
		MYLIB_API std::string strptime(const timestamp_ms timestamp, const std::string& format = "%Y-%m-%d %H:%M:%S.%f");
	}
}


#endif  // _MY_LIB_ 
