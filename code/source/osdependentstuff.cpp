#include "osdependentstuff.hpp"

char PAROC::OS::executablePath[1024] = {0};

bool PAROC::OS::initExecutablePath() {
#ifdef _WIN32
    GetModuleFileNameA(NULL, executablePath, MAX_PATH);
    for (int i = strlen(executablePath) - 1; i >= 0; --i) {
        if (executablePath[i] == '\\') {
            executablePath[i] = '\0';
            break;
        }
    }
    return true;
#elif __linux__ || __APPLE__
    char path[1024];
    ssize_t count = readlink("/proc/self/exe", executablePath, sizeof(executablePath) - 1);
    if (count != -1) {
        executablePath[count] = '\0';
        return true;
    }
    return false;
#else
    return false;
#endif
}