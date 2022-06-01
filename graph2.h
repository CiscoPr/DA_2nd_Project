#pragma once

#include <vector>
#include <list>
#include <queue>
#include <iostream>

#include "maxHeap.h"

using namespace std;

class Graph2 {
    struct Edge {

        int dest;   // Destination node
        int flux; //TODO
        int capacity; // An integer weight
        int duration;
        int parent;
    };

    struct Node {
        vector<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        int dist;
        int pred;
        bool visited;
        int flow;
        int parent;
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
    int edmondskarp(Graph2 g, int src, int dest);
    // Add edge from source to destination with a certain weight
    void addEdge_res(int src, int dest, int flux);

    bool bfs(int src, int f);
    int dfs(int v);

    int maxFlow(int a, int b);
};