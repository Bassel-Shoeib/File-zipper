#include "HuffmanNode.h"
HuffmanNode::HuffmanNode(char data, int freq)
    : data(data), freq(freq), left(nullptr), right(nullptr) {}

HuffmanNode::HuffmanNode(int freq, HuffmanNode* left, HuffmanNode* right)
    : data('\0'), freq(freq), left(left), right(right) {}

bool HuffmanNode::isLeaf() const {
    return !left && !right;
}