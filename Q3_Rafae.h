#pragma once
#include <iostream>
#include<string>

typedef struct {
    char* city1;
    char* city2;
    int cities_key;
    int distance;
} Distance;

struct Node {
    int city;
    Node* next;
};

typedef struct {
    char name[50];
    int index;
} City;

class Graph {
private:
    int numberOfCities;
    Node** adjList;
    Distance* distances;
    const int maxLength = 100; // Maximum length for linear probing

public:
    Graph();
    ~Graph();
    void insert_edge(Node* adj_list[], int src, int dest);
    void print_path(int parent[], int src, int dest, City cities[]);
    void bfs(Node* adj_list[], int src, int dest, City cities[], int n);
    int hash(char* c1, char* c2);
    void add_distance(Distance distances[], char* city1, char* city2, int distance);
    int find_distance(Distance distances[], char* city1, char* city2);
};

