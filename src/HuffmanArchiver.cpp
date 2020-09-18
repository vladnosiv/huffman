#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <optional>
#include <tuple>

#include "HuffmanArchiver.hpp"
#include "bin_manip.hpp"

void HuffmanArchiver::decodeData(std::istream& in, std::ostream& out) {
    huffmanTree.walkerInit();
    bit_reader reader;
    bool currentBit;
    for (int32_t i = 0; i < sizeOfData; ++i) {
        reader(in, currentBit);
        std::optional<unsigned char> oDecodedByte = huffmanTree.walkerMove(currentBit);
        if (oDecodedByte) {
            out << write_uchar(*oDecodedByte);
            rawDataSize++;
        }
    }
}

void HuffmanArchiver::readData(std::istream& in) {
    unsigned char currentByte;
    while (in >> read_uchar(currentByte)) {
        rawDataSize++;
        frequencyTable[currentByte]++;
    }
}

void HuffmanArchiver::encodeData(std::istream& in, std::ostream& out) {
    unsigned char currentByte;
    bit_writer writer;
    std::unordered_map<unsigned char, std::vector<bool>> codeForByte;
    while (in >> read_uchar(currentByte)) {
        if (codeForByte.find(currentByte) == codeForByte.end()) {
            codeForByte[currentByte] = huffmanTree.getCode(currentByte);
        }
        auto code = codeForByte[currentByte];
        for (bool currentBit : code) {
            writer(out, currentBit);
        }
    }
    writer.flush(out);
}

void HuffmanArchiver::readFrequencyTable(std::istream& in) {
    sizeOfData = 0;
    int32_t sizeOfFrequencyTable;
    in >> read_le_int32(sizeOfFrequencyTable);
    extraDataSize += 4;
    for (int32_t i = 0; i < sizeOfFrequencyTable; ++i) {
        unsigned char currentByte;
        int32_t byteWeight;
        in >> read_uchar(currentByte) >> read_le_int32(byteWeight);
        extraDataSize += 1 + 4;
        frequencyTable[currentByte] = byteWeight;
    }
}

void HuffmanArchiver::writeFrequenctTable(std::ostream& out) {
    int32_t sizeOfFrequencyTable = frequencyTable.size();
    out << write_le_int32(sizeOfFrequencyTable);
    extraDataSize += 4;
    for (auto& [currentByte, byteWeight] : frequencyTable) {
        out << write_uchar(currentByte) << write_le_int32(byteWeight);
        extraDataSize += 1 + 4;
    }
}

void HuffmanArchiver::countSizeOfData() {
    for (auto& [currentByte, weight] : frequencyTable) {
        auto code = huffmanTree.getCode(currentByte);
        sizeOfData += code.size() * weight;
    }
    compressDataSize = sizeOfData;
}

std::tuple<int, int, int> HuffmanArchiver::compress(std::istream& in, std::ostream& out) {
    sizeOfData = rawDataSize = compressDataSize = extraDataSize = 0;
    readData(in);
    huffmanTree.construct(frequencyTable);
    countSizeOfData();
    writeFrequenctTable(out);
    in.clear();
    in.seekg(0, std::ios::beg);
    encodeData(in, out);
    frequencyTable.clear();
    huffmanTree.clear();
    return {rawDataSize, compressDataSize, extraDataSize};
}

std::tuple<int, int, int> HuffmanArchiver::extract(std::istream& in, std::ostream& out) {
    sizeOfData = rawDataSize = compressDataSize = extraDataSize = 0;
    readFrequencyTable(in);
    huffmanTree.construct(frequencyTable);
    countSizeOfData();
    decodeData(in, out);
    frequencyTable.clear();
    huffmanTree.clear();
    return {rawDataSize, compressDataSize, extraDataSize};
}
