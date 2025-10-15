#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;

// Estructura del nodo del árbol de segmentos
struct Nodo {
	int inicio, fin;			// rango [inicio, fin]. Se asume 0-indexación
	int balanced,				// Cantidad de paréntesis "balanceados" en el rango. Es decir,
								// pares de paréntesis correctamente cerrados
		open,					// Cantidad de paréntesis abiertos en el rango que no han sido emparejados
		close; 					// Cantidad de paréntesis cerrados en el rango que no han sido emparejados

	Nodo(int inicio, int fin, int open, int close) : inicio(inicio), fin(fin), balanced(0), open(open), close(close){}
};

// Estructura del árbol de segmentos
class SegmentTree {
	vector<Nodo*> tree;			// Almacena los nodos del árbol de segmentos. El índice 1 es la raíz
	vector<vector<int> > adj;	// Almacena los hijos de cada nodo en el árbol de segmentos. El índice 1 es la raíz
	int size;					// Tamaño del string original (cadena de paréntesis)
	size_t idx;					// Índice para asignar identificadores únicos a los nodos

	private:
		// Función recursiva para construir el árbol de segmentos
		void build(const string& s, size_t id, int inicio, int fin) {
			if (id >= tree.size()) {
				cerr << "Error: id supera el tamaño de tree" << endl;
				exit(1);
			}
			// Caso base: si el rango es un solo carácter
			if (inicio == fin) {
				if (s[inicio] == '(') tree[id] = new Nodo(inicio, fin, 1, 0);
				else tree[id] = new Nodo(inicio, fin, 0, 1);
				return;
			}

			// Caso recursivo: dividir el rango en dos mitades y construir los nodos hijos
			int mid = (inicio + fin) / 2;
			size_t left_idx = ++this->idx;
			size_t right_idx = ++this->idx;

			if (left_idx >= tree.size() || right_idx >= tree.size()) {
				cerr << "Error: idx supera el tamaño de tree" << endl;
				exit(1);
			}
			
			adj[id].push_back(left_idx);
			adj[id].push_back(right_idx);
			
			build(s, left_idx, inicio, mid);
			build(s, right_idx, mid + 1, fin);
			
			// Combinar los nodos hijos en el nodo padre
			tree[id] = mergeNodes(tree[left_idx], tree[right_idx]);
		}

		/* 
		Función para combinar los valores de dos nodos en el padre.
		Con esta funcion se espera que el nodo padre cumpla con que:
			- El número de paréntesis balanceados represente la cantidad de paréntesis
			  correctamente cerrados en el rango (es decir, la subcadena correspondiente).
			- El número de paréntesis abiertos represente la cantidad de paréntesis abiertos
			  en el rango que no han sido emparejados.
			- El número de paréntesis cerrados represente la cantidad de paréntesis cerrados
			  en el rango que no han sido emparejados.
		*/
		Nodo* mergeNodes(Nodo* izq, Nodo* der) {
			if (izq == nullptr || der == nullptr) {
				cerr << "Error: Nodo izquierdo o derecho es nulo en mergeNodes" << endl;
				exit(1);
			}
			// Crear un nuevo nodo padre
			Nodo* padre = new Nodo(izq->inicio, der->fin, 0, 0);

			// La cantidad de nuevos pares balanceados formados al combinar los nodos
			// se determina por el mínimo entre los paréntesis abiertos del nodo izquierdo
			// y los paréntesis cerrados del nodo derecho, asegurando que solo se formen pares completos.
			int nuevos_pares = min(izq->open, der->close);

			// Actualizar los valores del nodo padre
			padre->balanced = izq->balanced + der->balanced + 2 * nuevos_pares;
			padre->open = izq->open + (der->open - nuevos_pares);
			padre->close = izq->close + (der->close - nuevos_pares);
			
			return padre;
		}

		// Función recursiva para consultar el árbol de segmentos en un rango dado
		Nodo* query(size_t id, int inicio_q, int fin_q) {
			if (id >= tree.size() || tree[id] == nullptr) {
				cerr << "Error: Nodo no inicializado en tree[" << id << "]" << endl;
				exit(1);
			}
			// Si el rango del nodo actual no se solapa con el rango de consulta
			// retornar un nodo neutro. Equivale a "delegar" a un solo nodo.
			if (tree[id]->fin < inicio_q || tree[id]->inicio > fin_q) {
				return new Nodo(0, 0, 0, 0); // Nodo neutro
			}

			// Si el rango del nodo actual está completamente dentro del rango de consulta
			// retornar el nodo actual (valor precalculado)
			if (tree[id]->inicio >= inicio_q && tree[id]->fin <= fin_q) {
				return tree[id];
			}

			if (adj[id].size() < 2) {
				cerr << "Error: adj[" << id << "] no tiene suficientes hijos" << endl;
				exit(1);
			}

			// Caso recursivo: consultar ambos hijos y combinar los resultados
			Nodo* izq = query(adj[id][0], inicio_q, fin_q);
			Nodo* der = query(adj[id][1], inicio_q, fin_q);
			
			return mergeNodes(izq, der);	
		}
	public:
		// Constructor que inicializa el árbol de segmentos a partir del string dado
		SegmentTree(const string& s) : size(s.size()), idx(1) {
			tree.resize(4 * size, nullptr);	// Tamaño máximo del árbol de segmentos
			adj.resize(4 * size);			// Tamaño máximo del árbol de segmentos
			build(s, 1, 0, size-1);			// Construcción del árbol de segmentos
		}

		// Función pública para consultar el número máximo de paréntesis balanceados en un rango dado
		int maxBP(int inicio_q, int fin_q) {
			Nodo* result = query(1, inicio_q, fin_q);
			if (result == nullptr) {
				cerr << "Error: Consulta fallida para el rango [" << inicio_q << ", " << fin_q << "]" << endl;
				exit(1);
			}
			return result->balanced;
		}
};

int main() {
	cout << "Ingrese una cadena de paréntesis [Ej.: ()()) ]: ";
	string s;
	cin >> s;
	SegmentTree segTree(s);
	cout << "Ingrese el rango de consulta 0-indexado [Ej.: inicio fin]: ";
	int inicio, fin;
	cin >> inicio >> fin;
	int result = segTree.maxBP(inicio, fin);
	cout << "La longitud de la sub-cadena bien parentizada más larga en el rango ["
		<< inicio << ", " << fin << "] es: " << result << endl;
	return 0;
}