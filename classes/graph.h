#include <string>
#include <list>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

class Graph {
    public:
        void outputSpanningTree(int* father, int* level);
    protected:
        int num_vertices;
        int num_edges;
        string GraphName;
};
