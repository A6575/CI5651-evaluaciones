#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Clase para representar un grafo no dirigido
class Graph {
	int N; // Número de nodos
	vector<vector<int>> adj; // Lista de adyacencia
	// --- Variables para deteccion de Puentes ---
    vector<int> disc;  	// 'prenum'
    vector<int> low;   	// 'highest'
    vector<int> parent; // vector de padres
    int time;			// Tiempo global para detección de puentes
public:
	// constructor
	Graph(int nodos) {
		N = nodos;
		adj.resize(N);

        disc.resize(N, -1); // -1 significa "no visitado"
        low.resize(N, -1);
        parent.resize(N, -1); // -1 significa "sin padre"
        time = 0;
	}

	// función para agregar una arista al grafo
	void add_edge(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u); // Grafo no dirigido
	}

	// funcion para determinar si el grafo puede convertirse en fuertemente conexo
	// Un grafo no dirigido puede ser convertido en fuertemente conexo si y solo si
	// es conexo y no tiene puentes
	bool can_be_strongly_connected(){
		return is_connected() && !find_bridges(0);
	}
private:
	// función para realizar DFS de forma iterativa
	void dfs(int v, vector<bool>& visited) {
		stack<int> s;
		s.push(v);
		visited[v] = true;

		while (!s.empty()) {
			int node = s.top();
			s.pop();

			for (int neighbor : adj[node]) {
				if (!visited[neighbor]) {
					visited[neighbor] = true;
					s.push(neighbor);
				}
			}
		}
	}
	
	// función para realizar DFS y verificar que el grafo es conexo
	// Si todos los nodos son visitados, el grafo es conexo
	bool is_connected() {
		// Caso borde: 0 o 1 agente siempre es "conexo"
        if (N <= 1) {
            return true;
        }
		// Vector para rastrear nodos visitados
		vector<bool> visited(N, false);

		// Iniciar DFS desde el nodo 0
		dfs(0, visited);
		
		// Verificar si todos los nodos fueron visitados
		for (int i = 0; i < N; ++i) {
			if (!visited[i]) {
				// Encontramos un nodo no visitado
				return false; // El grafo NO es conexo
			}
		}
		return true;
	}

	// funcion para encontrar nodos puentes en el grafo
	// Retorna true si se encuentra al menos 1 puente
	bool find_bridges(int u) {
        // Inicializar el nodo 'u' con tiempo de descubrimiento y valor 'low'
        disc[u] = low[u] = ++time;

        // Iterar sobre los vecinos 'v' de 'u'
        for (int v : adj[u]) {
            
            // Caso 1: Si 'v' es el padre, ignorarlo
            if (v == parent[u]) {
                continue; 
            }

            // Caso 2: Si 'v' no ha sido visitado (es un hijo)
            if (disc[v] == -1) {
                // Poner a 'u' como su padre
                parent[v] = u;
                
                // Llamada recursiva (explorar al hijo)
				// Si se encuentra un puente en la llamada recursiva, retornar true
				if (find_bridges(v)) {
					return true;
				}

                // Actualizar 'low[u]' (heredar el atajo del hijo)
                low[u] = min(low[u], low[v]);

                // Comprobación del puente
                if (low[v] > disc[u]) {
                    return true;
                }
            } 
            // Caso 3: Si 'v' YA fue visitado (es un ancestro/back-edge)
            else {
                // Actualizar 'low[u]' usando el atajo a 'v'
                low[u] = min(low[u], disc[v]);
            }
        }
		// No se encontró ningún puente en este grafo
		return false;
    }
};

int main() {
	// Crear un grafo de ejemplo
	Graph G(5); // Nodos: 0, 1, 2, 3, 4
	// Grafo conexo sin puentes
	G.add_edge(0, 1);
	G.add_edge(1, 2);
	G.add_edge(2, 0);
	G.add_edge(2, 3);
	G.add_edge(3, 4);
	G.add_edge(4, 2);

	if (G.can_be_strongly_connected()){
		cout << "Sí existe un plan para cada encuentro que asegura que toda la información se comparta adecuadamente." << endl;
	}else{
		cout << "No existe un plan que asegure que toda la información se comparta adecuadamente." << endl;
	}
	
    return 0;
}