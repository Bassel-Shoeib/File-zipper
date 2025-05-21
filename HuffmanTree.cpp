#include "HuffmanTree.h"
#include <string>
#include <functional>
#include <cstdint>
#include <iostream>
using namespace std;
HuffmanTree::HuffmanTree() : root(nullptr) {}

void HuffmanTree::buildCodeMap(HuffmanNode* node, std::string code) {
    if (!node) return;
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
    const CharFrequency* freqs = counter.getFrequencies();

    if (counter.getUniqueCount() == 1) {
        for (int i = 0; i < 256; ++i) {
            if (freqs[i].frequency > 0) {
                root = new HuffmanNode(freqs[i].character, freqs[i].frequency);
                codeMap[i] = "0";
                return;
            }
        }
    }

    MinHeap heap;
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

void HuffmanTree::serializeTree(BitWriter& writer) {
    std::function<void(HuffmanNode*)> serialize = [&](HuffmanNode* node) {
        if (node->isLeaf()) {
            writer.writeBit(true);
            writer.writeByte(node->data);
        } else {
            writer.writeBit(false);
            serialize(node->left);
            serialize(node->right);
        }
    };
    serialize(root);
}

HuffmanNode* HuffmanTree::deserializeTree(BitReader& reader) {
    if (reader.readBit()) {
        return new HuffmanNode(reader.readByte(), 0);
    }
    HuffmanNode* left = deserializeTree(reader);
    HuffmanNode* right = deserializeTree(reader);
    return new HuffmanNode(0, left, right);
}

void HuffmanTree::writeHeader(BitWriter& writer, uint32_t originalSize) {
    for (int i = 3; i >= 0; --i)
        writer.writeByte((originalSize >> (i * 8)) & 0xFF);
}

uint32_t HuffmanTree::readHeader(BitReader& reader) {
    uint32_t size = 0;
    for (int i = 0; i < 4; ++i) {
        size = (size << 8) | reader.readByte();
    }
    return size;
}

void HuffmanTree::compress(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) throw std::runtime_error("Cannot open input file.");

    in.seekg(0, std::ios::end);
    uint32_t originalSize = static_cast<uint32_t>(in.tellg());
    in.seekg(0, std::ios::beg);

    BitWriter writer(outputFile);
    writeHeader(writer, originalSize);
    serializeTree(writer);

    char ch;
    while (in.get(ch)) {
        const std::string& code = codeMap[static_cast<unsigned char>(ch)];
        if (code.empty()) {
            throw std::runtime_error("No Huffman code for character: " + std::to_string((unsigned char)ch));
        }
        for (char bit : code) {
            writer.writeBit(bit == '1');
        }
        std::cout<< ch<< ":" << code<<endl;
    }

    writer.flush();
}

void HuffmanTree::decompress(const std::string& inputFile, const std::string& outputFile) {
    BitReader reader(inputFile);
    HuffmanTree tree;
    uint32_t outputSize = tree.readHeader(reader);
    tree.root = tree.deserializeTree(reader);

    std::ofstream out(outputFile, std::ios::binary);
    if (!out) throw std::runtime_error("Cannot open output file.");

    if (tree.root && tree.root->isLeaf()) {
        for (uint32_t i = 0; i < outputSize; ++i) {
            out.put(tree.root->data);
        }
        return;
    }

    HuffmanNode* current = tree.root;
    uint32_t written = 0;

    while (written < outputSize) {
        if (!current) throw std::runtime_error("Tree traversal failed.");
        current = reader.readBit() ? current->right : current->left;
        if (current->isLeaf()) {
            out.put(current->data);
            current = tree.root;
            ++written;
        }
    }
}
