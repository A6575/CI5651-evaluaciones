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

#include <iostream>
#include <vector>

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

// Función DFS para encontrar un camino aumentante
bool dfs_match(int u, const vector<vector<int>>& adj, vector<int>& matchR, vector<bool>& visitado) {
    
    // Marcar el nodo impar 'u' como visitado
    visitado[u] = true;

    // Iterar por todos los vecinos 'v' (nodos pares) de 'u'
    for (int v : adj[u]) {
        
		// Caso 1: El nodo par 'v' está libre, por lo que se puede emparejar con 'u'
        // Caso 2: El nodo par 'v' está ocupado, pero su pareja
        // (matchR[v]) puede encontrar una nueva pareja recursivamente.
        //
        // Se evitará al 'visitado[matchR[v]]' para no entrar en bucles
        if (matchR[v] == -1 || (!visitado[matchR[v]] && dfs_match(matchR[v], adj, matchR, visitado))) {
            matchR[v] = u;
            return true;
        }
    }
    
    // No se pudo encontrar un camino/pareja desde 'u'
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
    vector<vector<int>> adj = build_bipartite_graph(impares, pares);

    // Encontrar Emparejamiento Máximo
    
    // matchR[j] = i -> el nodo par 'j' está emparejado con el impar 'i'
    // Inicializado en -1 (libre)
    vector<int> matchR(pares.size(), -1);
    
    int matching_size = 0;

    // Iterar por cada nodo impar 'i' e intentar encontrarle una pareja
    for (int i = 0; i < impares.size(); ++i) {
        
        // El 'visitado' se reinicia para CADA nodo impar.
        vector<bool> visitado(impares.size(), false);

        // Si el DFS tiene éxito, aumentar el contador
        if (dfs_match(i, adj, matchR, visitado)) {
            matching_size++;
        }
    }

    return matching_size;
}

int main() {
    // Ejemplo de un conjunto C
    vector<int> C = {1, 9, 20, 30};

    int min_elements_to_remove = find_min_elements_to_remove(C);

    cout << "El menor numero de elementos a eliminar es: " << min_elements_to_remove << endl;

    return 0;
}