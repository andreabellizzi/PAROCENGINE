#ifndef OSDEPENDENTSTUFF_HPP
#define OSDEPENDENTSTUFF_HPP

#ifdef _WIN32
    #include <windows.h>
    #define OS_NAME "WINDOWS"
#elif __linux__
    #include <unistd.h>
    #define OS_NAME "LINUX"
#elif __APPLE__
    #include <unistd.h>
    #define OS_NAME "MACOS"
#else
    #error "Unsupported OS"
#endif

namespace PAROC {
    namespace OS {
        extern char executablePath[1024];
        bool initExecutablePath();
    }
} // namespace PAROC

#endif // OSDEPENDENTSTUFF_HPP