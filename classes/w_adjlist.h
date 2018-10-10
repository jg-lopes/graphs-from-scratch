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
        vector <double> Dijkstra(int root);
        pair < double, vector <int> > Dijkstra_target(int root, int target);
        double Prim(int root, bool output);
        double excentricity(int root);
        double medium_distance();
        double medium_distance_probabilistic(int iterations);
        int vertexDegree(int vertex);
        vector<int> three_Max_Degrees();
        void print_neighbours(int vertex);
    protected:
        vector < int > findPathFromParent (vector < int > parent, int target);
    private:
        vector < list < AdjList_Tuple > > adjlist;
        pair < vector < double >, vector <int> > Dijkstra_core(int root);
};
 
#endif