#include "graph.h"

class AdjList: private Graph {
    public:
        AdjList(string FileLocation);
        void addEdge(int from, int to);
        void print();
    private:
     vector < list < int > > adjlist;
};