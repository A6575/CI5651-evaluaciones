#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// Funcion para determinar si dos subarrays son disjuntos
// i y j son los indices de inicio de los subarrays, k es la longitud del subarray
// Devuelve true si los subarrays son disjuntos, false en caso contrario
bool is_disjoint(int i, int j, int k) {
    // Dos subarrays son disjuntos si no se superponen:
    return (k == 0) || // Si k es 0, siempre son disjuntos
        (i + k - 1 < j) || // Si el primer subarray termina antes de que comience el segundo
        (j + k - 1 < i); // Si el segundo subarray termina antes de que comience el primero
}

// Funcion para calcular la longitud máxima de subarrays familiares
int max_family_subarrays(const vector<int>& A) {
    int n = A.size();
    if (n < 2) {
        return 0;   // Si el vector tiene menos de 2 elementos, no se pueden formar subarrays familiares
    }

    // Crear dos vectores para almacenar las longitudes de subarrays familiares
    vector<int> prev(n, 0); // Longitudes de subarrays familiares del paso anterior
    vector<int> curr(n, 0); // Longitudes de subarrays familiares del paso actual

    int max_length_global = 0;  // Longitud máxima global de subarrays familiares

    // Iterar sobre los elementos del vector A en orden inverso
    for (int i = n - 1; i >= 0; --i) {
        for (int j = n - 1; j >= 0; --j) {
            // Si i y j son iguales, el subarray es trivial y su longitud es 0
            if (i == j){
                curr[j] = 0;
            } // Si A[i] y A[j] son coprimos, se calcula la longitud del subarray
            else if (gcd(A[i], A[j]) == 1) {
                // Si los subarrays extendidos son disjuntos, se incrementa la longitud
                if (j + 1 < n && is_disjoint(i, j, 1 + prev[j + 1])) {
                    curr[j] = 1 + prev[j + 1];
                } else {
                    curr[j] = 1;
                }
            } // Si A[i] y A[j] no son coprimos, la longitud del subarray es 0 
            else {
                curr[j] = 0;
            }
            // Actualizar la longitud máxima global
            max_length_global = max(max_length_global, curr[j]);
        }
        // Actualizar el vector prev para la siguiente iteración
        prev = curr;
    }
    return max_length_global;
}

int main() {
    vector<int> A = {3, 10, 1, 8, 4, 5, 3, 6, 9, 2};
    cout << max_family_subarrays(A) << endl;
    return 0;
}