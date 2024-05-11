#ifndef SEARCH_LIB_BST_H
#define SEARCH_LIB_BST_H

#include <iostream>
#include <fstream>
using namespace std;

typedef long int dtype;

struct Node {
    dtype data;
    int index;
    Node* prev;
    Node* left;
    Node* right;
};

struct StackNode {
    Node* data;
    StackNode* next;
};

struct Stack {
    StackNode* top;
};

Node* createTree();
void printTree(Node* root);
Node* addNode(Node* root, dtype data, int index);
Node* getData(const string& filename);
void saveData(const string& filename, Node* root);
int getFirstOccurrence(dtype element, Node* root);
int getLastOccurrence(dtype element, Node* root);
void getAllOccurrences(dtype element, Node* root, int*& occurrences, int* numOccurrences);
bool validateTree(Node* root);

Stack* createStack();
void push(Stack* stack, Node* data);
Node* pop(Stack* stack);
bool isEmptyStack(Stack* stack);

#endif
