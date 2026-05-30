// Copyright 2021 NNTU-CS
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "bst.h"

bool isLatin(char ch);
char toLower(char ch);

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream fileIn(filename);  // используем filename, а не source
    if (!fileIn.is_open()) {
        std::cerr << "Cannot open file" << std::endl;
        return;
    }
    std::string wordBuffer;
    char currentCh;
    while (fileIn.get(currentCh)) {
        if (isLatin(currentCh)) {
            wordBuffer.push_back(toLower(currentCh));
        } else {
            if (!wordBuffer.empty()) {
                tree.insert(wordBuffer);
                wordBuffer.clear();
            }
        }
    }
    if (!wordBuffer.empty()) {
        tree.insert(wordBuffer);
    }
    fileIn.close();
}

bool compareByFreq(const std::pair<std::string, int>& a,
    const std::pair<std::string, int>& b) {
    return a.second > b.second;
}

void printFreq(BST<std::string>& voc) {
    std::vector<std::pair<std::string, int>> items;
    voc.collectInfo(items);
    std::sort(items.begin(), items.end(), compareByFreq);
    std::ofstream outFile("result/freq.txt");
    for (const auto& entry : items) {
        std::cout << entry.first << " - " << entry.second << std::endl;
        if (outFile.is_open()) {
            outFile << entry.first << " - " << entry.second << std::endl;
        }
    }
    outFile.close();
}

bool isLatin(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

char toLower(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return ch + ('a' - 'A');
    }
    return ch;
}
