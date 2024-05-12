#include "Graph_p2_lib.h"

void Graph::insert_edge(Node* adj_list[], int src, int dest)
{
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

int Graph::hash(char* c1, char* c2) {
    const int maxLength = 100;
    char key[maxLength];

    // Concatenate the names of the two cities
    strcpy_s(key, c1);
    strcat_s(key, c2);

    // Calculate the hash value
    int hashValue = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hashValue += key[i];
    }

    // Return the hash value
    return hashValue % maxLength;
}

int Graph::find_distance(Distance distances[], char* city1, char* city2) {
    int key = hash(city1, city2);
    cout << "Hash key generated: " << key << endl;

    if (key < 0 || key >= numberOfCities * numberOfCities) {
        cout << "Key out of range." << endl;
        return -1;
    }

    // Linear probing to find the distance
    int index = key;
    while (distances[index].cities_key != key || strcmp(distances[index].city1, city1) != 0 || strcmp(distances[index].city2, city2) != 0) {
        index = (index + 1) % (numberOfCities * numberOfCities);
        if (index == key) {
            cout << "Distance not found." << endl;
            return -1; // Distance not found
        }
    }

    return distances[index].distance;
}

void Graph::add_distance(Distance distances[], char* city1, char* city2, int distance) {
    // Calculate the hash key for the cities
    int key = hash(city1, city2);

    // Linear probing to add distance
    int index = key;
    while (distances[index].cities_key != -1) {
        index = (index + 1) % (numberOfCities * numberOfCities);
        if (index == key) {
            cout << "Distance table is full." << endl;
            return; // Distance table is full
        }
    }

    // Store the distance in the distances array at the calculated index
    distances[index].city1 = city1;
    distances[index].city2 = city2;
    distances[index].cities_key = key;
    distances[index].distance = distance;
    cout << "Distance between " << city1 << " and " << city2 << " added: " << distance << " km" << endl;
}
