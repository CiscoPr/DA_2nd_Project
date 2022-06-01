#pragma once

#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <stack>

#include "maxHeap.h"

using namespace std;

class Graph2 {
    struct Edge {

        int dest;   // Destination node

        int capacity; // An integer weight
        int duration;
    };

    struct Node {
        vector<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        int pred;
        bool visited;
        int flow;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented



public:
    // Constructor: nr nodes and direction (default: undirected)
    explicit Graph2(int nodes, bool dir = true);
    // Add edge from source to destination with a certain weight

    void addEdge(int src, int dest, int capacity, int duration);

    //applies the Ford-Fulkerson method
    int edmondskarp(Graph2 g, int src, int dest);
    // Add edge from source to destination with a certain weight
    void addEdge_res(int src, int dest, int flux);


    pair<bool, int> bfs(int src, int f, vector<int> path);
    int dfs(int v);

    pair<int, int> maxFlow(int a, int b);

    void scenario2(int start, int end);
};