#pragma once

#include <iostream>
#include <cstring>
#include<string>
#include<queue>
#include<vector>

using namespace std;


typedef struct {
    char name[50];
    int index;
} City;


typedef struct node {
    int city;
    struct node* next;

}Node;


class Graph {
private:
    int numberOfCities;
    Node** adjList;
    int** distances;

public:
    void insert_edge(Node* adj_list[], int src, int dest);
    void print_path(int parent[], int src, int dest, City cities[]);
    void bfs(Node* adj_list[], int src, int dest, City cities[], int n);
    int hash(char* c1, char* c2);
    int find_distance(double distances[], char* city1, char* city2);
    void add_distance(double distances[], char* city1, char* city2, double distance);
};



void Graph::insert_edge(Node* adj_list[], int src, int dest) {

    Node* newNode = new Node;
    newNode->city = dest;
    newNode->next = adj_list[src];
    adj_list[src] = newNode;
}


void Graph::print_path(int parent[], int src, int dest, City cities[]) 
{
    if (parent[dest] == -1) {
        cout << "No path exists from " << cities[src].name << " to " << cities[dest].name << endl;
        return;
    }

    const int maxlength = 10;
    int path[maxlength];
    int path_index = 0;

    int current = dest;
    while (current != -1 && path_index < maxlength) {
        path[path_index++] = current;
        if (current == src) break;
        current = parent[current];
    }

    cout << "Path from " << cities[src].name << " to " << cities[dest].name << ": ";
    for (int i = path_index - 1; i >= 0; i--) {
        cout << cities[path[i]].name;
        if (i > 0) cout << " -> ";
    }
    cout << endl;

}

void Graph::bfs(Node* adj_list[], int src, int dest, City cities[], int n) {
    
    bool* visited = new bool[n];
    int* parent = new int[n];
    for (int i = 0; i < n; ++i) {
        visited[i] = false; // Initialize all nodes as unvisited
        parent[i] = -1; // Initialize all parents as -1 (no parent)
    }

    // Create a queue for BFS
    queue<int> q;

    // Mark the current node as visited and enqueue it
    visited[src] = true;
    q.push(src);

    while (!q.empty()) {
        // Dequeue a vertex from the queue
        int u = q.front();
        q.pop();

        // Get all adjacent vertices of the dequeued vertex u
        // If an adjacent has not been visited, then mark it
        // visited and enqueue it
        Node* temp = adj_list[u];
        while (temp != nullptr) {
            int v = temp->city;
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u; // Set parent of v as u
                q.push(v);
            }
            temp = temp->next; // iterate to the next city 
        }
    }

    // If the destination node is found
    if (visited[dest]) 
    {
        cout << "Path is found: " << endl;
        print_path(parent, src, dest, cities);
    }
    else 
    {
        cout << "No path exists from " << cities[src].name << " to " << cities[dest].name << endl;
    }

    // Free dynamically allocated memory
    delete[] visited;
    delete[] parent;
}
int Graph::hash(char* c1, char* c2)
{
    const int maxLength = 100;
    char key[maxLength];

    // Concatenate the names of the two cities
    strcpy_s(key, c1);
    strcat_s(key, c2);

    // Calculate the hash value
    int hashValue = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        hashValue += key[i];
    }

    // Return the hash value
    return hashValue % maxLength;
}
int Graph::find_distance(double distances[], char* city1, char* city2) {
    // Calculate hash key
    int key = hash(city1, city2);

    // Check if the key is within the valid range
    if (key < 0 || key >= numberOfCities * numberOfCities) {
        // Key out of range, return -1 to indicate distance not found
        return -1;
    }

    // Retrieve the distance corresponding to the calculated key
    double distance = distances[key];

    // Check if the distance is valid
    if (distance < 0) {
        // Invalid distance, return -1 to indicate distance not found
        return -1;
    }

    // Return the retrieved distance
    return distance;
}
