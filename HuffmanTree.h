#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "MinHeap.h"
#include "bitIO.h"
#include "frequency_counter.h"
#include <fstream>
#include <string>
#include <cstdint>

class HuffmanTree {
private:
    HuffmanNode* root;
    std::string codeMap[256];

    void buildCodeMap(HuffmanNode* node, std::string code);
    void deleteTree(HuffmanNode* node);
    void serializeTree(BitWriter& writer);
    HuffmanNode* deserializeTree(BitReader& reader);
    void writeHeader(BitWriter& writer, uint32_t originalSize);
    uint32_t readHeader(BitReader& reader);

public:
    HuffmanTree();
    HuffmanTree(const char* filename);
    ~HuffmanTree();

    void compress(const std::string& inputFile, const std::string& outputFile);
    static void decompress(const std::string& inputFile, const std::string& outputFile);
    const std::string* getCodeMap() const;
};

#endif // HUFFMANTREE_H
