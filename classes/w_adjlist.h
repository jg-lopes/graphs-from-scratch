#ifndef W_ADJLIST_H
#define W_ADJLIST_H

typedef struct AdjList_Tuple {
    int connected_vertex;
    double weight;
} AdjList_Tuple;

class w_AdjList: public Graph {
    public:
        w_AdjList(string FileLocation);
        // Construtor para a lista de Adjacências a partir de um arquivo externo contendo o grafo

        void addEdge(int from, int to, int num_vertices, double weight);
        // Insere uma aresta nova na estrutura de dados
        
        void print();
        // Printa no console a representação da lista de adjacência
        
        vector <double> Dijkstra(int root);
        // Implementação do algoritmo de Dijkstra para apenas um vértice
        // Retorna o vetor de distâncias no final do Dijkstra do vértice escolhido para todos os outros

        pair < double, vector <int> > Dijkstra_target(int root, int target);
        // Implementação do algoritmo de Dijkstra para apenas um vértice
        // Double do pair representa a distância entre a raíz e o alvo
        // Retorna o caminho entre o vetor raíz e o alvo
        
        double Prim(int root, bool output);
        // Calcula a MST do grafo partindo do vértice root, retornando seu custo total
        // Se output for true, gera um arquivo MST.txt com a MST codificada

        double excentricity(int root);
        // Retorna a excentricidade do grafo no vértice

        double medium_distance();
        // Retorna a distância média do grafo fazendo Dijkstra em todos os pontos
        // Desconsidera para cálculo da soma de distâncias quando a distância for infinta

        double medium_distance_probabilistic(int iterations);
        // Retorna uma estimativa para a distância média calculando multiplas vezes a partir de vértices aleatórios
        // Iterations estabelece quantas medidas vão ser tomadas

        int vertexDegree(int vertex);
        // Retorna o grau de um dado vértice

        vector<int> three_Max_Degrees();
        // Encontra os 3 maiores vértices
        // Solução rápida e não expansível feita apenas para os estudos de caso

        void print_neighbours(int vertex);
        // Printa os vizinhos de um vértice

    protected:
        vector < int > findPathFromParent (vector < int > parent, int target);
        // Recebe o vetor de pais e calcula o caminho do vértice original até o vértice alvo
    
    private:
        vector < list < AdjList_Tuple > > adjlist;
        // Estrutura de dados base

        pair < vector < double >, vector <int> > Dijkstra_core(int root);
        // Dijkstra feito para ser chamado de dentro das funções
        // Retorna o vetor de distâncias e o vetor de pais
        // Como é chamado por uma função, não tem off by one

};
 
#endif