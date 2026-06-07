#include "PAROC.hpp"
#include "logger.hpp"
#include "osdependentstuff.hpp"
#include <filesystem>
#include <iostream>

std::ofstream PAROC::Logger::logFile;


int main(int argc, char *argv[]) {
    if (!PAROC::OS::initExecutablePath()) {
        std::cerr << "Failed to initialize executable path" << std::endl;
        return 1;
    }
    
    std::filesystem::current_path(PAROC::OS::executablePath);
    if (!PAROC::Logger::init("paroc.log")) {
        std::cout << "Failed to initialize logger" << std::endl;
        return 1;
    }

    LOG_INFO("PAROC Engine " PAROC_VERSION " started" );
    PAROC::Logger::close();
    return 0;
}