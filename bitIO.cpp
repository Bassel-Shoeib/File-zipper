#include "bitIO.h"
#include <stdexcept>

BitWriter::BitWriter(const std::string &filename) : buffer(0), bitCount(0) {
    out.open(filename, std::ios::binary);
    if (!out.is_open()) {
        throw std::runtime_error("Failed to open file for writing: " + filename);
    }
}

void BitWriter::writeBit(bool bit) {
    buffer = (buffer << 1) | bit;
    bitCount++;

    if (bitCount == 8) {
        out.put(static_cast<char>(buffer));
        bitCount = 0;
        buffer = 0;
    }
}

void BitWriter::writeByte(char byte) {
    if (bitCount == 0) {
        out.put(byte);
    } else {
        for (int i = 7; i >= 0; --i) {
            writeBit((byte >> i) & 1);
        }
    }
}

void BitWriter::flush() {
    if (bitCount > 0) {
        buffer <<= (8 - bitCount);
        out.put(static_cast<char>(buffer));
        buffer = 0;
        bitCount = 0;
    }
    out.flush();
}

BitWriter::~BitWriter() {
    flush();
    out.close();
}

BitReader::BitReader(const std::string &filename) : buffer(0), bitCount(0) {
    in.open(filename, std::ios::binary);
    if (!in.is_open()) {
        throw std::runtime_error("Failed to open file for reading: " + filename);
    }
}

bool BitReader::readBit() {
    if (bitCount == 0) {
        int nextChar = in.get();
        if (nextChar == EOF) {
            throw std::runtime_error("Unexpected end of file while reading bits.");
        }
        buffer = static_cast<unsigned char>(nextChar);
        bitCount = 8;
    }

    bool bit = (buffer >> (bitCount - 1)) & 1;
    bitCount--;
    return bit;
}

char BitReader::readByte() {
    char byte = 0;
    for (int i = 0; i < 8; i++) {
        byte = (byte << 1) | readBit();
    }
    return byte;
}

BitReader::~BitReader() {
    in.close();
}