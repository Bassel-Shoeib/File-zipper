//
// Created by Bassel on 4/1/2025.
//
#include <iostream>
#include "frequency_counter.h"
#include <fstream>

FrequencyCounter::FrequencyCounter() : uniqueCount(0) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        freqTable[i].character = static_cast<char>(i);
        freqTable[i].frequency = 0;
    }
}

void FrequencyCounter::count(const char* filename) {
    std::ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        unsigned char idx = static_cast<unsigned char>(ch);
        freqTable[idx].frequency++;
    }
    file.close();
}

const CharFrequency* FrequencyCounter::getFrequencies() const {
    return freqTable;
}

int FrequencyCounter::getUniqueCount() const {
    return uniqueCount;
}