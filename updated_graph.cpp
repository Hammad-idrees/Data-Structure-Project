#include <iostream>
#include "updated_graph.h"

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



    int parents[cityCount];
    for (int i = 0; i < cityCount; i++) {
        parents[i] = -1; // Initialize all parents as -1 (no parent)
    }


    parents[2] = 0; // Vehari's parent is Islamabad
    parents[3] = 0; // Pindi's parent is Islamabad (for path from Islamabad)
    parents[4] = 1; // Karachi's parent is Gujrat (for path from Gujrat)
    parents[3] = 4; // Pindi's parent is Karachi (for path from Karachi)


    cout << "Printing Citites:\n";

    // Print paths to demonstrate the setup
    myGraph.print_path(parents, 0, 2, cities); // Path from Islamabad to Vehari
    myGraph.print_path(parents, 0, 3, cities); // Path from Islamabad to Pindi
    myGraph.print_path(parents, 1, 4, cities); // Path from Gujrat to Karachi
    myGraph.print_path(parents, 4, 3, cities); // Path from Karachi to Pindi

    cout << endl << endl;
    cout << "************************************" << endl << endl;


    // Define a direct mapping of distances based on city index combinations
    const int pairCount = cityCount * cityCount;
    double distances[pairCount] = { 0 }; // Initialize all distances to zero

   
   




    // Ensure all other distances are initialized if not set directly
    for (int i = 0; i < pairCount; i++) {
        if (distances[i] == 0) distances[i] = -1; // Indicate no direct connection
    }

    // Using BFS

    cout << "Showing BFS Results:\n";
    myGraph.bfs(adjList, 1, 3, cities, cityCount); //gujrat to pindi
  

    // Example cities
    City city1 = cities[4]; // karachi
    City city2 = cities[3]; // Pindi

    // Calculate hash key
    cout << endl << endl;
    cout << "************************************" << endl << endl;
    cout << "Showing Hash key  Results:\n";
    int key = myGraph.hash(city1.name, city2.name);
    cout << "Hash key for (" << city1.name << ", " << city2.name << "): " << key << endl;
    cout << endl << endl;
    cout << "************************************" << endl << endl;


    // Find the distance between Islamabad and Pindi
    int index = city1.index * cityCount + city2.index;
  
    cout << "Showing Distance  Results:\n";
    // Print the distance if found


    myGraph.add_distance(distances, cities[0].name, cities[1].name, 200); // Islamabad to Gujrat
    myGraph.add_distance(distances, cities[0].name, cities[2].name, 300); // Islamabad to Vehari
    myGraph.add_distance(distances, cities[0].name, cities[3].name, 250); // Islamabad to Pindi
    myGraph.add_distance(distances, cities[0].name, cities[4].name, 500); // Islamabad to Karachi
    myGraph.add_distance(distances, cities[1].name, cities[4].name, 600); // Gujrat to Karachi
    myGraph.add_distance(distances, cities[4].name, cities[3].name, 300); //karachi to pindi


   
    double distance = myGraph.find_distance(distances, city1.name, city2.name);
    cout << "Showing Distance Results:\n";
    if (distance != -1) {
        cout << "Distance between " << city1.name << " and " << city2.name << ": " << distance << " km\n";
    }
    else {
        cout << "No valid distance found between " << city1.name << " and " << city2.name << ".\n";
    }



    cout << endl << endl;
    cout << "************************************" << endl << endl;

    return 0;
}

