#ifndef BITIO_H
#define BITIO_H

#include <fstream>
#include <string>

class BitWriter {
private:
    std::ofstream out;
    unsigned char buffer;
    int bitCount;

public:
    BitWriter(const std::string &filename);
    void writeBit(bool bit);
    void writeByte(char byte);
    void flush();
    ~BitWriter();
};

class BitReader {
private:
    std::ifstream in;
    unsigned char buffer;
    int bitCount;

public:
    BitReader(const std::string &filename);
    bool readBit();
    char readByte();
    ~BitReader();
};

#endif
