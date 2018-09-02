#include "matrix.h"

Matrix::Matrix(string FileLocation){
    ifstream GraphFile;
    GraphFile.open(FileLocation);

    // Lê a primeira linha do arquivo com o número de vértices
    GraphFile >> num_vertices;

    // Redimensiona os vetores de acordo com o tamanho da lista
    matrix.resize(num_vertices);
    for (int i = 0; i < num_vertices; i++){
        matrix[i].resize(num_vertices);
    };

    // Lê as linhas subsequentes no formato from, to para adicionar arestas ao grafo
    int from, to;
    while (GraphFile >> from >> to) {
        // Correção devido ao fato dos arquivos começarem com vértice 1
        addEdge(from-1, to-1, num_vertices);
    }

    GraphFile.close();
}
 
void Matrix::addEdge(int from, int to, int num_vertices){
    if (to < num_vertices){
        matrix[from][to] = 1;
        matrix[to][from] = 1;
    }
}

void Matrix::print(){
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix[i].size(); j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void Matrix::BFS(int root){
    //Correção
    root -= 1; 

    //Vetor de Marcação
    //Índice = Número do Vértice 
    //Valor 0 = Desconhecido; Valor 1 = Descoberto;
    vector < int > discovered (num_vertices, 0);

    // Vetor de pais de um vértice
    // Índice = Número do Vértice
    // Valor = Vértice Pai
    // Exceções: Valor 0 = Raiz; Valor -1 = Não descoberto
    //vector < int > father (num_vertices, -1);

    // Vetor de níveis do vector
    // Valor -1 = Não descoberto
    //vector < int > level (10, -1);

    queue < int > fifo;


    // Corrigindo para fazer início em 0
    discovered[root] = 1;
    //father[root] = 0;
    //level[root] = 0;

    int vertices_percorridos = 1;

    fifo.push(root);


    while (!fifo.empty()){
        
        int vertex = fifo.front();
        fifo.pop();

        for (int i = 0; i < num_vertices; i++){
            
            //Procura vértices vizinhos
            if (matrix[vertex][i] == 1){
                int neighbor = i;
                
                if (discovered[neighbor] == 0){
                    discovered[neighbor] = 1;
                    fifo.push(neighbor);
                }
            }
        }
    }
}

void Matrix::DFS(int root) {
    //Correção
    root -= 1;
    
    vector < int > discovered (num_vertices, 0);

    stack < int > lifo;

    lifo.push(root);
    
    while (!lifo.empty()) {
        
        int vertex = lifo.top();
        lifo.pop();

        if (discovered[vertex] == 0) {
            discovered[vertex] = 1;
            
            for (int i = 0; i < num_vertices; i++){
                if (matrix[vertex][i] == 1){
                    lifo.push(i);
                }
            } 
        }
    }
}