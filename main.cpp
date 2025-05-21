#include "HuffmanTree.h"
#include <iostream>
#include <string>

int main() {
    char choice;
    std::cout << "Choose operation (c for compress, d for decompress): ";
    std::cin >> choice;

    try {
        if (choice == 'c' || choice == 'C') {
            HuffmanTree tree("C:/Users/AUC/CLionProjects/file_zipper/original.txt");
            tree.compress("C:/Users/AUC/CLionProjects/file_zipper/original.txt",
                         "C:/Users/AUC/CLionProjects/file_zipper/compressed.huf");
            std::cout << "File compressed successfully!" << std::endl;
        }
        else if (choice == 'd' || choice == 'D') {
            HuffmanTree::decompress("C:/Users/AUC/CLionProjects/file_zipper/compressed.huf",
                                   "C:/Users/AUC/CLionProjects/file_zipper/decompressed.txt");
            std::cout << "File decompressed successfully!" << std::endl;
        }
        else {
            std::cout << "Invalid choice. Please enter 'c' for compress or 'd' for decompress." << std::endl;
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}