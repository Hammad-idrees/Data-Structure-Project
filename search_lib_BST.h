#ifndef SEARCH_LIB_BST_H
#define SEARCH_LIB_BST_H

#include <iostream>
#include <fstream>

typedef long int dtype;

// Struct for tree node
struct Node {
    dtype data;
    int index;
    Node* left;
    Node* right;
};

// Struct for stack node
struct StackNode {
    Node* data;
    StackNode* next;
};

// Struct for stack
struct Stack {
    StackNode* top;
};

// Function prototypes
Node* createTree();
void printTree(Node* root);
Node* addNode(Node* root, dtype data, int index);
Node* getData(const std::string& filename);
void saveData(const std::string& filename, Node* root);
int getFirstOccurrence(dtype element, Node* root);
int getLastOccurrence(dtype element, Node* root);
void getAllOccurrences(dtype element, Node* root, int*& occurrences, int* numOccurrences);
bool validateTree(Node* root);

// Stack utility functions
Stack* createStack();
void push(Stack* stack, Node* data);
Node* pop(Stack* stack);
bool isEmptyStack(Stack* stack);

#endif
