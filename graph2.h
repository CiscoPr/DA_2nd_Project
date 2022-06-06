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

    int maxStops;
    int minFlow;

public:
    /**
     * constructor of the graph
     * @param nodes
     * @param dir
     */
    // Constructor: nr nodes and direction (default: undirected)
    explicit Graph2(int nodes, bool dir = true);
    /**
     * adds the edges to the graph
     * @param src
     * @param dest
     * @param capacity
     * @param duration
     */
    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, int capacity, int duration);
    //applies the Ford-Fulkerson method
    /**
     * applies the Edmonds-Karp algorithm to the graph
     * @param g
     * @param src
     * @param dest
     * @return
     */
    int edmondskarp(Graph2 g, int src, int dest);
    // Add edge from source to destination with a certain weight
    //void addEdge_res(int src, int dest, int flux);
    /**
     * Applies the Breadth-First Search strategy to the graph
     * @param src
     * @param f
     * @return
     */
    pair<bool, int> bfs(int src, int f);
    /**
     * Determines the maximum flow on scenario 1
     * @param a
     * @param b
     * @return
     */
    pair<int, int> maxFlow(int a, int b);
    /**
     * Used for the second exercise of the 1st scenario
     * @param start
     * @param end
     */
    void scenario2(int start, int end);
    void printAllPaths(int s, int d, vector<queue<int>> &help, queue<int> aux);
    /**
     * create the residual graph of graph g
     * @param g
     * @return
     */
    vector<vector<pair<int,int>>> createResidualGraph(Graph2 g);

    bool bfs_for_scenario2(int src, int dest, vector<vector<pair<int, int>>> resid);

    vector<vector<vector<int>>> create_Flux_graph(vector<vector<pair<int, int>>> rGraph);

    int random_dimension_divided_groups(Graph2 g, int src, int dest, int dimension);

    int max_flow_separated_groups(Graph2 g, int src, int dest);

    int minimum_time(Graph2 g, int a, int b);
};