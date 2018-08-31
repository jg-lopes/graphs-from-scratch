#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "graph.h"

using namespace std;

int main() {
    ifstream GraphFile;
    GraphFile.open("graph.txt");
    
    string fileLine;
    
    getline(GraphFile, fileLine);
    istringstream iss(fileLine);
    int num_vertex;
    iss >> num_vertex;
    cout << num_vertex << endl;

    while (getline(GraphFile, fileLine)) {
        istringstream iss(fileLine);
        int a, b;
        iss >> a >> b;  
        //if (!(iss >> a >> b)) { break; } // error

        cout << a << " " << b << endl;
        
    }

    GraphFile.close();
    return 0;
}