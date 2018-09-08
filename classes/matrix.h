#ifndef MATRIX_H
#define MATRIX_H

class Matrix: public Graph {
    public:
        Matrix(string FileLocation, int directed);
        void addEdgeDirected(int from, int to, int num_vertices);
        void addEdgeUndirected(int from, int to, int num_vertices);
        void BFS(int root);
        void DFS(int root);
        vector<float> degreeInfo(); 
        int vertexDegree(int vertex);
        int connectedComponents();
        void print();
    private:
        vector< vector<int> > matrix;
        vector<int> BFS_core(int root, vector<int> &discovered);
};

#endif