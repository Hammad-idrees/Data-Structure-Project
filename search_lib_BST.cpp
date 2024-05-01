#include "search_lib_BST.h"
#include <iostream>
#include <fstream>
#include <limits> // Include limits header for INT_MIN and INT_MAX

const int MAX_OCCURRENCES = 100; // Define MAX_OCCURRENCES as a constant integer

// Function prototype declaration
bool validateTreeHelper(Node* root, dtype minValue, dtype maxValue);

// Function to create an empty tree
Node* createTree() {
    return nullptr;
}

// Function to print the tree in preorder traversal
void printTree(Node* root) {
    if (root != nullptr) {
        std::cout << root->data << " ";
        printTree(root->left);
        printTree(root->right);
    }
}

// Function to add a new node to the tree
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

// Function to read data from a file and populate the tree
Node* getData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
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

// Function to save tree data to a file
void saveData(const std::string& filename, Node* root) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Write tree data to the file (implementation dependent)

    file.close();
}

// Function to get the index of the first occurrence of an element in the tree
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

// Function to get the index of the last occurrence of an element in the tree
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

// Function to get all occurrences of an element in the tree
void getAllOccurrences(dtype element, Node* root, int*& occurrences, int* numOccurrences) {
    if (root == nullptr) {
        *numOccurrences = 0;
        return;
    }

    if (root->data == element) {
        occurrences[*numOccurrences] = root->index;
        (*numOccurrences)++;
    }

    getAllOccurrences(element, root->left, occurrences, numOccurrences);
    getAllOccurrences(element, root->right, occurrences, numOccurrences);
}

// Function to validate whether the tree is a Binary Search Tree
bool validateTree(Node* root) {
    return validateTreeHelper(root, std::numeric_limits<dtype>::min(), std::numeric_limits    <dtype>::max());
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

// Function to create an empty stack
Stack* createStack() {
    Stack* stack = new Stack;
    stack->top = nullptr;
    return stack;
}

// Function to push a node onto the stack
void push(Stack* stack, Node* data) {
    StackNode* newNode = new StackNode;
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Function to pop a node from the stack
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

// Function to check if the stack is empty
bool isEmptyStack(Stack* stack) {
    return stack->top == nullptr;
}

int main() {
    // Read data from the input file and populate the BST
    std::string inputFilename = "input.csv";
    Node* root = getData(inputFilename);

    if (root != nullptr) {
        // Validate whether the data was created as a BST and print an informative message
        bool isBST = validateTree(root);
        if (isBST) {
            std::cout << "The data was created as a Binary Search Tree." << std::endl;
        }
        else {
            std::cout << "The data was not created as a Binary Search Tree." << std::endl;
        }

        // Demonstrate the functionality of getting the first, last, and all occurrences of specified values
        long int valuesToSearch[] = { 232, 649, 989, 1447, 1909 };
        int numValues = sizeof(valuesToSearch) / sizeof(valuesToSearch[0]);

        for (int i = 0; i < numValues; ++i) {
            long int value = valuesToSearch[i];

            // Get first occurrence
            int firstOccurrence = getFirstOccurrence(value, root);

            // Get last occurrence
            int lastOccurrence = getLastOccurrence(value, root);

            // Get all occurrences
            int* occurrences = new int[MAX_OCCURRENCES];
            int numOccurrences = 0;
            getAllOccurrences(value, root, occurrences, &numOccurrences);

            std::cout << "Value: " << value << std::endl;
            std::cout << "First Occurrence Index: " << firstOccurrence << std::endl;
            std::cout << "Last Occurrence Index: " << lastOccurrence << std::endl;
            std::cout << "All Occurrences: ";
            for (int j = 0; j < numOccurrences; ++j) {
                std::cout << occurrences[j] << " ";
            }
            std::cout << std::endl;

            delete[] occurrences;
        }
    }

    return 0;
}

