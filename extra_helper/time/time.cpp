#include "time.h"
#include <list>

// 将毫秒时间戳转换为字符串
// 默认格式 %Y-%m-%d %H:%M:%S.%f
std::string extra::time::strftime(const timestamp_ms timestamp, const std::string& format) {
	assert(timestamp > 10000000000);

	// 将秒时间戳转换为时间结构体
	std::time_t time_t_value = static_cast<std::time_t>(timestamp / 1000);

	// 记录毫秒格式字符
	std::string _format = format;
	std::size_t ms_pos = _format.find("%f");
	if (ms_pos != std::string::npos) _format[ms_pos] = '$';

	// 格式化秒时间戳字符串
	std::string output = strftime(time_t_value, _format);

	// 添加毫秒
	if (ms_pos != std::string::npos) {
		std::size_t ms_pos_out = output.find("$f");

		// 计算毫秒
		int milliseconds = static_cast<int>(timestamp % 1000);

		// 替换毫秒
		std::string ms_str = std::to_string(milliseconds);
		int zero_need_fill = 3 - ms_str.size();
		if (zero_need_fill > 0) ms_str.insert(0, zero_need_fill, '0');

		output.replace(ms_pos_out, 2, ms_str);
	}

	return output;
}

// 将秒时间戳转换为字符串
// 默认格式 %Y-%m-%d %H:%M:%S
std::string extra::time::strftime(const time_t timestamp, const std::string& format) {
	assert(timestamp < 10000000000);

	// 将秒时间戳转换为时间结构体
	std::tm* tm_ptr = std::localtime(&timestamp);
	if (tm_ptr == nullptr) {
		// 获取错误代码
		int err = errno;
		// 输出错误信息
		std::cerr << "Error: " << err << std::endl;
	}

	// 创建stringstream对象
	std::stringstream ss;

	// 使用strftime函数格式化时间
	ss << std::put_time(tm_ptr, format.c_str());

	return ss.str();
}


// 将字符串转换为时间戳 毫秒
extra::time::timestamp_ms extra::time::strptime(const std::string& time_str, const std::string& format) {
	/*
	struct tm
	{
		int tm_sec;   // seconds after the minute - [0, 60] including leap second
		int tm_min;   // minutes after the hour - [0, 59]
		int tm_hour;  // hours since midnight - [0, 23]
		int tm_mday;  // day of the month - [1, 31]
		int tm_mon;   // months since January - [0, 11]
		int tm_year;  // years since 1900
		int tm_wday;  // days since Sunday - [0, 6]
		int tm_yday;  // days since January 1 - [0, 365]
		int tm_isdst; // daylight savings time flag
	};
	*/
	std::tm _tm = { 0 };
	int milliseconds = 0;
	size_t diff = 0;
	for (size_t i = 0; i < format.length(); i++) {
		if (format[i] == '%') {
			char flag = format[i + 1];
			if (flag == 'Y')
			{
				_tm.tm_year = std::stoi(time_str.substr(i + diff, 4)) - 1900;
				diff += 2;
			}
			else if (flag == 'm')
			{
				_tm.tm_mon = std::stoi(time_str.substr(i + diff, 2)) - 1;
			}
			else if (flag == 'd')
			{
				_tm.tm_mday = std::stoi(time_str.substr(i + diff, 2));
			}
			else if (flag == 'H')
			{
				_tm.tm_hour = std::stoi(time_str.substr(i + diff, 2));
			}
			else if (flag == 'M')
			{
				_tm.tm_min = std::stoi(time_str.substr(i + diff, 2));
			}
			else if (flag == 'S')
			{
				_tm.tm_sec = std::stoi(time_str.substr(i + diff, 2));
			}
			else if (flag == 'f')
			{
				milliseconds = std::stoi(time_str.substr(i + diff, 3));
				diff += 1;
			}


			i++;
		}
	}

	// 将时间结构体转换为时间戳
	std::time_t time_t_value = std::mktime(&_tm);
	extra::time::timestamp_ms timestamp = static_cast<timestamp_ms>(time_t_value) * 1000 + milliseconds;

	return timestamp;
}
