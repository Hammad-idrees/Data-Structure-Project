#pragma once
#include "Q3_Rafae"
#include "Q3_Rafae2"


Graph::Graph() {
    adjList = new Node * [maxLength];
    for (int i = 0; i < maxLength; ++i) {
        adjList[i] = nullptr;
    }
    distances = new Distance[maxLength];
    for (int i = 0; i < maxLength; ++i) {
        distances[i].distance = -1;
    }
}

Graph::~Graph() {
    for (int i = 0; i < maxLength; ++i) {
        Node* current = adjList[i];
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] adjList;
    delete[] distances;
}

void Graph::insert_edge(Node* adj_list[], int src, int dest) {
    Node* newNode = new Node;
    newNode->city = dest;
    newNode->next = adj_list[src];
    adj_list[src] = newNode;
}

void Graph::print_path(int parent[], int src, int dest, City cities[]) {
    // Implementation of print_path function
}

void Graph::bfs(Node* adj_list[], int src, int dest, City cities[], int n) {
    // Implementation of bfs function
}

int Graph::hash(char* c1, char* c2) {
    int hashValue = 0;
    for (int i = 0; c1[i] != '\0'; i++) {
        hashValue += c1[i];
    }
    for (int i = 0; c2[i] != '\0'; i++) {
        hashValue += c2[i];
    }
    return hashValue % maxLength;
}

void Graph::add_distance(Distance distances[], char* city1, char* city2, int distance) {
    int key = hash(city1, city2);
    int index = key % maxLength;
    while (distances[index].distance != -1) {
        index = (index + 1) % maxLength;
    }
    // Found an empty slot, add the distance
    distances[index].city1 = city1;
    distances[index].city2 = city2;
    distances[index].cities_key = key;
    distances[index].distance = distance;
}

int Graph::find_distance(Distance distances[], char* city1, char* city2) {
    int key = hash(city1, city2);
    int index = key % maxLength;

    // Calculate lengths of city1 and city2
    int city1_length = 0;
    while (city1[city1_length] != '\0') {
        city1_length++;
    }

    int city2_length = 0;
    while (city2[city2_length] != '\0') {
        city2_length++;
    }

    // Loop through distances array until finding the correct key or an empty slot
    while (distances[index].cities_key != key || distances[index].distance == -1) {
        index = (index + 1) % maxLength;
        if (index == key % maxLength) {
            // Cycled through all slots without finding the distance
            return -1;
        }
    }

    // Check if city names match
    int i = 0;
    while (i < city1_length && distances[index].city1[i] == city1[i]) {
        i++;
    }
    if (i != city1_length || distances[index].city1[i] != '\0') {
        // City1 names don't match, continue searching
        return -1;
    }

    i = 0;
    while (i < city2_length && distances[index].city2[i] == city2[i]) {
        i++;
    }
    if (i != city2_length || distances[index].city2[i] != '\0') {
        // City2 names don't match, continue searching
        return -1;
    }

    // Found the distance
    return distances[index].distance;
}