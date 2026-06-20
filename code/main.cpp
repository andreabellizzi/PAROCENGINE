#include <filesystem>
#include <iostream>

#include "PAROC.hpp"
#include "logger.hpp"
#include "osdependentstuff.hpp"


int main(int argc, char *argv[]) {

    // Initialize executable path and set current working directory to it
    if (!PAROC::OS::initExecutablePath()) {
        std::cerr << "Failed to initialize executable path" << std::endl;
        return 1;
    }
    
    std::filesystem::current_path(PAROC::OS::executablePath);

    if (!PAROC::Logger::init("paroc.log")) {
        std::cerr << "Failed to initialize logger" << std::endl;
        return 1;
    }
    LOG_INFO("PAROC Engine " PAROC_VERSION " started" );

    
    
    PAROC::Logger::close();
    return 0;
}