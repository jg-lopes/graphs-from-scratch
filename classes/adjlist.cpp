#include "adjlist.h"

AdjList::AdjList(string FileLocation){
    ifstream GraphFile;
    GraphFile.open(FileLocation);

    // Lê a primeira linha do arquivo com o número de vértices
    GraphFile >> num_vertices;

    // Redimensiona os vetores de acordo com o tamanho da adjlista
    adjlist.resize(num_vertices);
    
    // Lê as linhas subsequentes no formato from, to para adicionar arestas ao grafo
    int from, to;
    num_edges = 0;
    while (GraphFile >> from >> to) {
        // Correção devido ao fato dos arquivos começarem com vértice 1
        addEdge(from-1, to-1, num_vertices);
    }

    GraphFile.close();
}

void AdjList::addEdge(int from, int to, int num_vertices){
    
    if (to < num_vertices){
        adjlist[from].push_back(to);
        adjlist[to].push_back(from); 
        num_edges++;   
    }
}

int AdjList::vertexDegree(int vertex) {
    // Retorna o grau de um dado vértice

    int total = 0;
    for (list<int>::iterator it = adjlist[vertex].begin(); it != adjlist[vertex].end(); ++it) {
        total += 1;
    }
    return total; 
}

vector<float> AdjList::degreeInfo() { 
    // Retorna min, máx, média e mediana em um vector respectivamente

    vector < int > degrees (num_vertices, -1);

    int sum_degrees = 0;

    for (int i = 0; i < num_vertices; i++) {
        degrees[i] = vertexDegree(i);
        sum_degrees += vertexDegree(i);
    }

    // VectorMinMax é uma função auxiliar definida em graph.cpp
    vector<int> min_max = VectorMinMax(degrees);


    int min = min_max[0];
    int max = min_max[1];
    float mean = (float) sum_degrees / (float) num_vertices;

    // Inicializa cálculo da mediana
    float median = 0;
    
    sort(degrees.begin(), degrees.end());

    int pivot = degrees.size()/2;
    if (degrees.size() % 2 == 0) {
        median = (degrees[pivot] + degrees[pivot-1]) / 2;
    } else {
        median = degrees[pivot];
    }

    vector <float> answer {(float) min, (float) max, mean, median};

    edge_info = answer;

    return edge_info;
}

void AdjList::print(){
    for (int i = 0; i < adjlist.size(); i++){
        cout << "Adjacency adjlist of vertex " << i << endl;

        for (list<int>::iterator it = adjlist[i].begin(); it != adjlist[i].end(); ++it)
            cout << ' ' << *it;

        cout << endl;
    }

}

void AdjList::BFS(int root) {
    
    root -= 1;

    vector <int> discovered (num_vertices, 0);
    vector <int> father (num_vertices, -1);
    vector <int> level (num_vertices, -1);

    queue <int> fifo;

    discovered[root] = 1;
    father[root] = 0;
    level[root] = 0;

    fifo.push(root);

    while (!fifo.empty()) {

        int vertex = fifo.front();
        fifo.pop();

        for (list<int>::iterator it = adjlist[vertex].begin(); it != adjlist[vertex].end(); ++it){
            int neighbor = *it;

            if (discovered[neighbor] == 0) {
                discovered[neighbor] = 1;
                father[neighbor] = vertex + 1;
                level[neighbor] = level[vertex] + 1;

                fifo.push(neighbor);
            }
        }        
    }
    //outputSpanningTree(&father[0], &level[0]);
}

void AdjList::DFS(int root) {

    //Correção
    root -= 1;

    vector < int > discovered (num_vertices, 0);
    vector < int > father (num_vertices, -1);
    vector < int > level (num_vertices, -1);


    stack < int > lifo;

    father[root] = 0;
    level[root] = 0;

    lifo.push(root);

    while(!lifo.empty()) {

        int vertex = lifo.top();
        lifo.pop();

        if (discovered[vertex] == 0 ) {
            discovered[vertex] = 1;          

            for (list<int>::iterator it = adjlist[vertex].begin(); it != adjlist[vertex].end(); ++it){
                    if (father[*it] == -1){
                        father[*it] = vertex + 1;
                    }
                    if (level[*it] == -1) {

                        level[*it] = level[vertex] + 1;
                    }
                    lifo.push(*it);

            }
            
        }
    }

    outputSpanningTree(&father[0], &level[0]);

}

vector<int> AdjList::BFS_core(int root, vector<int> &discovered) {
    // Coração da BFS, usado no código de componentes conexos
       
    vector < int > component_vectors;
    component_vectors.insert(component_vectors.end(), root);
    queue <int> fifo;

    discovered[root] = 1;
    fifo.push(root);

    while (!fifo.empty()) {

        int vertex = fifo.front();
        fifo.pop();

        for (list<int>::iterator it = adjlist[vertex].begin(); it != adjlist[vertex].end(); ++it){
            int neighbor = *it;

            if (discovered[neighbor] == 0) {
                discovered[neighbor] = 1;
                component_vectors.insert(component_vectors.end(), neighbor);
                fifo.push(neighbor);
            }
        }        
    }

    return component_vectors;
}

int AdjList::connectedComponents() {
    // Calcula os componentes conexos do Grafo
    // Retorna os componentes no arquivo connected_components.txt

    vector <int> discovered (num_vertices, 0);
    
    vector < vector <int> > verticesComponent;

    int num_components = 0;

    for(int i = 0; i < num_vertices; i++) {

        if (discovered[i] == 0) {
            verticesComponent.insert(verticesComponent.end(), BFS_core(i , discovered));       
            num_components += 1;
        }
    }

    outputConnectedComponents(verticesComponent);
    return verticesComponent.size();
}
