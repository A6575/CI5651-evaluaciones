#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>

using namespace std;

struct HLDSolver{
	int N;					// Numero de nodos (1..N)
	vector<vector<int>> adj;// Lista de adjacencia

	// --- HEAVY-LIGHT DESCOMPOSITION ---

	vector<int> parent;		// parent[i] = padre del nodo i
	vector<int> depth;		// depth[i] = profundidad del nodo i
	vector<int> heavy;		// heavy[i] = hijo pesado del nodo i
	vector<int> size;		// size[i] = tamaño del subárbol enraizado en i
	vector<int> head;		// head[i] = cabeza de la cadena pesada de i
	vector<int> pos;		// pos[i] = posicion de u en el Arbol de Segmentos
	vector<int> arr_base;	// Los valores base, aplanados segun HLD
	int timer;				// Contador para asignar las posiciones
	
	// --- ARBOL DE SEGMENTOS ---
	vector<int> seg_min;	// seg_min[i] = Minimo del rango del nodo i
	vector<int> seg_max;	// seg_max[i] = Maximo del rango del nodo i
	vector<bool> lazy;		// lazy[i] = toogle pendiente en el nodo i?
	
	// Constructor
	HLDSolver(int n) : 
		N(n), adj(n+1), parent(n+1),
		depth(n+1), heavy(n+1), size(n+1),
		head(n+1), pos(n+1), arr_base(n+1), timer(0),
		seg_min(4*n+5), seg_max(4*n+5), lazy(4*n+5, false) {}

	// Funcion para agregar aristas
	void add_edge(int u, int v){
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	// Funcion para precondicionamiento del arbol
	void dfs_setup(int u, int p, int d){
		// Se guarda la informacion del nodo u
		parent[u] = p;
		depth[u] = d;
		size[u] = 1;
		heavy[u] = -1;

		int max_size = 0;
		
		// Llamada recursiva para recorrer el arbol
		for(int v : adj[u]){
			if (v == p) continue;

			dfs_setup(v, u, d + 1);
			
			// Se actualiza el tamaño del subarbol y del hijo más pesado
			size[u] += size[v];
			if(size[v] > max_size){
				max_size = size[v];
				heavy[u] = v;
			}
		}
	}

	// Funcion para aplicar Heavy-light Descomposition
	void dfs_hld(int u, int h){
		// Se guarda la informacion del nodo u
		head[u] = h;
		pos[u] = timer++;

		// Llamada recursiva para buscar la cadena pesada de u
		if (heavy[u] != -1){
			dfs_hld(heavy[u], head[u]);
		}

		// Recorrer por nodos adjacentes
		for (int v : adj[u]){
			if (v == parent[u] || v == heavy[u]) {
				continue; // Ya fue procesado u
			}
			// Comienzo de nueva cadena pesada
			dfs_hld(v, v);
		}
	}

	// Funcion para construir el arbol de segmentos
	void build_segment_tree(int node, int start, int end){
		// Caso base: valores asignados al inicio
		if (start == end){
			seg_min[node] = arr_base[start];
			seg_max[node] = arr_base[start];
		} else {
			// Caso recursivo: actualizacion del min y max por segmentos
			int mid = (start + end) / 2;
			build_segment_tree(2*node, start, mid);
			build_segment_tree(2*node+1, mid+1, end);
			seg_min[node] = min(seg_min[2*node], seg_min[2*node+1]);
			seg_max[node] = max(seg_max[2*node], seg_max[2*node+1]);
		}
	}

	// Funcion empujar las toogle pendientes del nodo
	void push_down(int node){
		if (lazy[node]){
			int left_child = 2*node;
			int right_child = 2*node + 1;
			
			// Aplicar a hijo izquierdo
			int old_min_left = seg_min[left_child];
			int old_max_left = seg_max[left_child];

			seg_min[left_child] = 1 - old_max_left;
			seg_max[left_child] = 1 - old_min_left;
			lazy[left_child] = !lazy[left_child];
			
			// Aplicar a hijo derecho
			int old_min_right = seg_min[right_child];
			int old_max_right = seg_max[right_child];

			seg_min[right_child] = 1 - old_max_right;
			seg_max[right_child] = 1 - old_min_right;
			lazy[right_child] = !lazy[right_child];
			
			// Limpiar lazy del nodo actual
			lazy[node] = false;
		}
	}
	
	// Funcion para consultar el rango para toggle
	void toggle_range(int node, int start, int end, int L, int R){
		// Caso base: fuera de rango
		if (start > R || end < L){
			return;
		}
		
		// Caso 1: esta completamente comprendido en el rango
		if (L <= start && end <= R){
			// Calucular el complemento y actualizar el status de lazy propagation
			int old_min = seg_min[node];
			int old_max = seg_max[node];
			
			seg_min[node] = 1 - old_max;
			seg_max[node] = 1 - old_min;
			lazy[node] = !lazy[node];
			
			return;
		}

		// Reportar estado de propagacion
		push_down(node);

		// Caso 2: Recorrer los otros segmentos
		int mid = (start + end) / 2;

		toggle_range(2 * node, start, mid, L, R);
		toggle_range(2 * node + 1, mid + 1, end, L, R);

		// Combinar resultados
		seg_min[node] = min(seg_min[2 * node], seg_min[2 * node + 1]);
    	seg_max[node] = max(seg_max[2 * node], seg_max[2 * node + 1]);
	}

	// Funcion para consultar el rango para forall y exists
	pair<int, int> query_range(int node, int start, int end, int L, int R){
		// Caso base: fuera del rango
		if (start > R || end < L){
			return {INT_MAX, INT_MIN};	// Valores "nulos" para min y max
		}

		// Caso 1: esta completamente comprendido en el rango
		if (L <= start && end <= R){
			return {seg_min[node], seg_max[node]}; // Retornar valores calculados
		}

		// Reportar estado de propagacion
		push_down(node);

		// Caso 2: Recorrer los otros segmentos
		int mid = (start + end) / 2;

    	pair<int, int> res_izq = query_range(2 * node, start, mid, L, R);
    	pair<int, int> res_der = query_range(2 * node + 1, mid + 1, end, L, R);

		// Combinar resultados
		return {min(res_izq.first, res_der.first), max(res_izq.second, res_der.second)};
	}

	// Funcion para la operacion toggle de la tarea
	// Aprovecha la funcion toggle_range para propagar la negacion
	void toggle(int u, int v){
		int n_seg_tree = N - 1;
		while (head[u] != head[v]){
			if (depth[head[u]] > depth[head[v]]){
				toggle_range(1, 0, n_seg_tree, pos[head[u]], pos[u]);
				u = parent[head[u]];
			} else {
				toggle_range(1, 0, n_seg_tree, pos[head[v]], pos[v]);
				v = parent[head[v]];
			}
		}
		if (u == v) return;
		int L = min(pos[u], pos[v]) + 1;
		int R = max(pos[u], pos[v]);
		toggle_range(1, 0, n_seg_tree, L, R);
	}

	// Funcion para la operacion forall y exists de la tarea
	// Aprovecha la funcion query_range para obtener el minimo y maximo del segmento
	pair<int, int> query_path(int u, int v){
		pair<int, int> total = {INT_MAX, INT_MIN};
		int n_seg_tree = N - 1;

		while(head[u] != head[v]){
			pair<int, int> temp;

			if (depth[head[u]] > depth[head[v]]){
				temp = query_range(1, 0, n_seg_tree, pos[head[u]], pos[u]);
				u = parent[head[u]];
			} else {
				temp = query_range(1, 0, n_seg_tree, pos[head[v]], pos[v]);
				v = parent[head[v]];
			}

			total.first = min(total.first, temp.first);
			total.second = max(total.second, temp.second);
		}

		if (u != v){
			int L = min(pos[u], pos[v]) + 1;
			int R = max(pos[u], pos[v]);

			pair<int, int> temp = query_range(1, 0, n_seg_tree, L, R);

			total.first = min(total.first, temp.first);
			total.second = max(total.second, temp.second);
		}

		return total;
	}

	// Funcion para la operacion forall de la tarea
	bool forall(int u, int v){
		pair<int, int> result = query_path(u, v);

		// si el minimo de todo el segmento es 1, no existe
		// 0 en el camino (SE CUMPLE FORALL)
		return result.first == 1;
	}

	// Funcion para la operacion exists de la tarea
	bool exists(int u, int v){
		pair<int, int> result = query_path(u, v);

		// si el maximo de todo el segmento es 1, se asegura 
		// al menos un 1 en el camino (SE CUMPLE EXISTS)
		return result.second == 1;
	}
};

// Funcion Principal
int main(){
	int N;
	cout << "Ingrese el numero de nodos (los nodos serán [1..N]): ";
	cin >> N;

	HLDSolver solver(N);

	cout << "Ingrese las aristas y sus pesos (u v peso): " << endl;
	vector<tuple<int, int, int> > edges;
	for (int i = 0; i < N - 1; i++) {
		int u, v, valor;
		cin >> u >> v >> valor;
		solver.add_edge(u, v);
		edges.emplace_back(u, v, valor);
	}

	solver.dfs_setup(1, 0, 0);
	solver.dfs_hld(1, 1);

	for(const auto& edge : edges){
		int u, v, valor;
		tie(u, v, valor) = edge;

		if(solver.parent[v] == u){
			solver.arr_base[solver.pos[v]] = valor;
		} else{
			solver.arr_base[solver.pos[u]] = valor;
		}
	}

	solver.build_segment_tree(1, 0, N-1);
	cout << "Ingrese la cantidad de operaciones a realizar: ";
	int Q;
	cin >> Q;
	for (int i = 0; i < Q; ++i){
		string tipo_query;
		int u, v;
		cout << "Ingrese la operacion y los nodos [forall/exists/toogle] u v: ";
		cin >> tipo_query >> u >> v;

		if (tipo_query == "toggle"){
			solver.toggle(u, v);
		} else if (tipo_query == "forall"){
			cout << (solver.forall(u, v) ? ">>> TRUE" : ">>> FALSE") << endl;
		} else if (tipo_query == "exists"){
			cout << (solver.exists(u, v) ? ">>> TRUE" : ">>> FALSE") << endl;
		}
	}

	return 0;
}