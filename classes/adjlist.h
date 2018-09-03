class AdjList: public Graph {
    public:
        AdjList(string FileLocation);
        void addEdge(int from, int to, int num_vertices);
        void BFS(int root);
        void DFS(int root);
        int vertexDegree(int vertex);
        vector<float> degreeInfo();
        int connectedComponents();
        void print();
    private:
        vector < list < int > > adjlist;
        vector<int> BFS_core(int root, vector<int> &discovered);
};