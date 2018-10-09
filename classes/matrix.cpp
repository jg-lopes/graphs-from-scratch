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
    num_edges = 0;

    while (GraphFile >> from >> to) {
    // Correção devido ao fato dos arquivos começarem com vértice 1
        addEdge(from-1, to-1, num_vertices);
    }
    
    GraphFile.close();
}

void Matrix::addEdge(int from, int to, int num_vertices){
    // Insere um vértice na estrutura

    if (to < num_vertices){
        matrix[from][to] = 1;
        num_edges++;
    }
}


int Matrix::vertexDegree(int vertex) {
    // Retorna o grau do vértice na Matriz

    int total = 0;
    for (int i = 0; i < matrix.size(); i++) {
        total += matrix[vertex][i];
    }
    return total; 
}
 
vector<float> Matrix::degreeInfo() { 
    // Retorna min, máx, média e mediana em um vector respectivamente
    // Calcula o valor no atributo edge_info e o retorna
 
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
    
    sort(degrees.begin(), degrees.end());

    int pivot = degrees.size()/2;
    if (degrees.size() % 2 == 0) {
        median = (degrees[pivot] + degrees[pivot-1]) / 2;
    } else {
        median = degrees[pivot];
    }

    vector <float> answer {(float) min, (float) max, mean, median};

    edge_info = answer;

    return edge_info;
}

void Matrix::print(){
    // Printa no console a representação da matriz

    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix[i].size(); j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void Matrix::BFS(int root){
    // Executa a BFS no grafo a partir de um vérice raiz
    // Retorna a árvore geradora no arquivo spanning_tree.txt

    //Correção para base 0
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

    // Vetor de níveis do grafo
    // Valor -1 = Não descoberto
    vector < int > level (num_vertices, -1);

    queue < int > fifo;

    discovered[root] = 1;
    father[root] = 0;
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
                    level[neighbor] = level[vertex] + 1;

                    // Correção devido ao arquivo começar em vértice 1
                    father[neighbor] = vertex + 1;
                    

                    fifo.push(neighbor);
                }
            }
        }
    }

    outputSpanningTree(&father[0], &level[0]);

}

void Matrix::DFS(int root) {
    // Executa a BFS no grafo a partir de um vérice raiz
    // Retorna a árvore geradora no arquivo spanning_tree.txt

    //Correção para base 0
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

    // Vetor de níveis do grafo
    // Valor -1 = Não descoberto
    vector < int > level (num_vertices, -1);

    stack < int > lifo;

    father[root] = 0;
    level[root] = 0;

    lifo.push(root);
    
    while (!lifo.empty()) {
        
        int vertex = lifo.top();
        lifo.pop();

        if (discovered[vertex] == 0) {
            discovered[vertex] = 1;
            
            for (int i = 0; i < num_vertices; i++){
                if (matrix[vertex][i] == 1){
                    if (father[i] == -1){
                        // Correção devido ao arquivo começar em vértice 1
                        father[i] = vertex + 1;
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

vector<int> Matrix::BFS_core(int root, vector<int> &discovered) {
    // Coração da BFS, usado no código de componentes conexos
       
    vector < int > component_vectors;
    component_vectors.insert(component_vectors.end(), root);
    queue <int> fifo;

    discovered[root] = 1;
    fifo.push(root);

    while (!fifo.empty()) {

        int vertex = fifo.front();
        fifo.pop();

        for (int i = 0; i < num_vertices; i++){
            if (matrix[vertex][i] == 1){
                int neighbor = i;

                if (discovered[neighbor] == 0) {
                    discovered[neighbor] = 1;
                    component_vectors.insert(component_vectors.end(), neighbor);
                    fifo.push(neighbor);
                }
            }
        }        
    }

    return component_vectors;
}

int Matrix::connectedComponents() {
    // Calcula os componentes conexos do Grafo
    // Retorna os componentes no arquivo connected_components.txt
    
    vector <int> discovered (num_vertices, 0);
    
    vector < vector <int> > verticesComponent;

    int num_components = 0;

    for(int i = 0; i < num_vertices; i++) {

        if (discovered[i] == 0) {
            verticesComponent.insert(verticesComponent.end(), BFS_core(i , discovered));       
            num_components += 1;
        }
    }

    outputConnectedComponents(verticesComponent);
    return verticesComponent.size();
}