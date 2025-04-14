//
// Created by Bassel on 4/1/2025.
//

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include "MinHeap.h"
#include "frequency_counter.h"
#include <fstream>
#include<string>

class HuffmanTree {
private:
    HuffmanNode* root;
    std::string codeMap[256];

    void buildCodeMap(HuffmanNode* node, std::string code);
    void deleteTree(HuffmanNode* node);

public:
    HuffmanTree(const char* filename);
    ~HuffmanTree();
    const std::string* getCodeMap() const;
};

#endif //HUFFMANTREE_H
