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

    // Cria distâncias do maior valor possível (infinito)
    vector < double > dist (num_vertices, __DBL_MAX__);


    vector < bool > set (num_vertices, false); // Conjunto S
    int num_in_set = 0;

    dist[root] = 0;

    while (num_in_set != num_vertices) {        
        int u = distance_outside_set(dist, set, num_vertices);
        num_in_set++;
        set[u] = true;

        for (list<AdjList_Tuple>::iterator it = adjlist[u].begin(); it != adjlist[u].end(); ++it){
            int neighbor = it->connected_vertex; 
            if (dist[neighbor] > dist[u] + it->weight) {
                dist[neighbor] = dist[u] + it->weight;
            }
        }
    }
    
    for (int i = 0; i < num_vertices; i++){
        cout << dist[i] << " ";
    }
    cout << "\n";

}
