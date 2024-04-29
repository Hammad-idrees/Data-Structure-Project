#pragma once

// Required libraries 
#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
using namespace std;

// Define the structure for doubly linked list
struct Node
{
	long int data;
	long int index;
	Node* left;
	Node* right;
};
typedef struct Stack
{
	int top;
	Node* head;
}Stack;

// Required Function headers
Node* createTree();
void printTree(Node* root);
Node* addNode(Node* root, long int data, long int index);
Node* getData(const string& filename);
void saveData(const string& filename, Node* root);
long int getFirstOccurrence(long int element, Node* root);
long int getLastOccurrence(long int element, Node* root);
void getAllOccurrences(long int element, Node* root, long int* occurrences, int& numOccurrences);
void saveData(const string& filename, Node* root);
bool validateTree(Node* root);
Stack* createStack();
void push(Stack* stack, Node* node);
Node* pop(Stack* stack);
bool isEmpty(Stack* stack);
/*

Supporting function header
void saveData(const string& filename, Node* root);

*/
