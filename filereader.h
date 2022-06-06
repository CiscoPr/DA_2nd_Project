#pragma once

#include <string>
#include "graph2.h"


class filereader {

public:
    filereader();
    /**
     * loads the graph of the desired database
     * @param file_name
     * @return
     */
    Graph2 load_database(const std::string& file_name);
    /**
     * returns the nodes chosen by the user
     * @param graph
     * @param choice
     * @return
     */
    pair<int, int> chooseNodes(Graph2 graph, int choice);
};