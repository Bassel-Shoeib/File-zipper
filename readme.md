# Huffman Coding Compression Tool

## Authors
**Noor Elshahidi**  
**Bassel Shoeib**

## Overview
This project implements a **Huffman coding-based file compressor and decompressor** in C++. Huffman coding is a lossless data compression algorithm that assigns variable-length codes to input characters based on their frequencies. The goal is to reduce file size without losing data.

## Features
- Efficient frequency analysis using a fixed-size table.
- MinHeap-based Huffman tree construction.
- Bit-level compression and decompression.
- Custom serialization/deserialization of the Huffman tree.
- Handles edge cases (e.g., files with a single unique character).
- Written from scratch with no third-party libraries.

## File Structure
- `frequency_counter.h/cpp`: Counts frequency of each byte in a file.
- `HuffmanNode.h/cpp`: Defines the tree node used in Huffman encoding.
- `HuffmanTree.h/cpp`: Builds the Huffman tree, compresses and decompresses files.
- `MinHeap.h/cpp`: Implements a priority queue for tree construction.
- `BitWriter.h/cpp` and `BitReader.h/cpp` *(not shown above)*: Handle bit-level file operations for compression and decompression.

## How It Works
1. **Frequency Count**: Scans the input file to determine frequency of each character.
2. **Tree Construction**: Builds a Huffman tree from character frequencies using a MinHeap.
3. **Encoding Map**: Traverses the tree to generate binary codes for each character.
4. **Compression**:
   - Serializes the Huffman tree.
   - Writes the original file size.
   - Encodes the file using the Huffman codes.
5. **Decompression**:
   - Reads the header and tree from the compressed file.
   - Traverses the tree using bits to reconstruct the original data.

## Usage

### Compilation

Make sure you have a C++ compiler that supports C++11 or later.

```bash
g++ -std=c++11 -o huffman main.cpp *.cpp
