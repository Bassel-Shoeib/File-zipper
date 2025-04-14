//
// Created by Bassel on 4/1/2025.
//

#ifndef HUFFMANNODE_H
#define HUFFMANNODE_H

class HuffmanNode {
public:
    char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;


    HuffmanNode(char data, int freq);

    HuffmanNode(int freq, HuffmanNode* left, HuffmanNode* right);

    bool isLeaf() const;
};

#endif // HUFFMANNODE_H