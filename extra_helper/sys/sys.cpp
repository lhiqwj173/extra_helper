#include "sys.h"
#include <cstdio>

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