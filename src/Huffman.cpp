#include <unordered_map>
#include <optional>
#include <vector>
#include <tuple>
#include <cassert>
#include <algorithm>
#include <random>
#include <set>

#include <iostream> //debug

#include "Huffman.hpp"

void HuffmanTree::construct(const std::unordered_map<unsigned char, int32_t>& frequencyTable) {
    gen = std::mt19937(rd());

    auto cmp = [](const std::pair<int32_t, HuffmanNode>& a, const std::pair<int32_t, HuffmanNode>& b) {
        return a.first < b.first;
    };

    std::vector<std::pair<unsigned char, int32_t>> table;
    for (auto& [currentByte, weight] : frequencyTable) {
        table.push_back({currentByte, weight});
    }
    std::sort(table.begin(), table.end());

    std::multiset<std::pair<int32_t, HuffmanNode>, decltype(cmp)> nodes(cmp);
    for (auto& [currentByte, weight] : table) {
        nodes.insert({weight, new HuffmanNode_(currentByte)});
    }

    if (nodes.size() == 1u) {
        walkerState = root = new HuffmanNode_(nullptr, nodes.begin()->second);
        return;
    }

    HuffmanNode leftNode, rightNode;
    int32_t leftNodeWeight, rightNodeWeight;
    while (nodes.size() > 1u) {
        std::tie(leftNodeWeight, leftNode) = *nodes.begin();
        nodes.erase(nodes.begin());
        std::tie(rightNodeWeight, rightNode) = *nodes.begin();
        nodes.erase(nodes.begin());
        nodes.insert({leftNodeWeight + rightNodeWeight, new HuffmanNode_(leftNode, rightNode)});
    }
    walkerState = root = (*nodes.begin()).second;
}

void HuffmanTree::walkerInit() {
    walkerState = root;
}

std::optional<unsigned char> HuffmanTree::walkerMove(bool nextBit) {
    std::optional<unsigned char> result;
    std::tie(walkerState, result) = move(walkerState, nextBit);
    return result;
}

std::vector<bool> HuffmanTree::getCode(unsigned char currentByte) {
    std::vector<bool> result;
    assert(findByte(root, result, currentByte));
    std::reverse(result.begin(), result.end());
    return result;
}

void HuffmanTree::clear() {
    garbageCollector(root);
    root->left = root->right = nullptr;
}

HuffmanTree::~HuffmanTree() {
    clear();
    delete root;
}

auto HuffmanTree::move(HuffmanNode node, bool nextBit) -> std::pair<HuffmanNode, std::optional<unsigned char>> {
    node = nextBit ? node->right : node->left;
    assert(node != nullptr);
    if (node->isTerminal) {
        return {root, {node->termByte}};
    }
    return {node, {}};
}

bool HuffmanTree::findByte(HuffmanNode node, std::vector<bool>& code, unsigned char target) {
    if (node == nullptr) {
        return false;
    }
    if (node->isTerminal && node->termByte == target) {
        return true;
    }
    HuffmanNode firstNode = node->left, secondNode = node->right;
    if (gen() % 2) { // Theoretically speeds up the search
        std::swap(firstNode, secondNode);
    }
    bool result = false;
    if (findByte(firstNode, code, target)) {
        code.push_back(firstNode == node->right);
        result = true;
    } else if (findByte(secondNode, code, target)) {
        code.push_back(secondNode == node->right);
        result = true;
    }
    return result;
}

void HuffmanTree::printCodes(HuffmanNode node, std::vector<bool>& code) {
    if (node == nullptr) {
        return;
    }
    if (node->isTerminal) {
        std::cerr << ((node->termByte == 10) ? '~' : (char)node->termByte) << ' ';
        for (auto b : code)
            std::cerr << b;
        std::cerr << std::endl;
    }
    code.push_back(0);
    printCodes(node->left, code);
    code.back() = 1;
    printCodes(node->right, code);
    code.pop_back();
}

void HuffmanTree::print() {
    std::vector<bool> code;
    printCodes(root, code);
}

void HuffmanTree::garbageCollector(HuffmanNode node) {
    if (node == nullptr) {
        return;
    }
    garbageCollector(node->left);
    garbageCollector(node->right);
    if (node != root) {
        delete node;
    }
}
