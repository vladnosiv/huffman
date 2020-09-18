#include <iostream>
#include <fstream>
#include <cstring>
#include <tuple>

#include "CLI.hpp"
#include "HuffmanArchiver.hpp"

int main(int argc, char* argv[]) {
    CLI cli;
    std::string target, inputFile, outputFile;
    try {
        cli.parseArgs(argc, argv, target, inputFile, outputFile);
    } catch (CLIException& ex) {
        std::cout << "Parse arguments error:\n" << ex.what() << std::endl;
        return 0;
    }
    HuffmanArchiver huffmanArchiver;
    int32_t rawDataSize, compressDataSize, extraDataSize;
    if (target == "compress") {
        std::ifstream in(inputFile);
        std::ofstream out(outputFile, std::ios::binary);
        std::tie(rawDataSize, compressDataSize, extraDataSize) = huffmanArchiver.compress(in, out);
    } else {
        std::ifstream in(inputFile, std::ios::binary);
        std::ofstream out(outputFile);
        std::tie(rawDataSize, compressDataSize, extraDataSize) = huffmanArchiver.extract(in, out);
    }
    cli.sendStatistic(rawDataSize, compressDataSize, extraDataSize);
}
