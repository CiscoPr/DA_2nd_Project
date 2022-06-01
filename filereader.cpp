#include <fstream>
#include "filereader.h"
#include <iostream>
#include "graph2.h"

filereader::filereader() {}

Graph2 filereader::load_database(std::string filename) {
    bool empty_line = false;
    std::ifstream database;
    database.open(filename);
    if(!database.is_open()){
        std::cout << "\nCould not find that dataset. Please try again!\n";
        exit(0);        //should we keep this or change to a call to the menu start func?

    }else{
        std::string nodes, edges, initial_node, dest_node, capacity, duration;
        getline(database, nodes, ' ');
        getline(database, edges);
        int edges_integer = stoi(edges);
        int nodes_integer = stoi(nodes);
        std::cout << "\nIt has " << edges_integer << " edges and " << nodes_integer << " nodes\n";
        Graph2 graph(nodes_integer, true);
        while(edges_integer!= 0){
            getline(database, initial_node, ' ');
            getline(database, dest_node, ' ');
            getline(database, capacity , ' ');
            getline(database, duration);
            int src = stoi(initial_node);
            int dest = stoi(dest_node);
            int cap = stoi(capacity);
            int dur = stoi(duration);
            graph.addEdge(src, dest, 0, cap, dur);
            //std::cout << "The init node is " << src << " the final is " << dest << " with capacity of " << cap << " and duration of " << dur << "\n";
            edges_integer --;
        }
        int s, d, number_of_people;
        std::cout << "Please enter your initial node: ";
        std::cin >> s;
        std::cout << "Please enter your final node: ";
        std::cin >> d;

        graph.maxFlow(s, d);
        /*if(graph.bfs(s, d)) {
            std::cout << "\nIt's reachable\n";
            std::cout << "Please insert the number of people of the group: ";
            std::cin >> number_of_people;
        }
        else{
            std::cout << "\nit's not reachable\n";
        }
        graph.edmondskarp(graph, s, d);
        //graph.fordfulkerson(graph);
        database.close();*/
        return graph;
    }
}