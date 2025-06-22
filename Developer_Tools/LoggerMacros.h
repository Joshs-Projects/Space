//
// Created by Josh on 22/06/2025.
//

#pragma once

#include "Logger.h"

#ifdef ENABLE_LOGGING
    #define LOG_ENTRY() Developer_Tools::Logger::getInstance().logEntry(__FUNCTION__)
    #define LOG_EXIT()  Developer_Tools::Logger::getInstance().logExit(__FUNCTION__)
    #define LOG_INFO(msg) Developer_Tools::Logger::getInstance().logInformation(msg)
    #define LOG_ERROR(msg) Developer_Tools::Logger::getInstance().logError(msg)
    #define LOG_CRITICAL(msg) Developer_Tools::Logger::getInstance().logCritical(msg)
#else
    #define LOG_ENTRY()
    #define LOG_EXIT()
    #define LOG_INFO(msg)
    #define LOG_ERROR(msg)
    #define LOG_CRITICAL(msg)
#endif

