#include "./classes/graph.cpp"

#include "./classes/matrix.cpp"
#include "./classes/adjlist.cpp"

/* 
    TRABALHO DE GRAFOS
    Grupo: João Gabriel Lopes e Gustavo Machado

    Ideia:
    1. Lê o arquivo a partir de um programa de I/O que vai separar as informações úteis - OK
        1.1 - Interfacear isso com a estrutura
    2. Armazena as informações na classe Grafo onde será feito a organização em estrutura de dados
        2.1 - Matriz - DONE
        2.2 - AdjList - DONE
    
    3. Execute os algoritmos pedidos
        3.1 BFS e DFS
        3.2 Testar conexo
        3.3 Grau mínimo, médio etc.
*/

int main() {
    AdjList graph("./graphs/tuturuu.txt");
    graph.DFS(5);
} 
