class Matrix: public Graph {
    public:
        Matrix(string FileLocation);
        void addEdge(int from, int to, int num_vertices);
        void BFS(int root);
        void DFS(int root);
        void print();
    private:
        vector< vector<int> > matrix;
};