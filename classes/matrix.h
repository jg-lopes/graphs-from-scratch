class Matrix: public Graph {
    public:
        Matrix(string FileLocation);
        void addEdge(int from, int to, int num_vertices);
        void BFS(int root);
        void DFS(int root);
        vector<float> edgeInfo();
        int vertexDegree(int vertex);
        void print();
    private:
        vector< vector<int> > matrix;
};