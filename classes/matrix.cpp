#include "matrix.h"

Matrix::Matrix(string FileLocation){
    GraphName = FileLocation;

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


int Matrix::vertexDegree(int vertex) {
    int total = 0;
    for (int i = 0; i < matrix.size(); i++) {
        total += matrix[vertex][i];
    }
    return total; 
}
 
vector<float> Matrix::edgeInfo() { 
    // Retorna min, máx, média e mediana em um vector respectivamente

    vector < int > degrees (num_vertices, -1);

    int sum_degrees = 0;

    for (int i = 0; i < num_vertices; i++) {
        degrees[i] = vertexDegree(i);
        sum_degrees += vertexDegree(i);
    }

    // VectorMinMax é uma função auxiliar definida em graph.cpp
    vector<int> min_max = VectorMinMax(degrees);


    int min = min_max[0];
    int max = min_max[1];
    float mean = (float) sum_degrees / (float) num_vertices;

    // Inicializa cálculo da mediana
    float median = 0;
    

    while (degrees.size() > 2) {
        degrees.erase(degrees.begin() + min_max[2]);
        degrees.erase(degrees.begin() + min_max[3]);
        min_max = VectorMinMax(degrees);
    }

    
    if (degrees.size() == 2) {
        median = (degrees[0] + degrees[1])/2;
    } else {
        median = degrees[0];
    }

    vector <float> answer {(float) min, (float) max, mean, median};

    return answer;
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
    vector < int > father (num_vertices, -1);

    // Vetor de níveis do vector
    // Valor -1 = Não descoberto
    vector < int > level (num_vertices, -1);

    queue < int > fifo;

    discovered[root] = 1;
    // Está com base 0, vai ser corrigido quando for base[1]
    father[root] = -1;
    level[root] = 0;

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
                    father[neighbor] = vertex;
                    level[neighbor] = level[vertex] + 1;

                    fifo.push(neighbor);
                }
            }
        }
    }

    outputSpanningTree(&father[0], &level[0]);

}

void Matrix::DFS(int root) {
    //Correção
    root -= 1;
    
    vector < int > discovered (num_vertices, 0);
    vector < int > father (num_vertices, -2);
    vector < int > level (num_vertices, -1);

    stack < int > lifo;

    father[root] = -1;
    level[root] = 0;

    lifo.push(root);
    
    while (!lifo.empty()) {
        
        int vertex = lifo.top();
        lifo.pop();

        if (discovered[vertex] == 0) {
            discovered[vertex] = 1;
            
            for (int i = 0; i < num_vertices; i++){
                if (matrix[vertex][i] == 1){
                    if (father[i] == -2){
                        father[i] = vertex;
                    }
                    if (level[i] == -1) {

                        level[i] = level[vertex] + 1;
                    }
                    lifo.push(i);
                }
            } 
        }
    }

    outputSpanningTree(&father[0], &level[0]);

}