#include "search_lib_BST.h"
#include <iostream>
#include <fstream>
#include <limits>
using namespace std;

const int MAX_OCCURRENCES = 100;
bool validateTreeHelper(Node* root, dtype minValue, dtype maxValue);

Node* createTree() {
    return nullptr;
}

void printTree(Node* root) {
    if (root != nullptr) {
        cout << root->data << " ";
        printTree(root->left);
        printTree(root->right);
    }
}

Node* addNode(Node* root, dtype data, int index) {
    if (root == nullptr) {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->index = index;
        newNode->left = newNode->right = nullptr;
        return newNode;
    }

    if (data < root->data) {
        root->left = addNode(root->left, data, index);
    }
    else {
        root->right = addNode(root->right, data, index);
    }

    return root;
}

Node* getData(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return nullptr;
    }

    Node* root = createTree();
    dtype value;
    int index = 0;
    while (file >> value) {
        root = addNode(root, value, index++);
    }

    file.close();
    return root;
}

void saveData(const string& filename, Node* root) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    file.close();
}

int getFirstOccurrence(dtype element, Node* root) {
    if (root == nullptr) {
        return -1;
    }

    if (root->data == element) {
        return root->index;
    }

    int leftResult = getFirstOccurrence(element, root->left);
    if (leftResult != -1) {
        return leftResult;
    }

    return getFirstOccurrence(element, root->right);
}

int getLastOccurrence(dtype element, Node* root) {
    if (root == nullptr) {
        return -1;
    }

    if (root->data == element) {
        return root->index;
    }

    int rightResult = getLastOccurrence(element, root->right);
    if (rightResult != -1) {
        return rightResult;
    }

    return getLastOccurrence(element, root->left);
}

void getAllOccurrences(dtype element, Node* root, int*& occurrences, int* numOccurrences) {
    if (root == nullptr) {
        *numOccurrences = 0;
        return;
    }

    if (root->data == element) {
        occurrences[*numOccurrences] = root->index;
        (*numOccurrences)++;
        cout << "Found occurrence of " << element << " at index " << root->index << endl;
    }

    getAllOccurrences(element, root->left, occurrences, numOccurrences);
    getAllOccurrences(element, root->right, occurrences, numOccurrences);
}


bool validateTree(Node* root) {
    return validateTreeHelper(root, numeric_limits<dtype>::min(), numeric_limits<dtype>::max());
}

bool validateTreeHelper(Node* root, dtype minValue, dtype maxValue) {
    if (root == nullptr) {
        return true;
    }

    if (root->data < minValue || root->data > maxValue) {
        return false;
    }

    return validateTreeHelper(root->left, minValue, root->data - 1) &&
        validateTreeHelper(root->right, root->data + 1, maxValue);
}

Stack* createStack() {
    Stack* stack = new Stack;
    stack->top = nullptr;
    return stack;
}

void push(Stack* stack, Node* data) {
    StackNode* newNode = new StackNode;
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

Node* pop(Stack* stack) {
    if (isEmptyStack(stack)) {
        return nullptr;
    }

    StackNode* temp = stack->top;
    Node* data = temp->data;
    stack->top = temp->next;
    delete temp;
    return data;
}

bool isEmptyStack(Stack* stack) {
    return stack->top == nullptr;
}

int main() {
    string inputFilename = "input.csv";
    Node* root = getData(inputFilename);

    if (root != nullptr) {
        bool isBST = validateTree(root);
        if (isBST) {
            cout << "The data was created as a Binary Search Tree." << endl;
        }
        else {
            cout << "The data was not created as a Binary Search Tree." << endl;
        }

        long int valuesToSearch[] = { 232, 649, 989, 1447, 1909 };
        int numValues = sizeof(valuesToSearch) / sizeof(valuesToSearch[0]);

        for (int i = 0; i < numValues; ++i) {
            long int value = valuesToSearch[i];
            int firstOccurrence = getFirstOccurrence(value, root);
            int lastOccurrence = getLastOccurrence(value, root);

            int* occurrences = new int[MAX_OCCURRENCES];
            int numOccurrences = 0;
            getAllOccurrences(value, root, occurrences, &numOccurrences);

            cout << "Value: " << value << endl;
            cout << "First Occurrence Index: " << firstOccurrence << endl;
            cout << "Last Occurrence Index: " << lastOccurrence << endl;
            cout << "All Occurrences: ";
            for (int j = 0; j < numOccurrences; ++j) {
                cout << occurrences[j] << " ";
            }
            cout << endl;

            delete[] occurrences;
        }
    }

    return 0;
}
