#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

// Estructura para representar un rectángulo
struct Rect {
    long long h, w;
};

// Estructura para representar una recta: y = mx + c
struct Line {
    long long m, c;
    
    // Evalúa la recta en un punto x
    long long eval(long long x) {
        return m * x + c;
    }
    
    // Calcula la intersección en el eje X entre dos rectas
    // (c2 - c1) / (m1 - m2)
    double intersectX(const Line& other) const {
        return (double)(other.c - c) / (m - other.m);
    }
};

int main() {
	// Cantidad de pares a ingresar
    int n;
	cout << "Ingrese el numero de rectangulos a ingresar: ";
	cin >> n;

	// Vector de Rectangulos (alto, ancho)
    vector<Rect> raw_rects(n);
	cout << "Ingrese los rectangulos (alto ancho):" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> raw_rects[i].h >> raw_rects[i].w;
    }

    // Preprocesamiento:
    // Ordenar por altura ascendente. A igual altura, ancho ascendente.
    sort(raw_rects.begin(), raw_rects.end(), [](const Rect& a, const Rect& b) {
        if (a.h != b.h) return a.h < b.h;
        return a.w < b.w;
    });

    vector<Rect> rects;
    for (const auto& r : raw_rects) {
        // Eliminar rectángulos dominados (es decir, contenidos en el actual).
        // Como h es creciente, solo se necesita chequear el ancho.
        while (!rects.empty() && rects.back().w <= r.w) {
            rects.pop_back();
        }
        rects.push_back(r);
    }
    
    // Ahora 'rects' tiene h estrictamente creciente y w estrictamente decreciente.
    int m = rects.size();
    
    // Programación Dinámica con Convex Hull Trick
    // dp[i] = costo mínimo para agrupar los rectángulos 0...i-1
    // Recurrencia: dp[i] = min_{0<=j<i} { dp[j] + rects[j].w * rects[i-1].h }
    // Recta para j: Pendiente m = rects[j].w, Intercepto c = dp[j]
    // Variable x = rects[i-1].h
    
    deque<Line> dq;
    
    // Caso base: dp[0] = 0. Agregamos la recta correspondiente a j=0.
    // La recta del caso base (j=0) tiene pendiente rects[0].w y costo dp[0]=0
    dq.push_back({rects[0].w, 0});
    
    vector<long long> dp(m + 1, 0);

    for (int i = 1; i <= m; ++i) {
        // Variable x para la consulta actual: altura del rectángulo actual
        long long x = rects[i-1].h;
        
        // Eliminar rectas del frente que ya no son óptimas.
        // Como x crece, el óptimo se mueve hacia pendientes menores (hacia la derecha).
        while (dq.size() >= 2 && dq[0].eval(x) >= dq[1].eval(x)) {
            dq.pop_front();
        }
        
        // El mejor valor actual
        dp[i] = dq[0].eval(x);
        
        // Agregar la nueva recta generada por el estado actual 'i'
        // para ser usada en el futuro (como j).
        if (i < m) {
            // Nueva recta con pendiente w del siguiente rectángulo posible (j+1)
            // y costo base acumulado dp[i]
            Line newLine = {rects[i].w, dp[i]};
            
            // Mantener la convexidad eliminando rectas redundantes del final.
            // Si la intersección de la nueva con la penúltima es antes que
            // la intersección de la última con la penúltima, la última no sirve.
            while (dq.size() >= 2) {
                const Line& l2 = dq.back();       // Última
                const Line& l1 = dq[dq.size()-2]; // Penúltima
                
                // Si intersect(l1, newLine) <= intersect(l1, l2), se borra l2
                if (l1.intersectX(newLine) <= l1.intersectX(l2)) {
                    dq.pop_back();
                } else {
                    break;
                }
            }
            dq.push_back(newLine);
        }
    }

	// Respuesta: 
    cout << "El costo minimo de la particion es: " << dp[m] << endl;

    return 0;
}