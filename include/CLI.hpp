#pragma once

#include <iostream>

class CLI {
private:
    enum FLAG {
        COMPRESS,
        EXTRACT,
        INPUT,
        OUTPUT
    };

    FLAG parseArg(char* arg);

    std::ostream& out = std::cout;
public:
    CLI() = default;
    CLI(std::ostream& out_) : out(out_) {}

    void parseArgs(int argc, char* argv[], std::string& target,
               std::string& inputFile, std::string& outputFile);

    void sendStatistic(int32_t rawDataSize, int32_t compressDataSize, int32_t extraDataSize);

};

class CLIException : public std::exception {
public:
    CLIException(const char* message_) : message(message_) {}

    const char* what() const noexcept override { return message; };
private:
    const char* message;
};
