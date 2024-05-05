#pragma once

#include <iostream>
#include <cstring>
#include<string>
#include<queue>


using namespace std;


typedef struct {
    char name[50];
    int index;
} City;


typedef struct node {
    int city;
    struct node* next;
} Node;



class Queue {
public:
    Node* rear;
    Node* front;

    Queue() : rear(nullptr), front(nullptr) {}

   void insert(int city) {
        Node* newnode = new Node; 
        newnode->city = city;     
        newnode->next = nullptr;   

        if (front == nullptr) {
           
            rear = front = newnode;
        }
        else {
           
            rear->next = newnode;
            rear = newnode;
        }
    }

    int getFront() {
        if (front == nullptr) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        return front->city;
    }

    void pop() {
        if (front == nullptr) {
            cout << "Queue is empty!" << endl;
            return;
        }
        Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
    }

    bool isEmpty() {
        return front == nullptr;
    }
};



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
        visited[i] = false;
        parent[i] = -1;
    }

    // Use the custom Queue instead of std::queue
    Queue q;
    visited[src] = true;
    q.insert(src);

    while (!q.isEmpty()) {
        int u = q.getFront();
        q.pop();

        Node* temp = adj_list[u];
        while (temp != nullptr) {
            int v = temp->city;
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                q.insert(v);
            }
            temp = temp->next;
        }
    }

    if (visited[dest]) {
        cout << "Path is found: " << endl;
        print_path(parent, src, dest, cities);
    }
    else {
        cout << "No path exists from " << cities[src].name << " to " << cities[dest].name << endl;
    }

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
    int key = hash(city1, city2);
    cout << "Hash key generated: " << key << endl;

    if (key < 0 || key >= numberOfCities * numberOfCities) {
        cout << "Key out of range." << endl;
        return -1;
    }

    double distance = distances[key];
    cout << "Retrieved distance: " << distance << endl;

    if (distance < 0) {
        cout << "Invalid distance." << endl;
        return -1;
    }

    return distance;
}

void Graph::add_distance(double distances[], char* city1, char* city2, double distance) {
    // Calculate the hash key for the cities
    int key = hash(city1, city2);

    // Check if the key is within range
    if (key < 0 || key >= numberOfCities * numberOfCities) {
        cout << "Key out of range." << endl;
        return;
    }

    // Store the distance in the distances array at the calculated index
    distances[key] = distance;
    cout << "Distance between " << city1 << " and " << city2 << " added: " << distance << " km" << endl;
}
