//
// Created by Josh on 13/07/2024.
//

#ifndef SPACE_LOGGING_H
#define SPACE_LOGGING_H

#include <string>
#include <iostream>
#include <fstream>
#include <mutex>

namespace Developer_Tools {
    enum class LogLevel {
        Info,
        Error,
        Critical
    };

    class Logger {
    private:
        Logger();                              // Constructor (private)
        ~Logger();                             // Destructor

        Logger(const Logger &) = delete;        // Prevent copying
        Logger &operator=(const Logger &) = delete;

        std::ofstream logFile;
        std::mutex logMutex;

    public:
        // Access the singleton instance
        static Logger &getInstance();

        // Logging method
        void log(const std::string& message, LogLevel level);

        void logEntry(const std::string& functionName);

        void logExit(const std::string& functionName);

        void logInformation(const std::string& message);

        void logCritical(const std::string& message);

        void logError(const std::string& message);
    };
}
#endif //SPACE_LOGGING_H
