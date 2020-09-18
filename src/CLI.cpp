#include <iostream>
#include <cstring>

#include "CLI.hpp"

auto CLI::parseArg(char* arg) -> FLAG {
    if (std::strcmp(arg, "-c") == 0) {
        return COMPRESS;
    }
    if (std::strcmp(arg, "-u") == 0) {
        return EXTRACT;
    }
    if (std::strcmp(arg, "-f") == 0 || std::strcmp(arg, "--file") == 0) {
        return INPUT;
    }
    if (std::strcmp(arg, "-o") == 0 || std::strcmp(arg, "--output") == 0) {
        return OUTPUT;
    }
    throw CLIException("Unknown argument.");
}

void CLI::parseArgs(int argc, char* argv[], std::string& target,
                    std::string& inputFile, std::string& outputFile) {
    if (argc != 6) {
        throw CLIException("Error: uncorrect number of arguments.");
    }

    target = inputFile = outputFile = "";
    for (int i = 1; i < argc; ++i) {
        auto arg = parseArg(argv[i]);
        if (arg == COMPRESS) {
            if (target != "") {
                throw CLIException("Error: uncorrect arguments.");
            }
            target = "compress";
        } else if (arg == EXTRACT) {
            if (target != "") {
                throw CLIException("Error: uncorrect arguments.");
            }
            target = "extract";
        } else if (arg == INPUT) {
            if (inputFile != "" || i == argc - 1) {
                throw CLIException("Error: uncorrect arguments.");
            }
            inputFile = argv[++i];
        } else if (arg == OUTPUT) {
            if (outputFile != "" || i == argc - 1) {
                throw CLIException("Error: uncorrect arguments.");
            }
            outputFile = argv[++i];
        }
    }
}

void CLI::sendStatistic(int32_t rawDataSize, int32_t compressDataSize, int32_t extraDataSize) {
    std::cout << rawDataSize << "\n" << compressDataSize << "\n" << extraDataSize << std::endl;
}
