#ifndef MINHEAP_H
#define MINHEAP_H

#include "HuffmanNode.h"

class MinHeap {
private:
    HuffmanNode** heapArray;
    int capacity;
    int currentSize;

    void resize(int newCapacity);
    void heapifyUp(int index);
    void heapifyDown(int index);
    void swapNodes(int i, int j);

public:
    MinHeap();
    ~MinHeap();
    void insert(HuffmanNode* node);
    HuffmanNode* extractMin();
    int size() const;
    bool empty() const;
};

#endif // MINHEAP_H