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
#include <set>
#include <chrono>
#include <thread>
#include <random>


using namespace std;

class Graph {
    public:
        void outputSpanningTree(int* father, int* level);
        void outputMinimumSpanningTree(int* father, double* cost);
        void outputGraphInfo();
        int getNumVertices();
    protected:
        int num_vertices;
        int num_edges;
        int num_components;
        vector<float> edge_info;
};

#include "graph.cpp"
#include "matrix.cpp"
#include "adjlist.cpp"
#include "w_matrix.cpp"
#include "w_adjlist.cpp"
#endif