#pragma once

#include <string>
#include "graph.h"


class filereader {
protected:
    int number_of_nodes;
    int number_of_branches;
public:
    filereader();
    Graph load_database(std::string file_name);
    void setNodes(int s){
        number_of_nodes=s;
    }
    int getNodes(){
        return number_of_nodes;
    }
    void setEdges(int d){
        number_of_branches = d;
    }
    int getEdges(){
        return number_of_branches;
    }
};