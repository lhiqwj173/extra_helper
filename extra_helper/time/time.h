#pragma once
#include "../defi.h"

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <assert.h>


namespace extra {
	namespace time {

		using timestamp_ms = unsigned long long;

		// 将毫秒时间戳转换为字符串
		// 默认格式 %Y-%m-%d %H:%M:%S.%f
		MYLIB_API std::string strftime(const timestamp_ms timestamp, const std::string& format = "%Y-%m-%d %H:%M:%S.%f");

		// 将秒时间戳转换为字符串
		MYLIB_API std::string strftime(const time_t timestamp, const std::string& format = "%Y-%m-%d %H:%M:%S");

		// 将字符串转换为时间戳 毫秒
		MYLIB_API timestamp_ms strptime(const std::string& time_str, const std::string& format = "%Y-%m-%d %H:%M:%S");
	}
}


