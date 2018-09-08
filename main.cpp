#include "./classes/graph.h"

#include <chrono>
/* 
    TRABALHO DE GRAFOS
    Grupo: João Gabriel Lopes e Gustavo Machado
*/

 
int main() {
    Matrix graph("./graphs/tuturuu.txt", 0);
    graph.print();

    

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
