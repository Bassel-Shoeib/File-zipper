#ifndef FREQUENCY_COUNTER_H
#define FREQUENCY_COUNTER_H

struct CharFrequency {
    unsigned char character;
    int frequency;
};

class FrequencyCounter {
private:
    static const int TABLE_SIZE = 256;
    CharFrequency freqTable[TABLE_SIZE];
    int uniqueCount;

public:
    FrequencyCounter();
    void count(const char* filename);
    const CharFrequency* getFrequencies() const;
    int getUniqueCount() const;
};

#endif // FREQUENCY_COUNTER_H
