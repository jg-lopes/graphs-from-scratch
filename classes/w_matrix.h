#ifndef W_MATRIX_H
#define W_MATRIX_H

typedef struct Matrix_Tuple {
    bool exists_vertex = false;
    double weight;
} Matrix_Tuple;

class w_Matrix: public Graph {
    public: 
        w_Matrix(string FileLocation);
        void addEdge(int from, int to, int num_vertices, double weight);
        void print();
        void Dijkstra(int root);
        double Dijkstra_target(int root, int target);
        void Prim(int root);
    private:
        vector< vector<Matrix_Tuple> > matrix;
};

#endif