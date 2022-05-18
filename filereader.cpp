//
// Created by 35191 on 18/05/2022.
//

#include <fstream>
#include "filereader.h"
#include <iostream>
#include "graph.h"
filereader::filereader() {}

void filereader::load_database(std::string filename) {
    bool empty_line = false;
    std::ifstream database;
    database.open(filename);
    if(!database.is_open()){
        std::cout << "Could not find that dataset. Please try again!";
        database.close();
    }
    std::string nodes, edges, initial_node, dest_node, capacity, duration;
    getline(database, nodes, ' ');
    getline(database, edges);
    setNodes(stoi(nodes));
    setEdges(stoi(edges));
    int edges_integer = getEdges();
    int nodes_integer = getNodes();
    std::cout << "\nIt has " << edges_integer << " edges and " << nodes_integer << " nodes\n";
    Graph graph(nodes_integer, true);
    while(edges_integer!= 0){
        getline(database, initial_node, ' ');
        getline(database, dest_node, ' ');
        getline(database, capacity , ' ');
        getline(database, duration);
        int src = stoi(initial_node);
        int dest = stoi(dest_node);
        int cap = stoi(capacity);
        int dur = stoi(duration);
        graph.addEdge(src, dest, cap, dur);
        //std::cout << "The init node is " << src << " the final is " << dest << " with capacity of " << cap << " and duration of " << dur << "\n";
        edges_integer --;
    }
}