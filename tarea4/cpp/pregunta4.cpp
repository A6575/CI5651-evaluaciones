#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
// Definicion de INFINITY como un valor grande
const long long INF = 1e18;

// Funcion para calcular la distancia al cuadrado entre dos puntos
long long distance_squared(pair<int, int> a, pair<int, int> b) {
	long long dx = a.first - b.first;
	long long dy = a.second - b.second;
	return dx * dx + dy * dy;
}

// Funcion para calcular el tiempo minimo para recoger todas las maletas
long long min_time_for_pickup_bags(vector<pair<int, int>>& bags, vector<long long>& simple_cost, vector<vector<long long>>& double_cost) {
	int n = bags.size();
	// Arreglo DP donde dp[mask] es el costo minimo para recoger las maletas en 'mask'
	vector<long long> dp(1 << n, INF);
	dp[0] = 0;	// Costo cero para recoger ninguna maleta

	int i_fija = -1,	// Indice de la primera maleta en el subconjunto actual
		simple_mask,	// Mascara despues de recoger una sola maleta
		double_mask;	// Iterar sobre todas las posibles combinaciones de maletas
	for (int mask = 1; mask < (1 << n); ++mask) {
		// Encontrar la primera maleta en el subconjunto actual
		for (int i = 0; i < n; ++i) {
			// Si la maleta i está en el subconjunto actual, la fijamos
			if (mask & (1 << i)) { i_fija = i; break; }
		}

		// Posibilidad 1: Recoger una sola bolsa (i_fija)
		simple_mask = mask ^ (1 << i_fija);	// Mascara antes de recoger la maleta i_fija
		dp[mask] = dp[simple_mask] + simple_cost[i_fija]; // Actualizar el costo minimo

		// Posibilidad 2: Recoger dos bolsas (i_fija y j)
		for (int j = i_fija + 1; j < n; ++j) {
			// Si la maleta j está en el subconjunto actual
			if (mask & (1 << j)) {
				double_mask = simple_mask ^ (1 << j); // Mascara antes de recoger las maletas i_fija y j
				// Actualizar el costo minimo considerando recoger ambas maletas
				dp[mask] = min(dp[mask], dp[double_mask] + double_cost[i_fija][j]);
			}
		}
	}
	// El resultado final es el costo minimo para recoger todas las maletas
	return dp[(1 << n) - 1];
}
		
int main() {
	int n;
	cout << "Ingrese el numero de maletas: ";
	cin >> n;
	vector<pair<int, int>> bags(n);
	cout << "Ingrese las coordenadas (x y) de cada maleta:" << endl;
	for (int i = 0; i < n; ++i) {
		cin >> bags[i].first >> bags[i].second;
	}
	// Precalcular los costos de recoger una y dos maletas
	vector<long long> simple_cost(n);	// Costo de recoger una sola maleta
	vector<vector<long long>> double_cost(n, vector<long long>(n)); // Costo de recoger dos maletas
	
	long long ruta1, ruta2;
	for (int i = 0; i < n; ++i) {
		// Recoger una sola maleta i toma el doble de la distancia al cuadrado desde el origen a la maleta i (viaje de ida y vuelta)
		simple_cost[i] = 2 * distance_squared({0, 0}, bags[i]);
		for (int j = i + 1; j < n; ++j) {
			// Recoger dos maletas i y j: considerar ambas rutas posibles y tomar la minima
			// Ruta 1: Origen -> i -> j -> Origen
			ruta1 = distance_squared({0, 0}, bags[i]) + distance_squared(bags[i], bags[j]) + distance_squared(bags[j], {0, 0});
			// Ruta 2: Origen -> j -> i -> Origen
			ruta2 = distance_squared({0, 0}, bags[j]) + distance_squared(bags[j], bags[i]) + distance_squared(bags[i], {0, 0});
			double_cost[i][j] = min(ruta1, ruta2);
			double_cost[j][i] = double_cost[i][j]; // El camino es simetrico
		}
	}

	cout << "El tiempo minimo para recoger todas las maletas es: "
		<< min_time_for_pickup_bags(bags, simple_cost, double_cost) << endl;
	
	return 0;
}