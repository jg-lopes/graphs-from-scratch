#include "./classes/graph.h"
 /* 
    TRABALHO DE GRAFOS
    Grupo: João Gabriel Lopes e Gustavo Machado

    1. Estudar erros de off by one no Djikstra e Prim
    2. Retorno do prim para um arquivo
    3. Dados relacionais
    
    5. Apresentação
    6. Relatório
    
 
*/

#include <random>

// Graph* createGraph(string file_location, int storage_type, int weighted){
//     Graph *graph;
//     switch (storage_type){
//         case 0:
//             if (weighted){
//                 w_Matrix matrix(file_location);
//                 graph = &matrix;
//             } else {
//                 Matrix matrix(file_location);
//                 graph = &matrix;
//             }
//         case 1:
//             if (weighted){
//                 w_AdjList matrix(file_location);
//                 graph = &matrix;
//             } else {
//                 w_AdjList matrix(file_location);
//                 graph = &matrix;
//             }
        
//     }
//     return graph;
// }

int main() {
    w_AdjList graph("./grafo_1.txt");
    //w_AdjList graph("./grafo_2.txt");
    //w_AdjList graph("./grafo_3.txt");
    //w_AdjList graph("./grafo_4.txt");
    //w_AdjList graph("./grafo_5.txt");

    for (int i = 1; i < 6; i++){
        cout << "Dijkstra entre vértices 1 e " << i*10 << endl;
        cout << "Caminho entre os pares:" << endl;
        double dist = graph.Dijkstra_target(1, i*10).first;
        cout << "Distância entre o par: " << dist << endl;
        cout << "---------------------------" << endl;
    }

    cout << endl << endl << endl;

    for (int i = 1; i < 6; i++){
        cout << "Excentricidade do vértice " << i*10 << endl;
        cout << "Valor da excentricidade: " << graph.excentricity(i*10) << endl;
        cout << "---------------------------" << endl;
    }


    cout << endl << endl << endl;


    mt19937 rng;
    rng.seed(random_device()());
    uniform_int_distribution<mt19937::result_type> rand_vertex(1, graph.getNumVertices());

    
    auto ti = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++){
        graph.excentricity(rand_vertex(rng));
    }
    auto tf = chrono::high_resolution_clock::now();
    cout << "Duração média da função: " << chrono::duration_cast<std::chrono::microseconds>(tf-ti).count()/100 << " microsegundos" << endl;




    cout << endl << endl << endl;




    cout << "Peso da árvore geradora mínima: " << graph.Prim(1) << endl;




    cout << endl << endl << endl;



    ti = chrono::high_resolution_clock::now();
    double mean_dist = graph.medium_distance();
    tf = chrono::high_resolution_clock::now();
    cout << "Distância média: " << mean_dist << endl;
    cout << "Duração da função: " << chrono::duration_cast<std::chrono::milliseconds>(tf-ti).count() << " milisegundos";


    // auto ti = chrono::high_resolution_clock::now();
    // auto tf = chrono::high_resolution_clock::now();
    // cout << "Duração da função: " << chrono::duration_cast<std::chrono::milliseconds>(tf-ti).count();
} 
