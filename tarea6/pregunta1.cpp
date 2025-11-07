#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Variable global para el numero de elementos del arreglo
int N;

// Estructura Nodo para representar un nodo del TREAP
struct Node{
	int value;			// Valor del nodo
	int priority;		// Prioridad del nodo (aleatoria)
	int size;			// Tamaño del subárbol
	Node* left;			// Hijo izquierdo
	Node* right;		// Hijo derecho

	// Constructor
	Node(int val) : value(val), priority(rand()), size(1), left(nullptr), right(nullptr) {}
};

// Función para obtener el tamaño del subárbol
int getSize(Node* node) {
	return node ? node->size : 0;
}

// Función para actualizar el tamaño del subárbol
void updateSize(Node* node) {
	if (node) {
		node->size = 1 + getSize(node->left) + getSize(node->right);
	}
}

// Función merge para unir dos árboles TREAP
Node* merge(Node* left, Node* right) {
	// Casos bases
	if (!left) return right;
	if (!right) return left;

	// Combinar según la prioridad
	if (left->priority > right->priority) {
		left->right = merge(left->right, right);
		updateSize(left);
		return left;
	} else {
		right->left = merge(left, right->left);
		updateSize(right);
		return right;
	}
}

// Función para dividir el árbol TREAP en función de key
void split(Node* root, int key, Node*& left, Node*& right) {
	// Caso base
	if (!root) {
		left = right = nullptr;
		return;
	}

	// Obtener la posición del nodo actual
	int currentKey = getSize(root->left) + 1;
	
	// Dividir recursivamente
	if (key < currentKey) {
		right = root;
		split(root->left, key, left, root->left);
		updateSize(right);
	} else {
		left = root;
		split(root->right, key - currentKey, root->right, right);
		updateSize(left);
	}
}

// Implementacion de Multiswap usando TREAP
void multiswap(Node*& root, int a, int b){
	// tamaño del primer bloque
	int b1_size = b - a;
	if (b1_size <= 0) return;

	// tamaño del segundo bloque
	int b2_size = min(b1_size, N - b+1);
	if (b2_size <= 0) return;

	// Dividir el TREAP en las cuatro partes necesarias
	// P1: [1, a-1], P2: [a, a+b1_size-1], P3: [a+b1_size, a+b1_size+b2_size-1], P4: [a+b1_size+b2_size, N]
	Node *P1, *P2, *P3, *P4;
	Node *leftPart1, *leftPart2;

	split(root, a - 1, P1, leftPart1);
	split(leftPart1, b1_size, P2, leftPart2);
	split(leftPart2, b2_size, P3, P4);
	
	// Unir las partes en el orden correcto: P1, P3, P2, P4
	Node *temp = merge(P1, P3);
	temp = merge(temp, P2);
	root = merge(temp, P4);
}

// Función para imprimir el árbol TREAP en orden
void imprimir(Node* T) {
    if (!T) return;
    imprimir(T->left);
    cout << T->value << " ";
    imprimir(T->right);
}

int main(){
	srand(time(0));
	cout << "Ingrese el numero de elementos del arreglo: ";
	cin >> N;
	
	Node* root = nullptr;
	int valor;
	
	cout << "Ingrese los elementos del arreglo: ";
	for(int i = 0; i<N; i++){
		cin >> valor;
		Node* node = new Node(valor);
		root = merge(root, node);
	}
	
	int n_op;
	cout << "Ingrese el numero de operaciones multiswap: ";
	cin >> n_op;
	
	int a, b;
	for (int i = 0; i < n_op; i++){
		cout << "Ingrese la operacion (a, b) nro " << i+1 << ": ";
		cin >> a >> b;
		multiswap(root, a, b);
		cout << "\n >>> Resultado: ";
		imprimir(root);
		cout << "\n" << endl;
	}
	
	return 0;
}