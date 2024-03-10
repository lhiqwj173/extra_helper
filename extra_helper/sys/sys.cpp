#include "sys.h"
#include <cstdio>
#include <filesystem>

#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <unistd.h>
#endif

#ifdef _WIN32
auto command_open = _popen;
auto command_close = _pclose;
#else
auto command_open = popen;
auto command_close = pclose;

#endif // _WIN32

bool extra::sys::executeCommand(const std::string& command, std::string &rets) {
    FILE* pipe = command_open(command.c_str(), "r");
    if (!pipe) {
        return false;
    }

    char buffer[128];
    rets = "";

    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL) {
            rets += buffer;
        }
    }

    command_close(pipe);
    return true;
}

std::filesystem::path _curExePath() {
    std::string exeName;

#if defined(_WIN32)
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    exeName = buffer;
#elif defined(__linux__)
    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1) {
        buffer[len] = '\0';
        exeName = buffer;
    }
#endif

    return std::filesystem::canonical(exeName);
}

// 当前可执行文件路径
std::string extra::sys::curExePath() {
    return _curExePath().string();
}

// 当前可执行文件文件名
// exp : 是否包含扩展名
std::string extra::sys::curExeName(bool exp){
    auto path = _curExePath();
	if (exp) {
		return path.filename().string();
	} else {
		return path.stem().string();
	}
}