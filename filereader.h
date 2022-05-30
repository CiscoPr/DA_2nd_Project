#pragma once

#include <string>
#include "graph2.h"


class filereader {
protected:
    int number_of_nodes;
    int number_of_branches;
public:
    filereader();
    Graph2 load_database(std::string file_name);

};