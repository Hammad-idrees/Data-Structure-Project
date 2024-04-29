// Import all the function of header file search_lib_BST.h here
#include "search_lib_BST.h"

// Function for empty tree
Node* createTree()
{
	return nullptr;
}
// Function to print tree elements by preorder traversal
void printTree(Node* root)
{
	if (root == nullptr)
	{
		return;
	}

	cout << root->data << " ";// Print the root element
	// Recursive call for left and right subtree
	printTree(root->left);
	printTree(root->right);
}	
// Function for adding the node in the binary search tree
Node* addNode(Node* root, long int data, long int index)
{
	if (root == nullptr) // check if the tree has not node already
	{
		Node* temp = new Node;
		temp->data = data;
		temp->index = index;
		temp->left = nullptr;
		temp->right = nullptr;
		return temp;
	}
	// Implement the conditions for the binary search tree insertion like 
	// the smaller elements in the left and greater elements in the right 
	if (data <= root->data)
	{
		root->left = addNode(root->left, data, index);
	}
	else
	{
		root->right = addNode(root->right, data, index);
	}
	return root;
}
// Function for import the data from the csv file from the pc
Node* getData(const string& filename) {
	// Construct complete file path
	string filePath = "C:/Users/HP/OneDrive/Documents/Project/" + filename;

	// Open the file for reading
	ifstream file(filePath);
	if (!file.is_open()) {
		cerr << "Error: Unable to open file " << filePath << endl;
		return nullptr;
	}

	// Data variables
	Node* root = nullptr;
	long int data;
	long int index = 0;
	string line;

	// Read lines and process data
	while (getline(file, line)) {
		// Extract integer with error handling
		try 
		{
			data = stol(line); // Convert string to long int
		}
		catch (const exception& e) {
			cerr << "Error: Invalid data format in line " << index + 1 << " of file " << filePath << endl;
			continue; // Skip to the next line in case of error
		}

		// Add node to the data structure (replace with your specific logic)
		root = addNode(root, data, index);
		index++;
	}

	// Close the file
	file.close();

	return root;
}
// Helper function for preorder traversal and saving data to file
void savePreorder(ofstream& file, Node* node)
{
	if (node == nullptr)
		return;

	file << node->data << endl; // Save data to file
	savePreorder(file, node->left);
	savePreorder(file, node->right);

	// <Time Complexity> O(n) 
	// It depends upn the number of the nodes in the binary search tree so it visits every node in the binary search tree.
}
// Function to save tree data to a CSV file in preorder traversal
void saveData(const string& filename, Node* root) 
{
	string filePath = "C:/Users/HP/OneDrive/Documents/Project/" + filename; // Construct complete file path

	// Open the file for writing
	ofstream file(filePath);
	if (!file.is_open()) {
		cerr << "Error: Unable to open file " << filePath << endl;
		return;
	}

	// Perform preorder traversal and save data to file
	savePreorder(file, root);

	// Close the file
	file.close();
}
//Function to find the index of the first occurence 
long int getFirstOccurrence(long int element, Node* root)
{
	if (root == nullptr)
	{
		return -1;
	}
	if (element == root->data)
		return root->index;
	else if (element < root->data)
		return getFirstOccurrence(element, root->left);
	else
		return getFirstOccurrence(element, root->right);
}
// Function to find the index of the last occurence of an element in the BST
long int getLastOccurrence(long int element, Node* root)
{
	if (root == nullptr)
	{
		return -1;
	}
	long int index = -1;
	if (element == root->data)
		index = root->index;
	// Check in the left subtree for the last occurence
	if (element <= root->data)
		return getLastOccurrence(element, root->left);
	else
		return getLastOccurrence(element, root->right);

	return index;
}	
// Function to find all the location of the BST
void getAllOccurrences(long int element, Node* root, long int* occurrences, int& numOccurrences)
{
	if (root == nullptr)
		return;

	if (element == root->data) {
		occurrences[numOccurrences++] = root->index;
		getAllOccurrences(element, root->left, occurrences, numOccurrences);
	}
	else if (element < root->data) {
		getAllOccurrences(element, root->left, occurrences, numOccurrences);
	}
	else {
		getAllOccurrences(element, root->right, occurrences, numOccurrences);
	}
}
// Function to validate if the tree is a BST
bool validateTree(Node* root)
{
	if (root == nullptr)
	{
		return true;
	}
	Stack* stack = createStack();
	Node* current = root;
	Node* prev = nullptr;

	while (current != nullptr || isEmpty(stack))
	{
		while (current != nullptr)
		{
			push(stack, current);
			current = current->left;
		}
		current = pop(stack);
		if (prev != nullptr && current->data <= prev->data)
			return false;

		prev = current;
		current = current->right;
	}
	return true;
}

// Function to create an empty stack
Stack* createStack()
{
	Stack* stack = new Stack;
	stack->top = -1;
	stack->head = nullptr;
	return stack;
}
void push(Stack* stack, Node* node)
{
	if (stack == nullptr)
		return;
	node->right = stack->head;
	stack->head = node;
	stack->top++;
}

// Function to pop/remove a node from the stack
Node* pop(Stack* stack)
{
	if (stack == nullptr || isEmpty(stack))
		return nullptr;
	
	Node* pop = stack->head;
	stack->head = pop->right;
	stack->top--;
	pop->right = nullptr;
	return pop;
}

// Function to check if the stack is empty or not
bool isEmpty(Stack* stack)
{
	return stack == nullptr || stack->top == -1;
}



// main function for implementation
int main()
{

}