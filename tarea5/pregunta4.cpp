/*
 * Nota sobre la implementación del algoritmo de Emparejamiento Máximo:
 *
 * Este código NO crea los nodos 's' (fuente) y 't' (sumidero) explícitamente,
 * sino que implementa sus roles de forma implícita:
 *
 * 		1. El rol del nodo fuente lo cumple el bucle 'for' principal en
 * 		`find_min_elements_to_remove`. Al iterar por cada nodo impar 'i'
 * 		y llamar a `dfs_match(i)`, se "ofrece" un camino (flujo)
 * 		desde la fuente a cada nodo impar, uno por uno.
 *
 * 		2. El rol del nodo sumidero lo cumple la condición base dentro
 * 		de `dfs_match`. Cuando se encuentra un nodo par 'v' que está libre
 * 		(es decir, `matchR[v] == -1`), se ha encontrado un "camino aumentante"
 * 		completo. Esto es equivalente a encontrar un camino que llega
 * 		exitosamente hasta el sumidero 't'.
 */
/*
 * Nota sobre la implementación y la Teoría de Flujo Máximo (Hopcroft-Karp):
 *
 * Este código NO crea 's' y 't' explícitamente, sino que implementa
 * sus roles de forma implícita, repartiéndolos entre las dos fases
 * del algoritmo (BFS y DFS):
 *
 * 1. El rol de la 'Fuente' (s): Lo cumple la función `bfs_hopcroft` (Paso 1).
 * Al buscar *todos* los nodos impares libres (`matchL[i] == -1`) y ponerlos
 * en la cola inicial con `dist = 0`, esta función actúa como una
 * super-fuente que "ofrece" un camino (flujo) a todos los nodos 'L'
 * (impares) a la vez, construyendo un "grafo de capas" (layer graph).
 *
 * 2. El rol del 'Sumidero' (t): Este rol se divide en dos:
 * a) El BFS lo *detecta*: Cuando el `bfs_hopcroft` encuentra un nodo par
 * libre (`matchR[v] == -1`), sabe que ha encontrado un camino
 * aumentante que llega al sumidero (y por eso devuelve `true`).
 *
 * b) El DFS lo *usa*: El caso base de éxito para `dfs_hopcroft` (Paso 2)
 * es también encontrar un nodo par libre (`matchR[v] == -1`),
 * que representa el paso final para "reclamar" ese camino y
 * "enviar el flujo" hasta el sumidero.
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Funcion auxiliar para verificar si un número es primo
bool is_prime(int n) {
    
    // 0 y 1 no son primos
    if (n <= 1) {
        return false; 
    }

    // Se empieza el bucle en i = 2 
    // y se itera hasta la raíz cuadrada de n
    for (int i = 2; i * i <= n; ++i) {
        // Si encontramos un divisor, no es primo
        if (n % i == 0) {
            return false;
        }
    }
    
    // Si el bucle termina sin encontrar ningún divisor,
    // entonces n debe ser primo
    return true;
}

// Función para separar el conjunto C en pares e impares
void separate_set(const vector<int>& C, vector<int>& par, vector<int>& impar) {
	for (int num : C) {
		if (num % 2 == 0){
			par.push_back(num);
		}else{
			impar.push_back(num);
		}
	}
}

// Función para construir el grafo bipartito entre impares y pares con bases en la suma prima
vector<vector<int>> build_bipartite_graph(const vector<int>& impares, const vector<int>& pares) {
	int N_impares = impares.size();
	int N_pares = pares.size();

	// Se crea una lista de adyacencia para el lado A (impares)
	// El tamaño es el número de nodos impares
	vector<vector<int>> adj(N_impares); 

	for (int i = 0; i < N_impares; ++i) { // 'i' es el índice del impar
		for (int j = 0; j < N_pares; ++j) { // 'j' es el índice del par
			
			// Se verifica si la suma es prima
			if (is_prime(impares[i] + pares[j])) {
				
				// Se conecta el nodo impar 'i' con el nodo par 'j'
				adj[i].push_back(j);
			}
		}
	}

	return adj;
}

// Funcion de bfs para el algoritmo de hopcroft
bool bfs_hopcroft(int N_impares, const vector<vector<int>>& adj, const vector<int>& matchL, const vector<int>& matchR, vector<int>& dist) {
    // Resetear distancias y crear cola
    fill(dist.begin(), dist.end(), -1); // -1 indica camino no calculado
    queue<int> q;

    // Inicializacion de la cola
    for (int i = 0; i < N_impares; ++i) {
        if (matchL[i] == -1) { // Verificar que el nodo 'i' (impar) está libre
            q.push(i);
            dist[i] = 0; // Establecer distancia 0
        }
    }

    bool path_found = false;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // Itera por vecinos 'v' (pares)
        for (int v : adj[u]) {
            int old_u = matchR[v]; // El impar con el que 'v' está emparejado

            // Si 'v' está emparejado (old_u != -1) Y
            // todavía no se ha visitado a 'old_u' (dist[old_u] == -1)
            if (old_u != -1 && dist[old_u] == -1) {
                // Se pone a 'old_u' en la siguiente capa
                dist[old_u] = dist[u] + 1;
                q.push(old_u); // Y se agrega a la cola
            } else if (old_u == -1) {
                // Si 'v' está LIBRE (old_u == -1), significa que
                // se encontro un camino
                path_found = true;
            }
        }
    }
    // Devuelve true si se encontró CUALQUIER camino
    return path_found;
}

// Funcion de dfs para el algoritmo de hopcroft
bool dfs_hopcroft(int u, const vector<vector<int>>& adj, vector<int>& matchL, vector<int>& matchR, const vector<int>& dist) {
    // Itera por todos los vecinos 'v' (pares) de 'u'
    for (int v : adj[u]) {
        // 'old_u' es el nodo impar con el que 'v' está emparejado
        int old_u = matchR[v]; 

        // Si 'v' está libre (el final del camino)
        if (old_u == -1) {
            // Se empareja u y v
            matchL[u] = v;
            matchR[v] = u;
            return true;
        }

        // Si 'v' está ocupado por 'old_u'
        // Se comprueba la condición de capas:
        if (dist[old_u] == dist[u] + 1) {
            // Si la llamada recursiva tiene éxito (old_u encontró otra pareja)
            if (dfs_hopcroft(old_u, adj, matchL, matchR, dist)) {
                // Entonces se puede emparejar u y v
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
    }
    // No se pudo encontrar un camino desde 'u'
    return false;
}

/**
 * Función principal para resolver el problema.
 */
int find_min_elements_to_remove(const vector<int>& C) {

    // Separar en pares e impares
    vector<int> impares;
    vector<int> pares;

    separate_set(C, pares, impares);

	// Generar el grafo bipartito
	int N_impares = impares.size();
	int N_pares = pares.size();

    vector<vector<int>> adj = build_bipartite_graph(impares, pares);

    // Encontrar Emparejamiento Máximo
    
    // matchR[j] = i -> el nodo par 'j' está emparejado con el impar 'i'
    // Inicializado en -1 (libre)
    vector<int> matchL(N_impares, -1);
    vector<int> matchR(N_pares, -1);
    vector<int> dist(N_impares);
    int matching_size = 0;

    // --- Bucle Principal de Hopcroft-Karp ---
    
    while (bfs_hopcroft(N_impares, adj, matchL, matchR, dist)) {
        for (int i = 0; i < N_impares; ++i) {
			// Si el nodo i esta libre y se encuentra un camino desde i, se incrementa el matching
            if (matchL[i] == -1 && dfs_hopcroft(i, adj, matchL, matchR, dist)) {
                matching_size++;
            }
        }
    }
    return matching_size;
}

int main() {
    // Ejemplo de un conjunto C
    vector<int> C = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int min_elements_to_remove = find_min_elements_to_remove(C);

    cout << "El menor numero de elementos a eliminar es: " << min_elements_to_remove << endl;

    return 0;
}