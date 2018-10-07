#include "./classes/graph.h"
 /* 
    TRABALHO DE GRAFOS
    Grupo: João Gabriel Lopes e Gustavo Machado

    1. Estudar erros de off by one no Djikstra e Prim
    2. Corretude do Djikstra e prim
    3. Corretude da excentricidade
    5 Distância Média, nem conheço mas ja fede
*/

 
int main() {
    w_AdjList adjlist("./grafo_5.txt");
    adjlist.excentricity(1);

    
    // for (int i = 0; i < 15; i++){
    //      cout << adjlist.Dijkstra_target(1, i) << endl;
    // }

    // auto ti = chrono::high_resolution_clock::now();
    // for (int i = 1; i < 11; i++){
    //     auto t1 = chrono::high_resolution_clock::now();
    //     graph.BFS(i);
    //     auto t2 = chrono::high_resolution_clock::now();
    //     cout << "Tempo parcial do vértice " << i << ": " << chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
    // }

    // auto tf = chrono::high_resolution_clock::now();
    // cout << "Duração da função: " << chrono::duration_cast<std::chrono::milliseconds>(tf-ti).count();
} 
