#include <sstream>

#include "doctest.h"
#include "HuffmanArchiver.hpp"

TEST_CASE("HuffmanArchiver Different Symbols Test") {
    HuffmanArchiver huffmanArchiver;
    std::string testData = "simple test data with diffe3ent symb0ls\t\n";
    std::stringstream inputCompress, outputBin, inputExtract;
    inputCompress << testData;
    huffmanArchiver.compress(inputCompress, outputBin);
    huffmanArchiver.extract(outputBin, inputExtract);
    CHECK(testData == inputExtract.str());
}

TEST_CASE("HuffmanArchiver Only endls") {
    HuffmanArchiver huffmanArchiver;
    std::string testData = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    std::stringstream inputCompress, outputBin, inputExtract;
    inputCompress << testData;
    huffmanArchiver.compress(inputCompress, outputBin);
    huffmanArchiver.extract(outputBin, inputExtract);
    CHECK(testData == inputExtract.str());
}

TEST_CASE("HuffmanArchiver One type of symbols") {
    HuffmanArchiver huffmanArchiver;
    std::string testData = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    std::stringstream inputCompress, outputBin, inputExtract;
    inputCompress << testData;
    huffmanArchiver.compress(inputCompress, outputBin);
    huffmanArchiver.extract(outputBin, inputExtract);
    CHECK(testData == inputExtract.str());
}
