#ifndef EUCLIDIAN_H
#define EUCLIDIAN_H

class Euclidian: public Graph{
    public:
        Euclidian(string FileLocation);
        double tupleDistance(tuple <double, double> from, tuple <double,double> to);
        int nearestVertex(int vertex);
        void nearestVertex_TSP(int start);

    private:
        vector< vector<int> > matrix;
        vector< tuple<double,double> > coordinate; 
        vector <bool> visited;
        double total_cost;
};

#endif