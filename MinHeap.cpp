#include "MinHeap.h"

MinHeap::MinHeap() : capacity(10), currentSize(0) {
    heapArray = new HuffmanNode*[capacity];
}

MinHeap::~MinHeap() {
    delete[] heapArray;
}

void MinHeap::swapNodes(int i, int j) {
    HuffmanNode* temp = heapArray[i];
    heapArray[i] = heapArray[j];
    heapArray[j] = temp;
}

void MinHeap::resize(int newCapacity) {
    HuffmanNode** newHeap = new HuffmanNode*[newCapacity];
    for (int i = 0; i < currentSize; ++i) {
        newHeap[i] = heapArray[i];
    }
    delete[] heapArray;
    heapArray = newHeap;
    capacity = newCapacity;
}

void MinHeap::insert(HuffmanNode* node) {
    if (currentSize == capacity) {
        resize(capacity * 2);
    }

    heapArray[currentSize] = node;
    heapifyUp(currentSize);
    currentSize++;
}

HuffmanNode* MinHeap::extractMin() {
    if (currentSize == 0) return nullptr;

    HuffmanNode* minNode = heapArray[0];
    heapArray[0] = heapArray[currentSize - 1];
    currentSize--;

    if (currentSize < capacity / 4 && capacity > 10) {
        resize(capacity / 2);
    }

    heapifyDown(0);
    return minNode;
}

void MinHeap::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heapArray[parent]->freq <= heapArray[index]->freq) break;
        swapNodes(parent, index);
        index = parent;
    }
}

void MinHeap::heapifyDown(int index) {
    while (true) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < currentSize && heapArray[left]->freq < heapArray[smallest]->freq) {
            smallest = left;
        }
        if (right < currentSize && heapArray[right]->freq < heapArray[smallest]->freq) {
            smallest = right;
        }
        if (smallest == index) break;

        swapNodes(index, smallest);
        index = smallest;
    }
}

int MinHeap::size() const {
    return currentSize;
}

bool MinHeap::empty() const {
    return currentSize == 0;
}