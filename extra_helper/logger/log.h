#pragma once
#include "../defi.h"
#include <string>

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "spdlog/spdlog.h"

namespace extra {
	namespace log {

		// 初始化日志
		MYLIB_API std::shared_ptr<spdlog::logger> getLogger(const std::string& log_name = "", const std::string& log_folder = "./log");

		// 有代码行号
		#define LTRACE(...)      SPDLOG_LOGGER_CALL(extra::log::getLogger().get(), spdlog::level::trace, __VA_ARGS__)
		#define LDEBUG(...)      SPDLOG_LOGGER_CALL(extra::log::getLogger().get(), spdlog::level::debug, __VA_ARGS__)
		#define LINFO(...)       SPDLOG_LOGGER_CALL(extra::log::getLogger().get(), spdlog::level::info, __VA_ARGS__)
		#define LWARN(...)       SPDLOG_LOGGER_CALL(extra::log::getLogger().get(), spdlog::level::warn, __VA_ARGS__)
		#define LERR(...)      SPDLOG_LOGGER_CALL(extra::log::getLogger().get(), spdlog::level::err, __VA_ARGS__)
		#define LCRITICAL(...)   SPDLOG_LOGGER_CALL(extra::log::getLogger().get(), spdlog::level::critical, __VA_ARGS__)
	}
}
