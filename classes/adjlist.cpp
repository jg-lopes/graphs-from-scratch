#include "adjlist.h"

AdjList::AdjList(string FileLocation){
    GraphName = FileLocation;

    ifstream GraphFile;
    GraphFile.open(FileLocation);

    // Lê a primeira linha do arquivo com o número de vértices
    GraphFile >> num_vertices;

    // Redimensiona os vetores de acordo com o tamanho da adjlista
    adjlist.resize(num_vertices);
    
    // Lê as linhas subsequentes no formato from, to para adicionar arestas ao grafo
    int from, to;
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
    }
}

int AdjList::vertexDegree(int vertex) {
    int total = 0;
    for (list<int>::iterator it = adjlist[vertex].begin(); it != adjlist[vertex].end(); ++it) {
        total += 1;
    }
    // Correção para cálculo de duas arestas
    return total; 
}

vector<float> AdjList::edgeInfo() { 
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

    // while (degrees.size() > 2) {
    //     degrees.erase(degrees.begin() + min_max[2]);
    //     degrees.erase(degrees.begin() + min_max[3]);
    //     min_max = VectorMinMax(degrees);
    // }

    
    // if (degrees.size() == 2) {
    //     median = (degrees[0] + degrees[1])/2;
    // } else {
    //     median = degrees[0];
    // }

    vector <float> answer {(float) min, (float) max, mean, median};

    return answer;
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
    //Compare
    root -= 1;

    vector <int> discovered (num_vertices, 0);
    vector <int> father (num_vertices, -1);
    vector <int> level (num_vertices, -1);

    queue <int> fifo;

    discovered[root] = 1;
    father[root] = -1;
    level[root] = 0;

    fifo.push(root);

    while (!fifo.empty()) {

        int vertex = fifo.front();
        fifo.pop();

        for (list<int>::iterator it = adjlist[vertex].begin(); it != adjlist[vertex].end(); ++it){
            int neighbor = *it;

            if (discovered[neighbor] == 0) {
                discovered[neighbor] = 1;
                father[neighbor] = vertex;
                level[neighbor] = level[vertex] + 1;

                fifo.push(neighbor);
            }
        }        
    }

    outputSpanningTree(&father[0], &level[0]);

}

void AdjList::DFS(int root) {

    //Correção
    root -= 1;

    vector < int > discovered (num_vertices, 0);
    vector < int > father (num_vertices, -2);
    vector < int > level (num_vertices, -1);


    stack < int > lifo;

    father[root] = -1;
    level[root] = 0;

    lifo.push(root);

    while(!lifo.empty()) {

        int vertex = lifo.top();
        lifo.pop();

        if (discovered[vertex] == 0 ) {
            discovered[vertex] = 1;          

            for (list<int>::iterator it = adjlist[vertex].begin(); it != adjlist[vertex].end(); ++it){
                    if (father[*it] == -2){
                        father[*it] = vertex;
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
