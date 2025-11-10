#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Estructura para representar el Arbol de Segmentos Persistente
struct Node{
	int sum;		// Suma del conteo de ocurrencias
	Node* left;		// Hijo izquierdo
	Node* right;	// Hijo derecho

	// Constructor hojas
	Node(int s) : sum(s), left(nullptr), right(nullptr) {}

	// Constructor padre
	Node(int s, Node* l, Node* r) : sum(s), left(l), right(r) {}
};

// Funcion para construir el arbol de segmentos
Node* build(int L, int R){
	if (L == R){
		return new Node(0);
	}

	int mid = (L + R) / 2;
	Node* hijo_izq = build(L, mid);
	Node* hijo_der = build(mid + 1, R);

	return new Node(hijo_izq->sum + hijo_der->sum, hijo_izq, hijo_der);
}

/**
 * Funcion para persistir en el arbol de segmentos
 * Crea una nueva versión (persistente) del árbol con el valor 'pos' actualizado.
 * 'prev_node' es la raíz de la versión anterior.
 * [L, R] es el rango de valores que cubre 'prev_node'.
 * 'pos' es el valor (de 1 a N) que estamos añadiendo.
 */
Node* update(Node* prev_node, int L, int R, int pos){
	if (L == R) {
        return new Node(prev_node->sum + 1);
    }

	int mid = (L + R) / 2;

	Node* nuevo_hijo_izq = prev_node->left;
	Node* nuevo_hijo_der = prev_node->right;

	if (pos <= mid){
		nuevo_hijo_izq = update(prev_node->left, L, mid, pos);
	}else{
		nuevo_hijo_der = update(prev_node->right, mid+1, R, pos);
	}

	return new Node(nuevo_hijo_izq->sum + nuevo_hijo_der->sum, nuevo_hijo_izq, nuevo_hijo_der);

}
// Funcion para hacer busqueda binaria en el arbol para buscar el k-esimo elemento
int query(Node* node_i, Node* node_j, int L, int R, int k){
	if (L==R){
		return L;
	}

	int mid = (L+R) / 2;

	int conteo_izq = node_j->left->sum - node_i->left->sum;

	if(k <= conteo_izq){
		return query(node_i->left, node_j->left, L, mid, k);
	} else {
		return query(node_i->right, node_j->right, mid+1, R, k - conteo_izq);
	}

}

int main() {
	vector<Node*> raices;
	// Leer N (numero de elementos) y Q (número de consultas)
	cout << "Ingrese el numero de elementos (N) y el numero de consultas (Q): ";
	int N, Q;
	cin >> N >> Q;

	int min_val = 1;
	int max_val = N;

	raices.push_back(build(min_val, max_val)); // raices[0]
	
	// Leer los elementos y construir las versiones persistentes del arbol
	cout << "Ingrese los elementos del arreglo A:" << endl;
	for (int i = 1; i <= N; ++i){
		int valor_actual_A;
		cin >> valor_actual_A;

		Node* nueva_raiz = update(raices[i-1], min_val, max_val, valor_actual_A);
		raices.push_back(nueva_raiz);
	}

	// Procesar las consultas
	cout << "Ingrese las consultas [i, j, k] (1-indexado):" << endl;
	for (int q = 0; q < Q; ++q){
		int i, j, k;
		cin >> i >> j >> k;
		int resultado = query(raices[i-1], raices[j], min_val, max_val, k);
		cout << ">>> Resultado de la consulta (" << i << ", " << j << ", " << k << "): " << resultado << endl;
	}

	return 0;
}