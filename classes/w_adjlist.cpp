#include "w_adjlist.h"

w_AdjList::w_AdjList(string FileLocation){
    // Construtor para a lista de Adjacências a partir de um arquivo externo
    // contendo o grafo

    ifstream GraphFile;
    GraphFile.open(FileLocation);

    // Lê a primeira linha do arquivo com o número de vértices
    GraphFile >> num_vertices;

    // Redimensiona os vetores de acordo com o tamanho da adjlista
    adjlist.resize(num_vertices);
    
    // Lê as linhas subsequentes no formato from, to para adicionar arestas ao grafo
    int from, to;
    double weight;
    num_edges = 0;
    while (GraphFile >> from >> to >> weight) {
        // Correção devido ao fato dos arquivos começarem com vértice 1
        addEdge(from-1, to-1, num_vertices, weight);
    }

    GraphFile.close();
}



void w_AdjList::addEdge(int from, int to, int num_vertices, double weight){
    // Insere um vértice novo na estrutura de dados

    if (to < num_vertices){
        AdjList_Tuple adjacent;
        adjacent.connected_vertex = to;
        adjacent.weight = weight; 

        adjlist[from].push_back(adjacent);

        adjacent.connected_vertex = from;
        adjacent.weight = weight;

        adjlist[to].push_back(adjacent); 
        num_edges++;   
    }
}



void w_AdjList::print(){
    // Printa no console a representação da lista de adjacência

    for (int i = 0; i < adjlist.size(); i++){
        cout << "Adjacency adjlist of vertex " << i << endl;

        for (list<AdjList_Tuple>::iterator it = adjlist[i].begin(); it != adjlist[i].end(); ++it)
            cout << " (" << it->connected_vertex << ", " << it->weight << ")";

        cout << endl;
    }

}



vector < double > w_AdjList::Dijkstra(int root){
    // Implementação do algoritmo de Dijkstra para apenas um vértice
    // Retorna o vetor de distâncias no final do Dijkstra do vértice escolhido para todos os outros

    // Corrige o erro de off by one
    root = root-1;  

    // Cria distâncias do maior valor possível (infinito)
    vector < double > dist (num_vertices, __DBL_MAX__);
    dist[root] = 0;

    // Cria o conjunto de vértices restantes para serem percorridos
    // Set faz a ordenação automática a partir do valor das distâncias
    set< pair<double, int> > remaining_vertices;
    remaining_vertices.insert( {0, root} );


    while (!remaining_vertices.empty()) {        
        
        // Escolhe os vértices de menor distância
        double current_dist = remaining_vertices.begin()->first;
        int current_vertex = remaining_vertices.begin()->second;

        // Remove o vértice do set, indicando que foi percorrido
        remaining_vertices.erase( {current_dist, current_vertex});

        // Itera sobre os vizinhos do vértice atual sendo percorrido
        for (list<AdjList_Tuple>::iterator it = adjlist[current_vertex].begin(); it != adjlist[current_vertex].end(); ++it){
            int neighbor = it->connected_vertex; 

            // Caso tenha achado um caminho melhor, ajusta a distância e insere no set
            if (dist[neighbor] > dist[current_vertex] + it->weight) {
                dist[neighbor] = dist[current_vertex] + it->weight;
                remaining_vertices.insert( {dist[neighbor], neighbor});
            }
        }
    }

    // Retorna o vetor das distâncias
    return dist;
}



vector < int > w_AdjList::findPathFromParent (vector < int > parent, int target){
    // Recebe o vetor de pais e calcula o caminho do vértice original até o vértice alvo

    vector < int > path;
    int iter = parent[target];
    path.push_back(iter);

    // Anda de pai a pai até achar um vértice sem pai (a raíz) escrevendo num vetor
    while (parent[iter] != -1) {
        iter = parent[iter];
        path.push_back(iter);
    }

    // Printa o vetor de trás pra frente seguindo assim o caminho raiz->alvo 
    for (int i = path.size()-1; i > -1; i--){
        //Ajusta o off by one
        cout << path[i]+1 << " ";
    }
    cout << target+1 << " " << endl;

    // Retorna vértice do caminho
    return path;
}

pair < double, vector <int> > w_AdjList::Dijkstra_target(int root, int target){
    // Implementação do algoritmo de Dijkstra para apenas um vértice
    // Double do pair representa a distância entre a raíz e o alvo
    // Retorna o caminho entre o vetor raíz e o alvo

    // Corrige erros de off by one
    root--;
    target--;

    // Cria distâncias do maior valor possível (infinito)
    vector < double > dist (num_vertices, __DBL_MAX__);
    dist[root] = 0;

    // Cria vetor com os pais dos vetores para fazer o caminho
    vector < int > parent (num_vertices, -1);
    
    // Cria o conjunto de vértices restantes para serem percorridos
    // Set faz a ordenação automática a partir do valor das distâncias
    set< pair<double, int> > remaining_vertices;
    remaining_vertices.insert( {0, root} );


    while (!remaining_vertices.empty()) {        
        
        // Escolhe os vértices de menor distância
        double current_dist = remaining_vertices.begin()->first;
        int current_vertex = remaining_vertices.begin()->second;

        // Checa se o vértice escolhido é o alvo
        // Se sim, retorna
        if (current_vertex == target) {
            pair < double, vector <int> > ans;
            ans.first = dist[current_vertex];
            ans.second = findPathFromParent(parent, target);
            return ans;
        }

        // Remove o vértice do set, indicando que foi percorrido
        remaining_vertices.erase( {current_dist, current_vertex});
        
        // Itera sobre os vizinhos do vértice atual sendo percorridos
        for (list<AdjList_Tuple>::iterator it = adjlist[current_vertex].begin(); it != adjlist[current_vertex].end(); ++it){
            int neighbor = it->connected_vertex; 

            // Caso tenha achado um caminho melhor, ajusta a distância, insere no set e estabelece o pai
            if (dist[neighbor] > dist[current_vertex] + it->weight) {
                dist[neighbor] = dist[current_vertex] + it->weight;
                remaining_vertices.insert( {dist[neighbor], neighbor});
                parent[neighbor] = current_vertex;
            }
        }
    }

    // Caso não tenha sido encontrado caminho, retorna -1 e o último caminho percorrido
    pair < double, vector <int> > ans;
    ans.first = -1;
    ans.second = findPathFromParent(parent, target);
    return ans;
}



double w_AdjList::Prim(int root, bool output = false){
    // Calcula a MST do grafo partindo do vértice root, retornando seu custo total
    // Se output for true, gera um arquivo MST.txt com a MST codificada

    // Corrige o erro de off by one
    root = root-1;  

    // Cria distâncias do maior valor possível (infinito)
    vector < double > cost (num_vertices, __DBL_MAX__);
    cost[root] = 0;

    // Cria vetor com os pais dos vetores para fazer o caminho
    vector < int > parent (num_vertices, -1);

    // Cria vetor indicando se o vértice escolhido já está na MST ou não
    vector < bool > inMST (num_vertices, false);
 
    // Cria o conjunto de vértices restantes para serem percorridos
    // Set faz a ordenação automática a partir do valor dos custos
    set< pair<double, int> > remaining_vertices;
    remaining_vertices.insert( {0, root} );
    

    while (!remaining_vertices.empty()){
        
        // Escolhe os vértices de menor distância
        double current_cost = remaining_vertices.begin()->first;
        int current_vertex = remaining_vertices.begin()->second;

        // Remove o vértice do set e marca, indicando que foi percorrido
        remaining_vertices.erase( {current_cost, current_vertex});
        inMST[current_vertex] = true;

        // Itera sobre os vizinhos do vértice atual sendo percorridos
        for (list<AdjList_Tuple>::iterator it = adjlist[current_vertex].begin(); it != adjlist[current_vertex].end(); ++it){
            int neighbor = it->connected_vertex; 

            // Caso tenha achado um custo melhor para um vértice fora da MST, ajusta a distância, insere no set e estabelece o pai
            if (cost[neighbor] > it->weight && inMST[neighbor] == false) {
                cost[neighbor] = it->weight;
                remaining_vertices.insert( {cost[neighbor], neighbor});
                parent[neighbor] = current_vertex;
            }
        }
    }

    // Se há pedido para gerar a MST em texto, chama a função de graph.cpp que trata
    if (output){
        outputMinimumSpanningTree(&parent[0], &cost[0]);
    }

    // Itera sobre o vetor de custo para achar o custo total
    double total_cost = 0;
    for (int i = 0; i < num_vertices; i++){
        total_cost += cost[i];
    }
    return total_cost;
}



pair < vector < double >, vector <int> > w_AdjList::Dijkstra_core(int root){
    // Dijkstra feito para ser chamado de dentro das funções
    // Retorna o vetor de distâncias e o vetor de pais
    // Como é chamado por uma função, não tem off by one


    // Cria distâncias do maior valor possível (infinito)
    vector < double > dist (num_vertices, __DBL_MAX__);
    dist[root] = 0;

    // Cria vetor para armazenar os pais dos vértices
    vector < int > parent (num_vertices, -1);

    // Cria o conjunto de vértices restantes para serem percorridos
    // Set faz a ordenação automática a partir do valor das distâncias
    set< pair<double, int> > remaining_vertices;
    remaining_vertices.insert( {0, root} );


    while (!remaining_vertices.empty()) {        
        
        // Escolhe os vértices de menor distância
        double current_dist = remaining_vertices.begin()->first;
        int current_vertex = remaining_vertices.begin()->second;

        // Remove o vértice do set, indicando que foi percorrido
        remaining_vertices.erase( {current_dist, current_vertex});

        // Itera sobre os vizinhos do vértice atual sendo percorrido
        for (list<AdjList_Tuple>::iterator it = adjlist[current_vertex].begin(); it != adjlist[current_vertex].end(); ++it){
            int neighbor = it->connected_vertex; 

            // Caso tenha achado um caminho melhor, ajusta a distância e insere no set
            if (dist[neighbor] > dist[current_vertex] + it->weight) {
                dist[neighbor] = dist[current_vertex] + it->weight;
                remaining_vertices.insert( {dist[neighbor], neighbor});
                parent[neighbor] = current_vertex;
            }
        }
    }

    // Retorna o vetor das distâncias e dos pais num pair
    pair < vector < double >, vector <int> > ans;
    ans.first = dist;
    ans.second = parent;
    return ans;
}



double w_AdjList::excentricity(int root){
    // Retorna a excentricidade do grafo no vértice

    // Corrige erros off by one
    root--;

    double max = 0;
    int max_vertex = -1;
    
    // Procura as distâncias para todos os vértices chamando Dijkstra
    vector <double> dist = Dijkstra_core(root).first;
    
    // Itera o vetor de distâncias procurando a distância máxima
    for (int vertex = 0; vertex < num_vertices; vertex++){
        if (dist[vertex] > max) {
            max = dist[vertex];
            max_vertex = vertex;
        }
    }

    return max;
}



double w_AdjList::medium_distance(){
    // Retorna a distância média do grafo fazendo Dijkstra em todos os pontos
    // Desconsidera para cálculo da soma de distâncias quando a distância for infinta

    double sum_of_distances = 0;
    double amount_of_distances = (num_vertices*(num_vertices-1))/2;
    
    // Itera calculando Dijkstra sobre todos os vértices do grafo
    for (int root = 0; root < num_vertices; root++){
        vector <double> dist = Dijkstra_core(root).first;

        // Itera sobre a distância de Dijkstra somando as distâncias
        // Começar o enlace em root evita cálculos redundantes
        for (int vertex = root; vertex < num_vertices; vertex++){
            if (dist[vertex] != __DBL_MAX__) {
                sum_of_distances += dist[vertex];
            }
        }
    }

    // Divide as distâncias pela quantidade de medidas
    double ans = (sum_of_distances / amount_of_distances);

    return ans;
}

double w_AdjList::medium_distance_probabilistic(int iterations){
    // Retorna uma estimativa para a distância média calculando multiplas vezes a partir de vértices aleatórios
    // Iterations estabelece quantas medidas vão ser tomadas

    // Estabelecendo a geração aleatória de vértices
    mt19937 rng;
    rng.seed(random_device()());
    uniform_int_distribution<mt19937::result_type> rand_vertex(1, getNumVertices()-1);

    double sum_of_distances = 0;
    double amount_of_distances = 0;

    // Pela quantidade de iterações oferecidas
    for (int i = 0; i < iterations; i++){

        // Calcula as distâncias a partir dos valores no Dijkstra
        vector <double> dist = Dijkstra_core(rand_vertex(rng)).first;
        for (int vertex = 0; vertex < num_vertices; vertex++){
            if (dist[vertex] != __DBL_MAX__) {
                sum_of_distances += dist[vertex];
                amount_of_distances++;
            }
        }
    }
    
    // Divide as distâncias pela quantidade de medidas
    double ans = (sum_of_distances / amount_of_distances);
    return ans;
}


int w_AdjList::vertexDegree(int vertex) {
    // Retorna o grau de um dado vértice

    int total = 0;
    
    // Itera sobre os vizinhos
    for (list<AdjList_Tuple>::iterator it = adjlist[vertex].begin(); it != adjlist[vertex].end(); ++it){
        total += 1;
    }
    return total; 
}

vector<int> w_AdjList::three_Max_Degrees() {
    // Encontra os 3 maiores vértices
    // Solução rápida e não expansível feita apenas para os estudos de caso
    
    // Vetor para armazenar os graus
    vector < int > degrees (num_vertices, -1);

    // Procura o maior grau
    int max1 = 0; 
    int i_max1 = -1; 
    for (int i = 0; i < num_vertices; i++) {
        degrees[i] = vertexDegree(i);
        if (degrees[i] > max1) {
            max1 = degrees[i];
            i_max1 = i;
        }
    }

    // Procura o maior grau dentre os que restam
    int max2 = 0;
    int i_max2 = -1;
    for (int i = 0; i < num_vertices; i++) {
        if (i != i_max1 && degrees[i] > max2) {
            max2 = degrees[i];
            i_max2 = i;
        }
    }

    // Procura o maior grau dentre os que restam
    int max3 = 0;
    int i_max3 = -1;
    for (int i = 0; i < num_vertices; i++) {
        if (i != i_max1 && i != i_max2 && degrees[i] > max3) {
            max3 = degrees[i];
            i_max3 = i;
        }
    }

    // Ajuste do off by one nos indices
    vector<int> answer {i_max1+1, i_max2+1, i_max3+1, max1, max2, max3};

    return answer;
}

void w_AdjList::print_neighbours(int vertex){
    // Printa os vizinhos de um vértice

    // Corrige o off by one
    vertex--;

    // Itera sobre os vizinhos, printando e corrigindo o off by one
    for (list<AdjList_Tuple>::iterator it = adjlist[vertex].begin(); it != adjlist[vertex].end(); ++it){
        cout << it->connected_vertex+1 << " ";
    }
    cout << endl;
}