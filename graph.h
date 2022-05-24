#pragma once

#include <vector>
#include <list>
#include <queue>
#include <iostream>

using namespace std;

class Graph {
    struct Edge {
        int dest;   // Destination node
        int capacity; // An integer capacity
        int duration; // an integer duration
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;   // As the node been visited on a search?
    };
    int edges;           //number of edges
    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);
    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, int capacity, int duration);
};