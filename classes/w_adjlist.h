#ifndef W_ADJLIST_H
#define W_ADJLIST_H

typedef struct AdjList_Tuple {
    int connected_vertex;
    double weight;
} AdjList_Tuple;

class w_AdjList: public Graph {
    public:
        w_AdjList(string FileLocation);
        void addEdge(int from, int to, int num_vertices, double weight);
        void print();
        void Dijkstra(int root);
        pair < double, vector <int> > Dijkstra_target(int root, int target);
        double Prim(int root);
        double excentricity(int root);
        double medium_distance();
    protected:
        vector < int > findPathFromParent (vector < int > parent, int target);
    private:
        vector < list < AdjList_Tuple > > adjlist;
        pair < vector < double >, vector <int> > Dijkstra_core(int root);
};
 
#endif