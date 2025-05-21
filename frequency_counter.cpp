#include "frequency_counter.h"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <cstring>

FrequencyCounter::FrequencyCounter() {
    std::memset(freqTable, 0, sizeof(freqTable));
    uniqueCount = 0;
}

void FrequencyCounter::count(const char* filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) throw std::runtime_error("Failed to open file for reading: " + std::string(filename));

    unsigned char ch;
    while (in.read(reinterpret_cast<char*>(&ch), 1)) {
        if (freqTable[ch].frequency == 0) {
            uniqueCount++;
        }
        freqTable[ch].character = ch;
        freqTable[ch].frequency++;
    }
}

const CharFrequency* FrequencyCounter::getFrequencies() const {
    return freqTable;
}

int FrequencyCounter::getUniqueCount() const {
    return uniqueCount;
}
