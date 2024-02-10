#include "time.h"

// 将毫秒时间戳转换为字符串
// 默认格式 %Y-%m-%d %H:%M:%S.%f
std::string extra::time::strptime(const timestamp_ms timestamp, const std::string& format) {
	// 将秒时间戳转换为时间结构体
	std::time_t time_t_value = static_cast<std::time_t>(timestamp / 1000);
	std::tm* tm_ptr = std::localtime(&time_t_value);
	if (tm_ptr == nullptr) {
		// 获取错误代码
		int err = errno;
		// 输出错误信息
		std::cerr << "Error: " << err << std::endl;
	}

	// 计算毫秒
	int milliseconds = static_cast<int>(timestamp % 1000);

	// 记录毫秒格式字符
	std::string _format = format;
	std::size_t ms_pos = _format.find("%f");
	if (ms_pos != std::string::npos) _format[ms_pos] = '$';

	// 创建stringstream对象
	std::stringstream ss;

	// 使用strftime函数格式化时间
	ss << std::put_time(tm_ptr, _format.c_str());
	std::string output = ss.str();

	// 添加毫秒
	if (ms_pos != std::string::npos) {
		std::size_t ms_pos_out = output.find("$f");

		// 替换毫秒
		std::string ms_str = std::to_string(milliseconds);
		int zero_need_fill = 3 - ms_str.size();
		if (zero_need_fill > 0) ms_str.insert(0, zero_need_fill, '0');

		output.replace(ms_pos_out, 2, ms_str);
	}

	return output;
}