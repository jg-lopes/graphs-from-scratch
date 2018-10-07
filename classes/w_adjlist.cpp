#include "w_adjlist.h"

w_AdjList::w_AdjList(string FileLocation){
    ifstream GraphFile;
    GraphFile.open(FileLocation);

    // Lê a primeira linha do arquivo com o número de vértices
    GraphFile >> num_vertices;

    // Redimensiona os vetores de acordo com o tamanho da adjlista
    adjlist.resize(num_vertices);
    
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


void w_AdjList::addEdge(int from, int to, int num_vertices, double weight){
    // Insere um vértice na estrutura

    if (to < num_vertices){
        AdjList_Tuple adjacent;
        adjacent.connected_vertex = to;
        adjacent.weight = weight; 

        adjlist[from].push_back(adjacent);

        adjacent.connected_vertex = from;
        adjacent.weight = weight;

        adjlist[to].push_back(adjacent); 
        num_edges++;   
    }
}

void w_AdjList::print(){
    // Printa no console a representação da matriz

    for (int i = 0; i < adjlist.size(); i++){
        cout << "Adjacency adjlist of vertex " << i << endl;

        for (list<AdjList_Tuple>::iterator it = adjlist[i].begin(); it != adjlist[i].end(); ++it)
            cout << " (" << it->connected_vertex << ", " << it->weight << ")";

        cout << endl;
    }

}

void w_AdjList::Dijkstra(int root){
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

        for (list<AdjList_Tuple>::iterator it = adjlist[current_vertex].begin(); it != adjlist[current_vertex].end(); ++it){
            int neighbor = it->connected_vertex; 
            if (dist[neighbor] > dist[current_vertex] + it->weight) {
                dist[neighbor] = dist[current_vertex] + it->weight;
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


double w_AdjList::Dijkstra_target(int root, int target){
    // Calcula a menor distância entre dois vértices

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
            //cout << "Duração da função: " << chrono::duration_cast<chrono::milliseconds>(tf-ti).count() << " milisegundos\n";
            return dist[current_vertex];
        }

        remaining_vertices.erase( {current_dist, current_vertex});

        for (list<AdjList_Tuple>::iterator it = adjlist[current_vertex].begin(); it != adjlist[current_vertex].end(); ++it){
            int neighbor = it->connected_vertex; 
            if (dist[neighbor] > dist[current_vertex] + it->weight) {
                dist[neighbor] = dist[current_vertex] + it->weight;
                remaining_vertices.insert( {dist[neighbor], neighbor});
            }
        }
    }
    auto tf = chrono::high_resolution_clock::now();
    //cout << "Duração da função: " << chrono::duration_cast<chrono::milliseconds>(tf-ti).count() << " milisegundos\n";    
    for (int i = 0; i < 15; i++){
        //cout << dist[i] << " ";
    }
    //cout << "\n";

}



void w_AdjList::Prim(int root){
    auto ti = chrono::high_resolution_clock::now();

    vector < double > cost (num_vertices, __DBL_MAX__);
    cost[root] = 0;

    set< pair<double, int> > remaining_vertices;
    remaining_vertices.insert( {0, root} );
    
    while (!remaining_vertices.empty()){
        double current_cost = remaining_vertices.begin()->first;
        int current_vertex = remaining_vertices.begin()->second;

        remaining_vertices.erase( {current_cost, current_vertex});

        for (list<AdjList_Tuple>::iterator it = adjlist[current_vertex].begin(); it != adjlist[current_vertex].end(); ++it){
            int neighbor = it->connected_vertex; 
            if (cost[neighbor] > it->weight) {
                cost[neighbor] = it->weight;
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


vector < double > w_AdjList::Dijkstra_core(int root){
    // Cria distâncias do maior valor possível (infinito)
    vector < double > dist (num_vertices, __DBL_MAX__);

    dist[root] = 0;

    set< pair<double, int> > remaining_vertices;
    remaining_vertices.insert( {0, root} );


    while (!remaining_vertices.empty()) {        
        
        double current_dist = remaining_vertices.begin()->first;
        int current_vertex = remaining_vertices.begin()->second;

        remaining_vertices.erase( {current_dist, current_vertex});

        for (list<AdjList_Tuple>::iterator it = adjlist[current_vertex].begin(); it != adjlist[current_vertex].end(); ++it){
            int neighbor = it->connected_vertex; 
            if (dist[neighbor] > dist[current_vertex] + it->weight) {
                dist[neighbor] = dist[current_vertex] + it->weight;
                remaining_vertices.insert( {dist[neighbor], neighbor});
            }
        }
    }
    return dist;
}


double w_AdjList::excentricity(int root){
    auto ti = chrono::high_resolution_clock::now();
    
    double max = 0;
    int max_vertex = -1;
    

    vector <double> dist = Dijkstra_core(root);
    
    for (int vertex = 0; vertex < num_vertices; vertex++){
        if (dist[vertex] > max) {
            max = dist[vertex];
            max_vertex = vertex;
        }
    }
    
    auto tf = chrono::high_resolution_clock::now();
    cout << "Duração da função: " << chrono::duration_cast<chrono::milliseconds>(tf-ti).count() << " milisegundos\n";
    cout << "Excentricidade: " << max << endl;
    cout << "Vértice para excentricidade: " << max_vertex << endl;
    return max;
}