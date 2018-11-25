#include "euclidian.h"

Euclidian::Euclidian(string FileLocation){
    ifstream GraphFile;
    GraphFile.open(FileLocation);

    // Lê a primeira linha do arquivo com o número de vértices
    GraphFile >> num_vertices;

    // Redimensiona os vetores de acordo com o tamanho da lista
    coordinate.resize(num_vertices);
    visited.resize(num_vertices);
    matrix.resize(num_vertices);
    for (int i = 0; i < num_vertices; i++){
        matrix[i].resize(num_vertices);
    };

    // Lê as linhas subsequentes no formato from, to para adicionar arestas ao grafo
    double x_coord, y_coord;
    num_edges = 0;

    int current_vertex = 1;

    // Lê o arquivo e armazena as tuplas de coordenadas (x,y) em uma estrutura auxiliar
    while (GraphFile >> x_coord >> y_coord) {
        // Corrige erro de off by one
        coordinate[current_vertex - 1] = make_tuple(x_coord,y_coord);
        current_vertex++;
    }

    // Seleciona todos os pares de vértices possíveis da lista e escreve as distâncias entre eles
    // Escreve as distâncias nos lugares correspondentes da matriz
    for (int i = 0; i < num_vertices-1; i++){
        for (int j = i+1; j < num_vertices; j++){
            double dist = tupleDistance(coordinate[i], coordinate[j]);

            matrix[i][j] = dist;
            matrix[j][i] = dist;
            num_edges++;
        }
    }

    GraphFile.close();

}

double Euclidian::tupleDistance(tuple <double, double> from, tuple <double,double> to){
    double x_dif = get<0>(from) - get<0>(to);
    double y_dif = get<1>(from) - get<1>(to);
    double sum_dif = (x_dif * x_dif) + (y_dif * y_dif);
    double dist = sqrt(sum_dif);

    return dist;
}
 
int Euclidian::nearestVertex(int vertex){
    
    double min = __DBL_MAX__;
    int nearestVertex = -1;

    for (int i = 0; i < num_vertices; i++){
        if (visited[i] == false){
            if ( matrix[vertex][i] != 0 && matrix[vertex][i] < min){
                min = matrix[vertex][i];
                nearestVertex = i;
            }
        }
    }

    total_cost += min;
    visited[nearestVertex] = true;
    return nearestVertex;

}

void Euclidian::nearestVertex_TSP(int start){
    
    // Corrige erro de off by one
    start--;
    total_cost = 0;

    for (int i = 0; i < num_vertices; i++){
        visited[i] = false;
    }

    int curr_vertex = start;
    visited[start] = true;

    cout << curr_vertex + 1 << " ";
    for (int i = 0; i < num_vertices-1; i++){
        
        curr_vertex = nearestVertex(curr_vertex);
        cout << curr_vertex + 1 << " ";
    }

    cout << endl;

    cout << "Custo total: " << total_cost;

    cout << endl;
}