#pragma once

#include <iostream>
#include <limits>
#include "graph2.h"
#include "filereader.h"


using namespace std;
/**
 * Class of user's interface
 */
class Menu {
public:
    /**
     * Constructor
     */
    Menu();
    /**
     * Starts user interface
     */
    static void start();
    /**
     * Creates the normal graph used
     * @param g
     * @param file
     * @param dataset_number
     * @param dataset_file
     */
    static void interfaceNodes(Graph2 &g, filereader &file, int &dataset_number, string &dataset_file);
    /**
     * Creates de residual graph
     * @param g
     * @param file
     * @param dataset_number
     * @param dataset_file
     */
    static void interfaceNodes_scen2(Graph2 &g, filereader &file, int &dataset_number, string &dataset_file);
};