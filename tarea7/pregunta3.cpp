#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

/**
 * Estructura de Punto 2D
 */
struct Point {
    long long x, y;

	// Sobrecarga de operadores para set y comparaciones
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

/**
 * Producto Cruzado
 * retorna > 0 (giro a la izquierda), 
 * < 0 (giro a la derecha), 
 * = 0 (colineal)
 */
long long cross_product_sign(Point p, Point q, Point r) {
	// Se calcula relativo a 'p' para mantener los números más pequeños
    return (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
}

/**
 * Calcula la distancia al cuadrado (más rápido que sqrt).
 * Se usa para desempatar puntos colineales en el ordenamiento.
 */
long long distSq(Point p1, Point p2) {
    long long dx = p1.x - p2.x;
    long long dy = p1.y - p2.y;
    return dx * dx + dy * dy;
}

// Punto pivote global (o se puede pasar por referencia/captura lambda)
Point p0;

/**
 * Función de comparación para el ordenamiento angular de Graham Scan.
 */
bool compare_angles(const Point& p1, const Point& p2) {
    // Calcula el giro p0 -> p1 -> p2
    long long cp = cross_product_sign(p0, p1, p2);

    // Caso 1: Los puntos son colineales con p0
    if (cp == 0) {
        // Desempata por distancia: el más cercano va primero
        return distSq(p0, p1) < distSq(p0, p2);
    }

    // Caso 2: No son colineales.
    // Si el giro es > 0 (izquierda), p1 viene antes que p2 en el orden angular.
    return cp > 0;
}

/**
 * Encuentra la Convex Hull usando el algoritmo Graham Scan.
 */
vector<Point> find_convex_hull(vector<Point>& points) {
    int m = points.size();
    if (m <= 2) {
        return points;
    }

    // Encontrar el punto pivote p0 (y-min, luego x-min)
    int p0_idx = 0;
    for (int i = 1; i < m; ++i) {
        if (points[i].y < points[p0_idx].y ||
            (points[i].y == points[p0_idx].y && points[i].x < points[p0_idx].x)) {
            p0_idx = i;
        }
    }
    
    // Mover p0 al inicio del vector
    swap(points[0], points[p0_idx]);
    p0 = points[0]; // Asignar el pivote global para el comparador

    // Ordenar el resto de los puntos (desde el índice 1) por ángulo
    sort(points.begin() + 1, points.end(), compare_angles);

    vector<Point> hull_stack;
    hull_stack.push_back(points[0]); // p0
    hull_stack.push_back(points[1]); // p1

    for (int i = 2; i < m; ++i) {
        Point p_nuevo = points[i];

        // sacar de la pila si el giro es <= 0 (derecha o colineal)
        while (hull_stack.size() >= 2 &&
               cross_product_sign(hull_stack[hull_stack.size() - 2], // p_ant
                                  hull_stack.back(),                 // p_top
                                  p_nuevo) <= 0) {
            hull_stack.pop_back();
        }
        
        hull_stack.push_back(p_nuevo);
    }

    return hull_stack;
}

/**
 * Funcion para calcular el número de "capas" de la envolvente convexa.
 */
int count_layers(const vector<Point>& all_points) {
    if (all_points.empty()) {
        return 0;
    }
    int layer_count = 0;
	// set para almacenar los puntos restantes.
    set<Point> remaining_points(all_points.begin(), all_points.end());

    while (!remaining_points.empty()) {
		// Caso base: si quedan 2 o menos, forman la última capa.
        if (remaining_points.size() <= 2) {
            layer_count++;
            break;
        }

		// Convertir el set a vector para el algoritmo de la envolvente
        vector<Point> current_batch(remaining_points.begin(),
                                         remaining_points.end());

        // calcular convex hull
        vector<Point> hull = find_convex_hull(current_batch);

		// Incrementar el contador
        layer_count++;

		// eliminar los puntos de la envolvente
        if (hull.empty()) {
            break; 
        }
        
        for (const Point& p : hull) {
            remaining_points.erase(p);
        }
    }
    return layer_count;
}

int main() {
	// Ejemplo de uso
    vector<Point> points = {
        {1, 1}, {2, 2}, {3, 1}, {4, 3}, {5, 1}, {5, 5},
        {1, 5}, {3, 6}, {2, 4}, {3, 3}, {4, 4}
    };
    
    cout << "Calculando capas (con Graham Scan)..." << endl;
    int num_layers = count_layers(points);
    cout << "Numero total de capas: " << num_layers << endl; // Debería ser 3
    cout << "---" << endl;

    // Ejemplo colineal
    vector<Point> collinear_points = {
        {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}
    };
    cout << "Calculando capas para puntos colineales..." << endl;
    int num_layers_collinear = count_layers(collinear_points);
    cout << "Numero total de capas: " << num_layers_collinear << endl; // Debería ser 3
    
    return 0;
}