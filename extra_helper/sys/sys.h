#pragma once
#include "../defi.h"

#include <string>

namespace extra {
	namespace sys {
		// 执行命令
		MYLIB_API bool executeCommand(const ::std::string& command, ::std::string& rets);

		// 当前可执行文件路径
		MYLIB_API ::std::string curExePath();

		// 当前可执行文件文件名
		MYLIB_API ::std::string curExeName(bool exp=true);
	}
}