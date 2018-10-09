#include "graph.h"

void Graph::outputSpanningTree(int* father, int* level){
    // Gera arquivo de saída com a árvore geradora
    ofstream output;
    output.open("spanning_tree.txt");

    for (int i = 0; i < num_vertices; i++){
        output << father[i] << " " << level[i] << endl;        
    }
    output.close();
}

void Graph::outputGraphInfo(){
    // Gerando arquivo de saída
    ofstream output;
    output.open("graph_info.txt");

    output << "Número de Vértices: " << num_vertices << endl;
    output << "Número de Arestas: " << num_edges << endl;
    output << "Grau Mínimo: " << edge_info[0] << endl;
    output << "Grau Máximo: " << edge_info[1] << endl;
    output << "Média do Grau: " << edge_info[2] << endl;
    output << "Mediana de Grau: " << edge_info[3] << endl;

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

void outputConnectedComponents(vector< vector<int> > verticesComponent){
    // Ordenando do maior componente para o menor em número de vértices
    sort(verticesComponent.begin(), verticesComponent.end(), [](const vector<int> & a, const vector<int> & b){ return a.size() > b.size(); });

    ofstream output;
    output.open("connected_components.txt");

    output << verticesComponent.size() << endl;

    for (int i = 0; i < verticesComponent.size(); i++) {
        
        output << verticesComponent[i].size() << " ";

        for (int j = 0; j < verticesComponent[i].size(); j++){
            output << verticesComponent[i][j] << " ";
        }
        
        output << endl;
    }
}

int Graph::getNumVertices(){
    return num_vertices;
}