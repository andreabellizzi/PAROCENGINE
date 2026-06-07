#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <assert.h>
#include <stdexcept>

#ifndef LOG_FILE
    #define LOG_FILE "paroc.log"
    #warning "LOG_FILE is not defined, using default: paroc.log"
#endif

#define LOG_LEVEL_DEBUG 0
#define LOG_LEVEL_INFO 1
#define LOG_LEVEL_WARNING 2
#define LOG_LEVEL_ERROR 3

namespace PAROC {

    enum LogLevel { DEBUG=LOG_LEVEL_DEBUG, INFO=LOG_LEVEL_INFO, WARNING=LOG_LEVEL_WARNING, ERROR=LOG_LEVEL_ERROR };

    struct Logger {
        static std::ofstream logFile;

        static bool init(const std::string& filename = LOG_FILE) {
            logFile.open(filename, std::ios::out | std::ios::trunc);
            if (!logFile.is_open()) {
                std::cerr << "Failed to open log file: " << filename << std::endl;
                return false;
            }
            return true;
        }

        static void log(const std::string& message, LogLevel level = INFO) {
            assert(logFile.is_open() && "Log file is not initialized");

            std::ostringstream logStream;
            std::time_t now = std::time(0);
            std::tm *ltm = std::localtime(&now);
            logStream << "[" << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << "] ";
            switch (level) {
                case DEBUG:
                    logStream << "[DEBUG] ";
                    break;
                case INFO:
                    logStream << "[INFO] ";
                    break;
                case WARNING:
                    logStream << "[WARNING] ";
                    break;
                case ERROR:
                    logStream << "[ERROR] ";
                    break;
            }
            logStream << message << std::endl;
            logFile << logStream.str();
            logFile.flush();
        }

        static void close() {
            if (logFile.is_open()) {
                logFile.close();
            }
        }
    };
};

#ifdef LOG_LEVEL
    #if LOG_LEVEL == LOG_LEVEL_DEBUG
        #define LOG_DEBUG(msg) { PAROC::Logger::log(msg, PAROC::DEBUG); }
        #define LOG_INFO(msg)  { PAROC::Logger::log(msg, PAROC::INFO); }
        #define LOG_WARNING(msg) { PAROC::Logger::log(msg, PAROC::WARNING); }
        #define LOG_ERROR(msg) { PAROC::Logger::log(msg, PAROC::ERROR); }
    #elif LOG_LEVEL == LOG_LEVEL_INFO
        #define LOG_DEBUG(msg) 
        #define LOG_INFO(msg)  { PAROC::Logger::log(msg, PAROC::INFO); }
        #define LOG_WARNING(msg) { PAROC::Logger::log(msg, PAROC::WARNING); }
        #define LOG_ERROR(msg) { PAROC::Logger::log(msg, PAROC::ERROR); }
    #elif LOG_LEVEL == LOG_LEVEL_WARNING
        #define LOG_DEBUG(msg) 
        #define LOG_INFO(msg)  
        #define LOG_WARNING(msg) { PAROC::Logger::log(msg, PAROC::WARNING); }
        #define LOG_ERROR(msg) { PAROC::Logger::log(msg, PAROC::ERROR); }
    #elif LOG_LEVEL == LOG_LEVEL_ERROR
        #define LOG_DEBUG(msg) 
        #define LOG_INFO(msg)  
        #define LOG_WARNING(msg) 
        #define LOG_ERROR(msg) { PAROC::Logger::log(msg, PAROC::ERROR); }
    #else
        #error "Invalid LOG_LEVEL defined"
    #endif
#else
    #error "LOG_LEVEL is not defined"
#endif

#endif // LOGGER_HPP