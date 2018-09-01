#include <iostream>
#include <fstream>

using namespace std;

int readGraph(string FileLocation) {
    ifstream GraphFile;
    GraphFile.open(FileLocation);

    // Lê a primeira linha do arquivo com o número de vértices
    int num_vertex;
    GraphFile >> num_vertex;
    // PLACEHOLDER lógica de num de vertices

    // Lê as linhas subsequentes no formato a, b para adicionar arestas ao grafo
    int a, b;
    while (GraphFile >> a >> b) {
        // PLACEHOLDER lógica de adicionar aresta
    }

    GraphFile.close();
}

int readNumVertices (string FileLocation) {
    ifstream GraphFile;
    GraphFile.open(FileLocation);

    // Lê a primeira linha do arquivo com o número de vértices
    int num_vertex;
    GraphFile >> num_vertex;

    return num_vertex;
}
