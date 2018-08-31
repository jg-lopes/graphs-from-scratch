#include "./classes/graph.cpp"

#include "./classes/matrix.cpp"

/* 
    TRABALHO DE GRAFOS
    Grupo: João Gabriel Lopes e Gustavo Machado

    Ideia:
    1. Lê o arquivo a partir de um programa de I/O que vai separar as informações úteis - OK
        1.1 - Interfacear isso com a estrutura
    2. Armazena as informações na classe Grafo onde será feito a organização em estrutura de dados
        2.1 - Matriz - DONE
        2.2 - AdjList - NOT DONE
    3. Execute os algoritmos pedidos
*/

/*
    1. Estruturas de dados em C funcionam (vector, stack, etc.)
    2. OOP em C funciona
*/

// void createGraph(string FileLocation, int type, Matrix* graph, AdjList* graph2) {
//     switch (type) {
//         case 1:
//             Matrix graph(string FileLocation);
//         case 2:
//             //AdjList graph(string FileLocation);
//     }
// }

int main() {
    Matrix graph("graph.txt");
    //graph.printMatrix();
}  