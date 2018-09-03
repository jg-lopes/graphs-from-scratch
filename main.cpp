#include "./classes/graph.cpp"
#include "./classes/matrix.cpp"
#include "./classes/adjlist.cpp"

/* 
    TRABALHO DE GRAFOS
    Grupo: João Gabriel Lopes e Gustavo Machado

    Fazer as medidas do estudo de caso
*/

 
int main() {
    Matrix graph("./graphs/as_graph.txt");
    graph.degreeInfo();

    graph.outputGraphInfo();
    graph.BFS(1);
    graph.connectedComponents();
} 
