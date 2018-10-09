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
    
    // Corrige o erro de of by one
    root = root-1;  

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

vector < int > w_AdjList::findPathFromParent (vector < int > parent, int target){
    vector < int > path;
    int iter = parent[target];
    path.push_back(iter);
    while (parent[iter] != -1) {
        iter = parent[iter];
        path.push_back(iter);
    }

    for (int i = path.size()-1; i > -1; i--){
        //Ajusta o off by one
        cout << path[i]+1 << " ";
    }
    cout << target+1 << " " << endl;
    return path;
}

pair < double, vector <int> > w_AdjList::Dijkstra_target(int root, int target){
    // Calcula a menor distância entre dois vértices

    auto ti = chrono::high_resolution_clock::now();

    // Corrige erros off by one
    root--;
    target--;

    // Cria distâncias do maior valor possível (infinito)
    vector < double > dist (num_vertices, __DBL_MAX__);
    dist[root] = 0;

    vector < int > parent (num_vertices, -1);

    set< pair<double, int> > remaining_vertices;
    remaining_vertices.insert( {0, root} );


    while (!remaining_vertices.empty()) {        
        
        double current_dist = remaining_vertices.begin()->first;
        int current_vertex = remaining_vertices.begin()->second;
        if (current_vertex == target) {
            auto tf = chrono::high_resolution_clock::now();
            //cout << "Duração da função: " << chrono::duration_cast<chrono::milliseconds>(tf-ti).count() << " milisegundos\n";
            pair < double, vector <int> > ans;
            ans.first = dist[current_vertex];
            ans.second = findPathFromParent(parent, target);
            return ans;
        }

        remaining_vertices.erase( {current_dist, current_vertex});

        for (list<AdjList_Tuple>::iterator it = adjlist[current_vertex].begin(); it != adjlist[current_vertex].end(); ++it){
            int neighbor = it->connected_vertex; 
            if (dist[neighbor] > dist[current_vertex] + it->weight) {
                dist[neighbor] = dist[current_vertex] + it->weight;
                remaining_vertices.insert( {dist[neighbor], neighbor});
                parent[neighbor] = current_vertex;
            }
        }
    }
    auto tf = chrono::high_resolution_clock::now();
    //cout << "Duração da função: " << chrono::duration_cast<chrono::milliseconds>(tf-ti).count() << " milisegundos\n";    
    
    
    pair < double, vector <int> > ans;
    ans.first = -1;
    ans.second = findPathFromParent(parent, target);
    return ans;
}



double w_AdjList::Prim(int root){
    //auto ti = chrono::high_resolution_clock::now();

    // Corrige o erro de of by one
    root = root-1;  

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

    double total_cost = 0;
    for (int i = 0; i < num_vertices; i++){
        if (cost[i] != __DBL_MAX__){
            total_cost += cost[i];
        }
    }
    return total_cost;
}



pair < vector < double >, vector <int> > w_AdjList::Dijkstra_core(int root){
    // CHAMADO DE DENTRO DAS FUNÇÕES, NÃO TEM OFF BY ONE


    // Cria distâncias do maior valor possível (infinito)
    vector < double > dist (num_vertices, __DBL_MAX__);
    dist[root] = 0;

    // Cria vetor para armazenar os pais dos vértices
    vector < int > parent (num_vertices, -1);

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
                parent[neighbor] = current_vertex;
            }
        }
    }
    pair < vector < double >, vector <int> > ans;
    ans.first = dist;
    ans.second = parent;
    return ans;
}



double w_AdjList::excentricity(int root){
    //auto ti = chrono::high_resolution_clock::now();
    
    // Corrige erros off by one
    root--;

    double max = 0;
    int max_vertex = -1;
    

    vector <double> dist = Dijkstra_core(root).first;
    
    for (int vertex = 0; vertex < num_vertices; vertex++){
        if (dist[vertex] > max) {
            max = dist[vertex];
            max_vertex = vertex;
        }
    }

    //auto tf = chrono::high_resolution_clock::now();
    //cout << "Duração da função: " << chrono::duration_cast<chrono::milliseconds>(tf-ti).count() << " milisegundos\n";
    //cout << "Excentricidade: " << max << endl;
    //cout << "Vértice para excentricidade: " << max_vertex << endl;
    return max;
}



double w_AdjList::medium_distance(){
    double sum_of_distances = 0;
    double amount_of_distances = (num_vertices*(num_vertices-1))/2;
    
    for (int root = 0; root < num_vertices; root++){
        vector <double> dist = Dijkstra_core(root).first;
        //cout << root << endl;
        for (int vertex = root; vertex < num_vertices; vertex++){
            if (dist[vertex] != __DBL_MAX__) {
                sum_of_distances += dist[vertex];
            }
        }
    }
    double ans = (sum_of_distances / amount_of_distances);

    return ans;
}