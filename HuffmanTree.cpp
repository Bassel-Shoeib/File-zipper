//
// Created by Bassel on 4/1/2025.
//

#include "HuffmanTree.h"
#include<string>
void HuffmanTree::buildCodeMap(HuffmanNode* node, std::string code) {
    if (node == nullptr) return;

    if (node->isLeaf() && code.empty()) {
        codeMap[static_cast<unsigned char>(node->data)] = "0";
        return;
    }

    if (node->isLeaf()) {
        codeMap[static_cast<unsigned char>(node->data)] = code;
        return;
    }
    buildCodeMap(node->left, code + "0");
    buildCodeMap(node->right, code + "1");
}

void HuffmanTree::deleteTree(HuffmanNode* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

HuffmanTree::HuffmanTree(const char* filename) : root(nullptr) {
    FrequencyCounter counter;
    counter.count(filename);
    if (counter.getUniqueCount() == 1) {
        for (int i = 0; i < 256; ++i) {
            if (counter.getFrequencies()[i].frequency > 0) {
                root = new HuffmanNode(counter.getFrequencies()[i].character,
                                      counter.getFrequencies()[i].frequency);
                codeMap[i] = "0";
                return;
            }
        }
    }
    MinHeap heap;
    const CharFrequency* freqs = counter.getFrequencies();

    for (int i = 0; i < 256; ++i) {
        if (freqs[i].frequency > 0) {
            heap.insert(new HuffmanNode(freqs[i].character, freqs[i].frequency));
        }
    }

    while (heap.size() > 1) {
        HuffmanNode* left = heap.extractMin();
        HuffmanNode* right = heap.extractMin();
        heap.insert(new HuffmanNode(left->freq + right->freq, left, right));
    }

    root = heap.extractMin();
    buildCodeMap(root, "");
}

HuffmanTree::~HuffmanTree() {
    deleteTree(root);
}

const std::string* HuffmanTree::getCodeMap() const {
    return codeMap;
}