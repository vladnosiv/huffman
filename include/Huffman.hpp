#pragma once

#include <unordered_map>
#include <optional>
#include <vector>
#include <random>

class HuffmanTree {
private:
    struct HuffmanNode_;
    typedef HuffmanNode_* HuffmanNode;

    struct HuffmanNode_ {
        HuffmanNode left = nullptr;
        HuffmanNode right = nullptr;

        bool isTerminal = false;
        unsigned char termByte = 0;

        HuffmanNode_() = default;
        HuffmanNode_(unsigned char termByte_) : isTerminal(true), termByte(termByte_) {}
        HuffmanNode_(HuffmanNode left_, HuffmanNode right_) : left(left_), right(right_) {}
    };

    std::pair<HuffmanNode, std::optional<unsigned char>> move(HuffmanNode node, bool nextBit);
    bool findByte(HuffmanNode node, std::vector<bool>& code, unsigned char target);

    void garbageCollector(HuffmanNode node);

    HuffmanNode root = nullptr;
    HuffmanNode walkerState = nullptr;

    void printCodes(HuffmanNode node, std::vector<bool>& code); //debug

    // To speed up code search
    std::random_device rd;
    std::mt19937 gen;

public:
    HuffmanTree() = default;
    void construct(const std::unordered_map<unsigned char, int32_t>& frequencyTable);

    void walkerInit();
    std::optional<unsigned char> walkerMove(bool nextBit);

    std::vector<bool> getCode(unsigned char currentByte);

    void print(); //debug

    void clear();

    ~HuffmanTree();
};
