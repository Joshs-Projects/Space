//
// Created by Josh on 13/07/2024.
//

#include "Logging.h"

int Developer_Tools::Logging::writeLineToFile(std::string line) {
    std::ofstream outFile;

    outFile.open(this->logFileName);

    if(!outFile){
        std::cerr << "Unable to open file";
        return 0;
    }

    outFile << line << std::endl;

    outFile.close();

    return 1;
}

void Developer_Tools::Logging::log(const bool isError, const std::string& className, const std::string& objectName, const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    std::string newLine;

    if (isError) {
        newLine = "ERROR: ";
    } else {
        newLine = "Message: ";
    }

    newLine = newLine + "[" + className + ":" + objectName + "] - " + message + "\n";

    writeLineToFile(newLine);
}


