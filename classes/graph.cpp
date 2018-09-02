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


vector<int> VectorMinMax(vector<int> list) {
    // Retorna o valor mínimo e máximo em uma lista nos índices 0 e 1
    // Retorna os índices mínimo e máximo nos índices 2, 3
    int min = list[0];
    int i_min = 0;
    int max = list[0];
    int i_max = 0;

    for (int i = 0; i < list.size(); i++) {
        if (list[i] < min) {
            min = list[i];
            i_min = i;
        }
        if (list[i] > max) {
            max = list[i];
            i_max = i;
        }
    }

    vector <int> result {min, max, i_min, i_max};
    return result;
}