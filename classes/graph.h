#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <list>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <stack>
#include <algorithm>


using namespace std;

class Graph {
    public:
        void outputSpanningTree(int* father, int* level);
        void outputGraphInfo();
    protected:
        int num_vertices;
        int num_edges;
        int num_components;
        vector<float> edge_info;
};

#include "graph.cpp"
#include "matrix.cpp"
#include "adjlist.cpp"

#endif