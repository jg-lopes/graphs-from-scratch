class Matrix: public Graph {
    public:
        Matrix(string FileLocation);
        void addEdge(int from, int to);
        void print();
    private:
        vector< vector<int> > matrix;
};