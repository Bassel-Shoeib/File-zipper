cmake_minimum_required(VERSION 3.30)
project(untitled)

set(CMAKE_CXX_STANDARD 23)

add_executable(untitled main.cpp
        HuffmanNode.cpp
        HuffmanNode.h
        MinHeap.cpp
        MinHeap.h
        frequency_counter.cpp
        frequency_counter.h
        HuffmanTree.cpp
        HuffmanTree.h)
