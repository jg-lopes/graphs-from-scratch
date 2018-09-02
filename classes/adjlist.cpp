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
