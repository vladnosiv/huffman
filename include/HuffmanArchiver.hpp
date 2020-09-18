#pragma once

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <tuple>

#include "Huffman.hpp"

class HuffmanArchiver {
private:

    void decodeData(std::istream& in, std::ostream& out);

    void readData(std::istream& in); // First pass
    void encodeData(std::istream& in, std::ostream& out); // Second pass

    void readFrequencyTable(std::istream& in);
    void writeFrequenctTable(std::ostream& out);

    void countSizeOfData();

    std::unordered_map<unsigned char, int32_t> frequencyTable;
    HuffmanTree huffmanTree;
    int32_t sizeOfData, rawDataSize, compressDataSize, extraDataSize;

public:

    HuffmanArchiver() = default;

    std::tuple<int, int, int> compress(std::istream& in, std::ostream& out);

    std::tuple<int, int, int> extract(std::istream& in, std::ostream& out);

};
