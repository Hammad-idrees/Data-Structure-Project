#include<iostream>
#include "Q3_Rafae.h"
#include<string>
using namespace std;

int main() {
    Graph myGraph;

    // Example cities
    City cities[] = {
        {"Islamabad", 0},
        {"Gujrat", 1},
        {"Vehari", 2},
        {"Pindi", 3},
        {"Karachi", 4}
    };

    // Add distances between cities
    myGraph.add_distance(myGraph.distances, "Islamabad", "Gujrat", 200);
    myGraph.add_distance(myGraph.distances, "Islamabad", "Vehari", 300);
    myGraph.add_distance(myGraph.distances, "Islamabad", "Pindi", 250);
    myGraph.add_distance(myGraph.distances, "Islamabad", "Karachi", 500);
    myGraph.add_distance(myGraph.distances, "Gujrat", "Vehari", 150);
    myGraph.add_distance(myGraph.distances, "Gujrat", "Pindi", 350);
    myGraph.add_distance(myGraph.distances, "Gujrat", "Karachi", 600);
    myGraph.add_distance(myGraph.distances, "Vehari", "Pindi", 200);
    myGraph.add_distance(myGraph.distances, "Vehari", "Karachi", 450);
    myGraph.add_distance(myGraph.distances, "Pindi", "Karachi", 300);

    // Example queries
    char* city1 = "Islamabad";
    char* city2 = "Karachi";

    // Find distance between cities
    int distance = myGraph.find_distance(myGraph.distances, city1, city2);

    // Print the distance if found
    if (distance != -1) {
        std::cout << "Distance between " << city1 << " and " << city2 << ": " << distance << std::endl;
    }
    else {
        std::cout << "Distance between " << city1 << " and " << city2 << " not found." << std::endl;
    }

    return 0;
}
