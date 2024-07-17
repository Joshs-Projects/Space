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
    class Logging {
    private:
        std::mutex mutex_;

        std::string logFileName = "Logs.txt";

        //Private constructor
        Logging(){};

        //Private destructor
        ~Logging(){};

        int writeLineToFile(std::string line);

    public:
        static Logging& getInstance() {
            static Logging instance;
            return instance;
        }

        Logging(Logging const&) = delete;           //Prevents the C++ default copy constructor that copies the logger into a new logger object by deleting the constructor
        void operator=(const Logging&) = delete;    //Prevents the C++ default copy assignment operator that copies the logger values into a new logger object by deleting the copy assignment operator



        void log(bool isError, const std::string& className, const std::string& objectName, const std::string& message);
    };

}


#endif //SPACE_LOGGING_H
