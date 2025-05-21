#include <iostream>
#include "HuffmanTree.h"
#include "frequency_counter.h"  // Need to include for debug
#include "MinHeap.h"          // Need to include for debug

void printCode(char ch, const std::string& code) {
    std::cout << "'";
    if (ch == '\n') std::cout << "\\n";
    else if (ch == '\t') std::cout << "\\t";
    else if (ch == ' ') std::cout << " ";
    else if (ch < 32 || ch > 126) std::cout << "0x" << std::hex << (int)ch << std::dec;
    else std::cout << ch;
    std::cout << "' : " << code << "\n";
}

int main() {
    const char* filename = "C:/Users/Hp/Documents/GitHub/File-zipper/sample.txt";

    // --- DEBUG CODE START ---
    FrequencyCounter counter;
    counter.count(filename);
    MinHeap heap;

    // Build heap for debug check
    const CharFrequency* freqs = counter.getFrequencies();
    for (int i = 0; i < 256; ++i) {
        if (freqs[i].frequency > 0) {
            heap.insert(new HuffmanNode(freqs[i].character, freqs[i].frequency));
        }
    }

    if (counter.getUniqueCount() == 1) {
        std::cout << "DEBUG: Single character detected\n";
        HuffmanNode* node = heap.extractMin();
        std::cout << "Node char: '" << node->data
                  << "' freq: " << node->freq << "\n";
        delete node;  // Clean up
    }
    // --- DEBUG CODE END ---

    // Original main logic
    HuffmanTree huffmanTree(filename);
    const std::string* codeMap = huffmanTree.getCodeMap();

    std::cout << "Huffman Codes:\n";
    for (int i = 0; i < 256; ++i) {
        if (!codeMap[i].empty()) {
            printCode(static_cast<char>(i), codeMap[i]);
        }
    }
    return 0;
}