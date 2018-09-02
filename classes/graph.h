#include <string>
#include <list>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>

using namespace std;

class Graph {
    public:
        void printNumVertices();
    protected:
        int num_vertices;
        int num_edges;
        string GraphLocation;
};
