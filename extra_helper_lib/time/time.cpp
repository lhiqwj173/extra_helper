#include "time.h"

// ������ʱ���ת��Ϊ�ַ���
// Ĭ�ϸ�ʽ %Y-%m-%d %H:%M:%S.%f
std::string extra::time::strptime(const timestamp_ms timestamp, const std::string& format) {
	// ����ʱ���ת��Ϊʱ��ṹ��
	std::time_t time_t_value = static_cast<std::time_t>(timestamp / 1000);
	std::tm* tm_ptr = std::localtime(&time_t_value);
	if (tm_ptr == nullptr) {
		// ��ȡ�������
		int err = errno;
		// ���������Ϣ
		std::cerr << "Error: " << err << std::endl;
	}

	// �������
	int milliseconds = static_cast<int>(timestamp % 1000);

	// ��¼�����ʽ�ַ�
	std::string _format = format;
	std::size_t ms_pos = _format.find("%f");
	if (ms_pos != std::string::npos) _format[ms_pos] = '$';

	// ����stringstream����
	std::stringstream ss;

	// ʹ��strftime������ʽ��ʱ��
	ss << std::put_time(tm_ptr, _format.c_str());
	std::string output = ss.str();

	// ��Ӻ���
	if (ms_pos != std::string::npos) {
		std::size_t ms_pos_out = output.find("$f");

		// �滻����
		std::string ms_str = std::to_string(milliseconds);
		int zero_need_fill = 3 - ms_str.size();
		if (zero_need_fill > 0) ms_str.insert(0, zero_need_fill, '0');

		output.replace(ms_pos_out, 2, ms_str);
	}

	return output;
}