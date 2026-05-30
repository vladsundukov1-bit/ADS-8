// Copyright 2021 NNTU-CS
#include "bst.h"
#include <string>

void makeTree(BST<std::string>&, const char*);
void printFreq(BST<std::string>&);

int main() {
    BST<std::string> dictionary;
    makeTree(dictionary, "src/war_peace.txt");
    printFreq(dictionary);
    return 0;
}
