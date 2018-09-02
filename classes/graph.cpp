#include "graph.h"

void Graph::outputSpanningTree(int* father, int* level){
    // Gerando arquivo de saída
    ofstream output;
    output.open("spanning_tree.txt");

    for (int i = 0; i < num_vertices; i++){
        output << father[i] + 1 << " " << level[i] << endl;        
    }
    output.close();
}