#include <iostream>
#include "graph.h" 

int main() {
    Graph myGraph;

    // Define cities
    City cities[] = {
        {"Islamabad", 0},
        {"Gujrat", 1},
        {"Vehari", 2},
        {"Pindi", 3},
        {"Karachi", 4}
    };

    // Total number of cities
    const int cityCount = sizeof(cities) / sizeof(cities[0]);

    // Initialize the adjacency list
    Node* adjList[cityCount] = { nullptr };

    // Insert edges according to the paths you want to establish
    myGraph.insert_edge(adjList, 0, 2); // Islamabad to Vehari
    myGraph.insert_edge(adjList, 0, 3); // Islamabad to Pindi
    myGraph.insert_edge(adjList, 1, 4); // Gujrat to Karachi
    myGraph.insert_edge(adjList, 4, 3); // Karachi to Pindi

    // Parent array initialization
    int parents[cityCount];
    for (int i = 0; i < cityCount; i++) {
        parents[i] = -1; // Initialize all parents as -1 (no parent)
    }

    
    parents[2] = 0; // Vehari's parent is Islamabad
    parents[3] = 0; // Pindi's parent is Islamabad (for path from Islamabad)
    parents[4] = 1; // Karachi's parent is Gujrat (for path from Gujrat)
    parents[3] = 4; // Pindi's parent is Karachi (for path from Karachi)

    // Print paths to demonstrate the setup
    myGraph.print_path(parents, 0, 2, cities); // Path from Islamabad to Vehari
    myGraph.print_path(parents, 0, 3, cities); // Path from Islamabad to Pindi
    myGraph.print_path(parents, 1, 4, cities); // Path from Gujrat to Karachi
    myGraph.print_path(parents, 4, 3, cities); // Path from Karachi to Pindi
    return 0;
}
