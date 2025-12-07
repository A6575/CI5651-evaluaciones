#include <iostream>
#include <vector>

using namespace std;

// Función para encontrar una cobertura de vértices usando un algoritmo voraz 2-aproximado
vector<int> min_cover(vector<pair<int, int>> aristas, int n) {
    // Vector para rastrear qué vértices ya han sido incluidos en la cobertura
    vector<bool> visitado(n, false);
    vector<int> cover;

    for (const auto& arista : aristas) {
        int u = arista.first;
        int v = arista.second;

        if (!visitado[u] && !visitado[v]) {
            visitado[u] = true;
            visitado[v] = true;
            cover.push_back(u);
            cover.push_back(v);
        }
    }

    return cover;
}

int main() {
    // Grafo Estrella (0 es el centro, conectado a 1, 2, 3, 4, 5)
    // Óptimo: Solo el nodo {0}. Tamaño = 1.
    // Algoritmo propuesto: Al ver (0,1), toma {0,1}. Luego 0 ya está ocupado, ignora las demás.
    // Resultado esperado: {0, 1} (Tamaño 2).
    vector<pair<int, int>> estrella = {{0,1}, {0,2}, {0,3}, {0,4}, {0,5}};
    vector<int> resultado = min_cover(estrella, 6);

    cout << "Aristas procesadas: ";
    for(auto p : estrella) cout << "(" << p.first << "," << p.second << ") ";
    cout << endl;

    cout << "Solucion obtenida (Size " << resultado.size() << "): ";
    for (int v : resultado) cout << v << " ";
    cout << endl;

    return 0;
}