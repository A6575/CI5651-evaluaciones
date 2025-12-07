#include <iostream>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

vector<double> multiplicar_matriz_vector(const vector<vector<double>>& matriz, const vector<double>& vec) {
    size_t filas = matriz.size();
    size_t columnas = matriz[0].size();
    vector<double> resultado(filas, 0.0);

    for (size_t i = 0; i < filas; ++i) {
        for (size_t j = 0; j < columnas; ++j) {
            resultado[i] += matriz[i][j] * vec[j];
        }
    }

    return resultado;
}

// Algoritmo de Monte Carlo para verificar si B es inversa de A
bool verificarInversa(const vector<vector<double>>& A, const vector<vector<double>>& B, double epsilon) {
    int n = A.size();
    
    // 1. Calcular k iteraciones necesarias según epsilon
    // k >= log(1/epsilon) / log(2)
    int k = ceil(log(1.0 / epsilon) / log(2.0));

    // Configuración de aleatoriedad moderna
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 1); // ¡Aquí están tu 0 y 1!

    for (int iter = 0; iter < k; ++iter) {
        // 2. Generar vector aleatorio r con 0s y 1s
        vector<double> r(n);
        for (int i = 0; i < n; ++i) {
            r[i] = distrib(gen);
        }

        // 3. Calcular x = B * r  (O(n^2))
        vector<double> x = multiplicar_matriz_vector(B, r);

        // 4. Calcular y = A * x  (O(n^2))
        // Esto equivale a y = A * (B * r)
        vector<double> y = multiplicar_matriz_vector(A, x);
        // 5. Verificar si y == r (con margen de error por ser doubles)
        for (int i = 0; i < n; ++i) {
            if (abs(y[i] - r[i]) > 1e-9) { 
                return false; // Testigo de que NO son inversas
            }
        }
    }

    return true; // Probablemente son inversas
}

int main() {
    // Ejemplo de uso
    vector<vector<double>> A = {
        {4, 0},
        {0, 4}
    };

    vector<vector<double>> B = {
        {0.25, 0},
        {0, 0.25}
    };

    double epsilon = 0.01; // Nivel de confianza

    if (verificarInversa(A, B, epsilon)) {
        cout << "B es probablemente la inversa de A." << endl;
    } else {
        cout << "B NO es la inversa de A." << endl;
    }

    return 0;
}
