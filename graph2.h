#pragma once

#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <stack>

#include "maxHeap.h"

using namespace std;

/**
 * Class of the used graph
 */
class Graph2 {

    /**
     * Struct of graph's edges
     */
    struct Edge {

        int dest;   // Destination node

        int capacity; // An integer weight
        int duration;
    };

    /**
     * Struct of graph's nodes
     */
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
     * @param src start
     * @param f end
     * @return boolean depending on if it was successful and int with capacity of path
     */
    pair<bool, int> bfs(int src, int f);
    /**
     * Determines the maximum capacity on scenario 1
     * @param a start
     * @param b end
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
    /**
     * BFS algorithm adapted for the obtained residual graph
     * @param src
     * @param dest
     * @param resid
     * @return
     */
    bool bfs_for_scenario2(int src, int dest, vector<vector<pair<int, int>>> resid);

    /**
     * creates a flux graph
     * @param rGraph
     * @return
     */
    vector<vector<vector<int>>> create_Flux_graph(vector<vector<pair<int, int>>> rGraph);

    /**
     * the function used to determine a path for the user input group
     * @param g
     * @param src
     * @param dest
     * @param dimension
     * @return
     */
    vector<vector<int>> random_dimension_divided_groups(Graph2 g, int src, int dest, int dimension);

    /**
     * calculates de max flow for scenario 2
     * @param g
     * @param src
     * @param dest
     * @return
     */
    int max_flow_separated_groups(Graph2 g, int src, int dest);

    /**
     * used for 2.4, equivalent to max capacity path time
     * @param g
     * @param a
     * @param b
     * @return
     */
    int minimum_time(Graph2 g, int a, int b);

    /**
     * used to compute the max wait time of the path
     * and shows the nodes with that time
     * @param p
     * @return
     */
    int maximum_wait_time(Graph2 g, vector<vector<int>> p);
};