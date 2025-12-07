#include <iostream>
#include <vector>

using namespace std;

vector<int> min_cover(vector<pair<int, int>> aristas, int n) {
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

void imprimirCaso(string nombre, int n, vector<pair<int, int>> aristas, int optimoEsperado) {
    cout << "--- " << nombre << " ---" << endl;
    vector<int> resultado = min_cover(aristas, n);

    cout << "Aristas procesadas: ";
    for(auto p : aristas) cout << "(" << p.first << "," << p.second << ") ";
    cout << endl;

    cout << "Tu Solucion (Size " << resultado.size() << "): ";
    for (int v : resultado) cout << v << " ";
    cout << endl;

    cout << "Solucion Optima (Size " << optimoEsperado << ")" << endl;
    
    if (resultado.size() <= 2 * optimoEsperado) {
        cout << "RESULTADO: Cumple la 2-aproximacion. ";
        if (resultado.size() > optimoEsperado) cout << "(Es suboptima, como se esperaba)";
        else cout << "(¡Encontro el optimo!)";
    } else {
        cout << "ALERTA: Algo salio mal, supera el doble del optimo.";
    }
    cout << endl << endl;
}

int main() {
    // CASO 1: Grafo Estrella (0 es el centro, conectado a 1, 2, 3, 4, 5)
    // Óptimo: Solo el nodo {0}. Tamaño = 1.
    // Tu algoritmo: Al ver (0,1), toma {0,1}. Luego 0 ya está ocupado, ignora las demás.
    // Resultado esperado: {0, 1} (Tamaño 2).
    vector<pair<int, int>> estrella = {{0,1}, {0,2}, {0,3}, {0,4}, {0,5}};
    imprimirCaso("Caso Estrella", 6, estrella, 1);

    // CASO 2: Camino de 4 nodos (0-1-2-3)
    // Óptimo: Los nodos del medio {1, 2}. Tamaño = 2.
    // Tu algoritmo: Toma (0,1) -> agrega {0,1}. El 1 queda ocupado.
    //               Mira (1,2) -> 1 ocupado, ignora.
    //               Mira (2,3) -> 2 libre, 3 libre -> agrega {2,3}.
    // Resultado esperado: {0, 1, 2, 3} (Tamaño 4). ¡El doble del óptimo!
    vector<pair<int, int>> camino = {{0,1}, {1,2}, {2,3}};
    imprimirCaso("Caso Camino Lineal", 4, camino, 2);

    // CASO 3: Triángulo (0-1-2-0)
    // Óptimo: Cualesquiera 2 nodos cubren todo. Tamaño = 2.
    // Tu algoritmo: Toma (0,1) -> agrega {0,1}.
    //               El resto de aristas tocan el 0 o el 1, así que las ignora.
    // Resultado esperado: {0, 1} (Tamaño 2).
    vector<pair<int, int>> triangulo = {{0,1}, {1,2}, {2,0}};
    imprimirCaso("Caso Triangulo", 3, triangulo, 2);

    return 0;
}