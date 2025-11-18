#include <iostream>
#include <vector>
#include <cmath>       // Para sqrt, atan2, acos, PI
#include <algorithm>   // Para sort, max
#include <iomanip>     // Para fixed y setprecision

using namespace std;

// --- Constantes y Estructuras ---

// Estructura para representar un punto 2D
struct Point {
    double x, y;
};

// Estructura para guardar el resultado de la pregunta
struct Result{
	Point p;
	int max_points;
};

// Tolerancia (Epsilon) para cálculos con punto flotante
const double EPSILON = 1e-9;
// Definición de PI
const double PI = acos(-1.0);

/**
 * Funcion que calcula la distancia al cuadrado
 */
double distSq(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

/**
 * Funcion para normalizar un ángulo para que esté en el rango [-PI, PI]
 */
double normalize_angle(double angle) {
    while (angle > PI) angle -= 2 * PI;
    while (angle <= -PI) angle += 2 * PI;
    return angle;
}

/**
 * Utiliza un Barrido Angular (Angular Sweep) anclado en cada punto para
 * calcular el centro y la maximizacion de los puntos
 */
Result find_point_of_max_coverage(const vector<Point>& P, double R) {
    int n = P.size();
    if (n == 0) return { {0, 0}, 0 };

    double R_sq = R * R;
    int max_puntos = 1;
	Point mejor_centro = P[0]; // Primer punto como un centro inicial

    // Bucle para cada punto "ancla" P[i]
    for (int i = 0; i < n; ++i) {

        // --- CASO 1: Probar el círculo centrado EN P[i] ---
        int puntos_centrados_en_i = 0;
        for (int k = 0; k < n; ++k) {
            if (distSq(P[i], P[k]) <= R_sq + EPSILON) {
                puntos_centrados_en_i++;
            }
        }

        if (puntos_centrados_en_i > max_puntos) {
            max_puntos = puntos_centrados_en_i;
            mejor_centro = P[i];
        }

        // --- CASO 2: Barrido Angular (P[i] en el borde) ---

        // Lista de eventos (angulo, tipo)
        // tipo +1 = un punto "entra" en el círculo
        // tipo -1 = un punto "sale" del círculo
        vector<pair<double, int>> events;
        
        // El conteo inicial para el barrido.
        // Incluye el ancla P[i]
        int puntos_actuales_barrido = 1; 

        // Bucle para generar eventos
        for (int j = 0; j < n; ++j) {
            if (i == j) continue; // No comparar con nosotros mismos

            double d = sqrt(distSq(P[i], P[j]));

            // Si P[j] está demasiado lejos, nunca puede estar en un
            // círculo que también tiene a P[i] en el borde.
            if (d > 2 * R + EPSILON) continue;

            // --- Geometría del Arco ---
            // ángulo_ij = ángulo del vector P[i] -> P[j]
            // offset = mitad del ángulo en P[i] (P[j]-P[i]-C)
            double angle_ij = atan2(P[j].y - P[i].y, P[j].x - P[i].x);
            double offset = acos(d / (2.0 * R));

            double alpha = normalize_angle(angle_ij - offset);
            double beta = normalize_angle(angle_ij + offset);
            
            events.push_back({alpha, +1});
            events.push_back({beta, -1});
            
            // Si el arco cruza -PI/PI (wrap-around)
            if (alpha > beta) {
                // Este punto P[j] está activo al inicio del barrido (en -PI)
                puntos_actuales_barrido++;
            }
        }
        
        // Ordenar los eventos
        sort(events.begin(), events.end());
        
        // Barrido Angular
        if (puntos_actuales_barrido > max_puntos){
			max_puntos = puntos_actuales_barrido;
			mejor_centro = {
				P[i].x + R * cos(-PI),
				P[i].y + R * sin(-PI)
			};
		}
        
        for (const auto& ev : events) {
            puntos_actuales_barrido += ev.second; // +1 o -1
            if (puntos_actuales_barrido > max_puntos){
				max_puntos = puntos_actuales_barrido;
				mejor_centro = {
					P[i].x + R * cos(ev.first),
					P[i].y + R * sin(ev.first)
				};
			}
        }
    }

    return {mejor_centro, max_puntos};
}

// --- Función Principal (main) ---

int main() {
    // Configurar la precisión de salida para doubles
    cout << fixed << setprecision(1);

    // --- Test: Ejemplo de prueba ---
    cout << "--- Test ---" << endl;
    vector<Point> points = {
        {1, 3}, {2, 3}, {1, 2}, {3, 5}, {4, 3}
    };
    double R = 1.0;
    cout << "Puntos: {(1,3), (2,3), (1,2), (3,5), (4,3)}, Radio: " << R << endl;
    Result max = find_point_of_max_coverage(points, R);
    cout << "Puntos maximos cubiertos: " << max.max_points << endl;
	cout << "Centro:    (" << max.p.x << ", " << max.p.y << ")" << endl;
    cout << "---------------------------------" << endl;

    return 0;
}