class AdjList: private Graph {
    public:
        AdjList(string FileLocation);
        void addEdge(int from, int to, int num_vertices);
        void BFS(int root);
        void DFS(int root);
        int vertexDegree(int vertex);
        vector<float> edgeInfo();
        void print();
    private:
     vector < list < int > > adjlist;
};