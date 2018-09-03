#include "./classes/graph.cpp"
#include "./classes/matrix.cpp"
#include "./classes/adjlist.cpp"

/* 
    TRABALHO DE GRAFOS
    Grupo: João Gabriel Lopes e Gustavo Machado
*/

 
int main() {
    AdjList graph("./graphs/live_journal.txt");
    graph.degreeInfo();

    graph.outputGraphInfo();
    graph.BFS(15000);
    graph.connectedComponents();
} 
