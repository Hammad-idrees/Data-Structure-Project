#include <iostream>
#include "Graph_p2_lib.h"

// main function
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

    // Initialize the distances array
    myGraph.numberOfCities = cityCount;
    Distance* distances = new Distance[cityCount * cityCount];
    for (int i = 0; i < cityCount * cityCount; ++i) {
        distances[i].cities_key = -1; // Mark all keys as -1 indicating empty
    }

    // Add distances
    myGraph.add_distance(distances, cities[0].name, cities[1].name, 200); // Islamabad to Gujrat
    myGraph.add_distance(distances, cities[0].name, cities[2].name, 300); // Islamabad to Vehari
    myGraph.add_distance(distances, cities[0].name, cities[3].name, 250); // Islamabad to Pindi
    myGraph.add_distance(distances, cities[0].name, cities[4].name, 500); // Islamabad to Karachi
    myGraph.add_distance(distances, cities[1].name, cities[4].name, 600); // Gujrat to Karachi
    myGraph.add_distance(distances, cities[4].name, cities[3].name, 300); // Karachi to Pindi

    // Example cities
    City city1 = cities[4]; // karachi
    City city2 = cities[3]; // Pindi

    // Using BFS
    cout << "Showing BFS Results:\n";
    myGraph.bfs(adjList, 1, 3, cities, cityCount); //gujrat to pindi

    // Calculate hash key
    cout << "Showing Hash key Results:\n";
    int key = myGraph.hash(city1.name, city2.name);
    cout << "Hash key for (" << city1.name << ", " << city2.name << "): " << key << endl;

    // Find the distance between Islamabad and Pindi
    cout << "Showing Distance Results:\n";
    double distance = myGraph.find_distance(distances, city1.name, city2.name);
    if (distance != -1) {
        cout << "Distance between " << city1.name << " and " << city2.name << ": " << distance << " km\n";
    }
    else {
        cout << "No valid distance found between " << city1.name << " and " << city2.name << ".\n";
    }

    delete[] distances; // Free allocated memory
    return 0;
}
