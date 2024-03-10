#include "log.h"
#include "../path/path.h"
#include "../sys/sys.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"

/*
spdlog::set_default_logger(m_pLogger);
console: trace
file: info
*/
std::shared_ptr<spdlog::logger> extra::log::getLogger(const std::string& log_name, const std::string& log_folder){
	static std::shared_ptr<spdlog::logger> m_pLogger;

	if (m_pLogger == nullptr) {
		// check folder
		extra::path::check_create_folder(log_folder);

		// check log name
		std::string _log_name;
		if (log_name.empty())_log_name = extra::sys::curExeName(false);
		else _log_name = log_name;

		//sink容器
		std::vector<spdlog::sink_ptr> vecSink;

		// Initialize the logger
		auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		console_sink->set_level(spdlog::level::trace);
		vecSink.push_back(console_sink);

		//auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(log_folder + "/" + log_name + ".log", 100 * 1024 * 1024, 15);
		auto file_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(log_folder + "/" + _log_name + ".log", 0, 0, false, 5);
		file_sink->set_level(spdlog::level::info);
		vecSink.push_back(file_sink);

		// 创建 pattern_formatter，定义输出格式
		auto formatter = std::make_unique<spdlog::pattern_formatter>("[%Y-%m-%d %H:%M:%S.%e][%s][%!][%L] %v");

		m_pLogger = std::make_shared<spdlog::logger>("multi", begin(vecSink), end(vecSink));
		m_pLogger->set_level(spdlog::level::trace);
		m_pLogger->set_formatter(std::move(formatter));
		spdlog::register_logger(m_pLogger);
		spdlog::set_default_logger(m_pLogger);

		spdlog::flush_on(spdlog::level::info);
		spdlog::flush_every(std::chrono::seconds(3));
	}

	return m_pLogger;
}

