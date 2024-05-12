#pragma once

#include <iostream>
#include <cstring>
#include <string>
#include <queue>

using namespace std;

typedef struct {
    char name[50];
    int index;
} City;

typedef struct node {
    int city;
    struct node* next;
} Node;

typedef struct {
    char* city1;
    char* city2;
    int cities_key;
    int distance;
} Distance;

class Queue
{
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
    
    Node** adjList;
    Distance* distances;

public:
    int numberOfCities;
    void insert_edge(Node* adj_list[], int src, int dest);
    void print_path(int parent[], int src, int dest, City cities[]);
    void bfs(Node* adj_list[], int src, int dest, City cities[], int n);
    int hash(char* c1, char* c2);
    int find_distance(Distance distances[], char* city1, char* city2);
    void add_distance(Distance distances[], char* city1, char* city2, int distance);
};
