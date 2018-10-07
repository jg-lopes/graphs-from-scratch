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



void w_Matrix::Dijkstra(int root){
    auto ti = chrono::high_resolution_clock::now();
    
    // Cria distâncias do maior valor possível (infinito)
    vector < double > dist (num_vertices, __DBL_MAX__);
    dist[root] = 0;

    set< pair<double, int> > remaining_vertices;
    remaining_vertices.insert( {0, root} );


    while (!remaining_vertices.empty()) {        

        double current_dist = remaining_vertices.begin()->first;
        int current_vertex = remaining_vertices.begin()->second;
        
        remaining_vertices.erase( {current_dist, current_vertex});

        for (int neighbor = 0; neighbor < num_vertices; neighbor++){
            if (dist[neighbor] > dist[current_vertex] + matrix[current_vertex][neighbor].weight 
                        && matrix[current_vertex][neighbor].exists_vertex){

    
                dist[neighbor] = dist[current_vertex] + matrix[current_vertex][neighbor].weight;
                remaining_vertices.insert( {dist[neighbor], neighbor});

            }
        }
    }
    
    auto tf = chrono::high_resolution_clock::now();
    cout << "Duração da função: " << chrono::duration_cast<chrono::milliseconds>(tf-ti).count() << " milisegundos\n";
    for (int i = 0; i < 15; i++){
        cout << dist[i] << " ";
    }
    cout << "\n";
}



double w_Matrix::Dijkstra_target(int root, int target){
    auto ti = chrono::high_resolution_clock::now();
    
    // Cria distâncias do maior valor possível (infinito)
    vector < double > dist (num_vertices, __DBL_MAX__);
    dist[root] = 0;

    set< pair<double, int> > remaining_vertices;
    remaining_vertices.insert( {0, root} );


    while (!remaining_vertices.empty()) {       
        double current_dist = remaining_vertices.begin()->first;
        int current_vertex = remaining_vertices.begin()->second;
        if (current_vertex == target) {
            auto tf = chrono::high_resolution_clock::now();
            cout << "Duração da função: " << chrono::duration_cast<chrono::milliseconds>(tf-ti).count() << " milisegundos\n";
            return dist[current_vertex];
        }
        
        remaining_vertices.erase( {current_dist, current_vertex});

        for (int neighbor = 0; neighbor < num_vertices; neighbor++){
            if (dist[neighbor] > dist[current_vertex] + matrix[current_vertex][neighbor].weight 
                        && matrix[current_vertex][neighbor].exists_vertex){

                //remaining_vertices.erase( {dist[neighbor], neighbor});
                dist[neighbor] = dist[current_vertex] + matrix[current_vertex][neighbor].weight;
                remaining_vertices.insert( {dist[neighbor], neighbor});

            }
        }
    }
    
    auto tf = chrono::high_resolution_clock::now();
    cout << "Duração da função: " << chrono::duration_cast<chrono::milliseconds>(tf-ti).count() << " milisegundos\n";
    for (int i = 0; i < 15; i++){
        cout << dist[i] << " ";
    }
    cout << "\n";
    return __DBL_MAX__;
}



void w_Matrix::Prim(int root){
    auto ti = chrono::high_resolution_clock::now();

    vector < double > cost (num_vertices, __DBL_MAX__);
    cost[root] = 0;

    set< pair<double, int> > remaining_vertices;
    remaining_vertices.insert( {0, root} );
    
    while (!remaining_vertices.empty()){
        double current_cost = remaining_vertices.begin()->first;
        int current_vertex = remaining_vertices.begin()->second;

        remaining_vertices.erase( {current_cost, current_vertex});


        for (int neighbor = 0; neighbor < num_vertices; neighbor++){
            if (cost[neighbor] > matrix[current_vertex][neighbor].weight 
                        && matrix[current_vertex][neighbor].exists_vertex){
                
                
                cost[neighbor] = matrix[current_vertex][neighbor].weight;
                remaining_vertices.insert( {cost[neighbor], neighbor});
            }
        }
    }

    auto tf = chrono::high_resolution_clock::now();
    cout << "Duração da função: " << chrono::duration_cast<chrono::milliseconds>(tf-ti).count() << " milisegundos\n";
    for (int i = 0; i < 15; i++){
        cout << cost[i] << " ";
    }
    cout << endl;
}