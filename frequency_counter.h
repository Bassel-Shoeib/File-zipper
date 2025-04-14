//
// Created by Bassel on 4/1/2025.
//

#ifndef FREQUENCY_COUNTER_H
#define FREQUENCY_COUNTER_H
struct CharFrequency {
    char character;
    int frequency;
};

class FrequencyCounter {
private:
    static const int TABLE_SIZE = 256; // ASCII range
    CharFrequency freqTable[TABLE_SIZE];
    int uniqueCount; // Tracks unique characters

public:
    FrequencyCounter();
    void count(const char* filename);
    const CharFrequency* getFrequencies() const;
    int getUniqueCount() const;
};

#endif // FREQUENCYCOUNTER_H
