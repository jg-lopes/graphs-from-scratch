#include "w_matrix.h"

w_Matrix::w_Matrix(string FileLocation){
    ifstream GraphFile;
    GraphFile.open(FileLocation);

    // Lê a primeira linha do arquivo com o número de vértices
    GraphFile >> num_vertices;

    // Redimensiona os vetores de acordo com o tamanho da lista
    matrix.resize(num_vertices);
    for (int i = 0; i < num_vertices; i++){
        matrix[i].resize(num_vertices);
    };

    // Lê as linhas subsequentes no formato from, to para adicionar arestas ao grafo
    int from, to;
    double weight;
    num_edges = 0;
    
    while (GraphFile >> from >> to >> weight) {
    // Correção devido ao fato dos arquivos começarem com vértice 1
        addEdge(from-1, to-1, num_vertices, weight);
    }
    
    GraphFile.close();
}

void w_Matrix::addEdge(int from, int to, int num_vertices, double weight){
    // Insere um vértice na estrutura

    if (to < num_vertices){
        Matrix_Tuple edge;
        edge.exists_vertex = true;
        edge.weight = weight;

        matrix[from][to] = edge;
        matrix[to][from] = edge;
        num_edges++;
    }
}

void w_Matrix::print(){
    // Printa no console a representação da matriz

    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix[i].size(); j++){
            cout << matrix[i][j].weight << "\t";
        }
        cout << endl;
    }
}

int distance_outside_set(vector <double> distance, vector <bool> set, int num_vertices){

    double min = __DBL_MAX__, min_index;    
    for (int neighbor = 0; neighbor < num_vertices; neighbor++) 
        if (set[neighbor] == false && distance[neighbor] <= min) 
            min = distance[neighbor], min_index = neighbor; 
   
   return min_index; 
}

void w_Matrix::Dijkstra(int root){

    // Cria distâncias do maior valor possível (infinito)
    vector < double > dist (num_vertices, __DBL_MAX__);


    vector < bool > set (num_vertices, false); // Conjunto S
    int num_in_set = 0;

    dist[root] = 0;

    while (num_in_set != num_vertices) {        
        int u = distance_outside_set(dist, set, num_vertices);
        num_in_set++;
        set[u] = true;

        for (int neighbor = 0; neighbor < num_vertices; neighbor++){
            if (dist[neighbor] > dist[u] + matrix[u][neighbor].weight && matrix[u][neighbor].exists_vertex){
                dist[neighbor] = dist[u] + matrix[u][neighbor].weight;
            }
        }
    }
    
    for (int i = 0; i < num_vertices; i++){
        cout << dist[i] << " ";
    }
    cout << "\n";

}