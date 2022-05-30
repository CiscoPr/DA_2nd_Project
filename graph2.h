#pragma once

#include <vector>
#include <list>
#include <queue>
#include <iostream>

using namespace std;

class Graph2 {
    struct Edge {

        int dest;   // Destination node
        int flux; //TODO
        int capacity; // An integer weight
        int duration;
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        int dist;
        int pred;
        bool visited;
        string name;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented



public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph2(int nodes, bool dir = true);
    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, int flux,  int capacity, int duration);
    //applies the Ford-Fulkerson method
    void fordfulkerson(Graph2 g, int src, int dest);
    list<int> fordfulkerson_path(Graph2 g);
    bool bfs(int src, int f);
    void edges();
    void stops();
};