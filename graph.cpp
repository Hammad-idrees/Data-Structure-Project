#include <iostream>
#include "graph.h" 

int main()
{
    Graph myGraph;

    // Define cities
    City cities[] =
    {
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

    // Call BFS to find paths from source to destination
    myGraph.bfs(adjList, 0, 3, cities, cityCount); // Find path from Islamabad to Pindi

    // Example cities
    City city1 = cities[0]; // Islamabad
    City city2 = cities[3]; // Pindi

    // Calculate hash key
    int key = myGraph.hash(city1.name, city2.name);

    // Print hash key
    cout << "Hash key for (" << city1.name << ", " << city2.name << "): " << key << endl;

    // for find_distance function
    // Example distances array
    double distances[] =
    {
        // Distance between Islamabad and Gujrat
        200,
        // Distance between Islamabad and Vehari
        300,
        // Distance between Islamabad and Pindi
        250,
        // Distance between Islamabad and Karachi
        500,
        // Distance between Gujrat and Vehari
        150,
        // Distance between Gujrat and Pindi
        350,
        // Distance between Gujrat and Karachi
        600,
        // Distance between Vehari and Pindi
        200,
        // Distance between Vehari and Karachi
        450,
        // Distance between Pindi and Karachi
        300
    };

    // Find the distance between the cities
        double distance = myGraph.find_distance(distances, city1.name, city2.name);

        // Print the distance if found
        if (distance != -1) {
            cout << "Distance between " << city1.name << " and " << city2.name << ": " << distance << endl;
        }
        else {
            cout << "Distance between " << city1.name << " and " << city2.name << " not found." << endl;
        }

        
    return 0;
}
