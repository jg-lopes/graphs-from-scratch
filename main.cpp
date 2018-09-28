#include "./classes/graph.h"
 
#include <chrono>
/* 
    TRABALHO DE GRAFOS
    Grupo: João Gabriel Lopes e Gustavo Machado

    1. Fazer a estrutura capaz de reconhecer grafos de peso - OK
    2. Dijkstra e suas peculiaridades - Falta fazer o offset
    3. Prim
    4. Excentricidade vulgo que porra é essa
    5 Distância Média, nem conheço mas ja fede
*/

 
int main() {
    w_Matrix graph("./grafo_3.txt");
    graph.Dijkstra(1);

    

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
