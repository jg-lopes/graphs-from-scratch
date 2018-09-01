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
    while (GraphFile >> from >> to) {
        // Correção devido ao fato dos arquivos começarem com vértice 1
        addEdge(from-1, to-1);
    }

    GraphFile.close();
}

void AdjList::addEdge(int from, int to){

    adjlist[from].push_back(to);
    adjlist[to].push_back(from);    
}

void AdjList::print(){

    for (int i = 0; i < adjlist.size(); i++){
        cout << "Adjacency adjlist of vertex " << i << endl;

        for (list<int>::iterator it = adjlist[i].begin(); it != adjlist[i].end(); ++it)
            cout << ' ' << *it;

        cout << endl;
    }

}