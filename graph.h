#pragma once

#include <iostream>
#include <cstring>

using namespace std;


typedef struct {
    char name[50];
    int index;
} City;


typedef struct node {
    int city;
    struct node* next;

}Node;




class Graph {
private:
    int numberOfCities;
    Node** adjList;
    int** distances; 

public:
    void insert_edge(Node* adj_list[], int src, int dest);
    void print_path(int parent[], int src, int dest, City cities[]);


};



//bool hashchain(T sent) {
        //        if (head == NULL) {
        //            head = new Node<T>(sent);
        //            head->next = head; 
        //            return true;
        //        }
        //        else {
        //            Node<T>* temp = head;
        //            while (temp!= head) {
        //                if (temp->data == sent) 
        //                    return false;
        //                temp = temp->next;
        //            }
        //            if (temp->data == sent) 
        //                return false;
        //
        //            Node<T>* newnode = new Node<T>(sent);
        //            newnode->next = head; 
        //            temp->next = newnode; 
        //            return true;
        //        }
        //    }
        //


void Graph::insert_edge(Node* adj_list[], int src, int dest) {
   
    Node* newNode = new Node;
    newNode->city = dest;
    newNode->next = adj_list[src];
    adj_list[src] = newNode;
}





void Graph :: print_path(int parent[], int src, int dest, City cities[]) {
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




