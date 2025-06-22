//
// Created by Josh on 13/07/2024.
//

#include "Logger.h"
#include <iostream>

namespace Developer_Tools {
    Logger::Logger() {
        logFile.open("Log.txt", std::ios::app); // Append mode
        if (!logFile.is_open()) {
            std::cerr << "Failed to open log file." << std::endl;
        }
    }

    Logger::~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    Logger &Logger::getInstance() {
        static Logger instance;  // Thread-safe in C++11 and later
        return instance;
    }

    void Logger::log(const std::string &message, LogLevel level) {
        std::lock_guard<std::mutex> guard(logMutex);

        std::string levelStr;
        switch (level){
            case LogLevel::Info: levelStr = "[INFO]"; break;
            case LogLevel::Error: levelStr = "[ERROR]"; break;
            case LogLevel::Critical: levelStr = "[CRITICAL]"; break;
        }

        // Optional timestamp
        //std::time_t now = std::time(nullptr);
        //char timestamp[30];
        //std::strftime(timestamp, sizeof(timestamp), "%F %T", std::localtime(&now));

        time_t timestamp;
        char output[100];
        struct tm * datetime;

        time(&timestamp);
        datetime = localtime(&timestamp);

        strftime(output, 100, "%Y-%m-%d %H:%M:%S", datetime);
        std::cout << output << "\n";

        if (logFile.is_open()) {
            logFile << output << " " << levelStr << " " << message << std::endl;
        }
    }

    void Logger::logEntry(const std::string& functionName){
        log("Entered function: " + functionName, LogLevel::Info);
    }

    void Logger::logExit(const std::string& functionName){
        log("Exited function: " + functionName, LogLevel::Info);
    }

    void Logger::logInformation(const std::string& message){
        log(message, LogLevel::Info);
    }

    void Logger::logError(const std::string& message){
        log(message, LogLevel::Error);
    }

    void Logger::logCritical(const std::string& message){
        log(message, LogLevel::Critical);
    }
}
