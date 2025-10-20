#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
const long long INF = 1e18;

// Funcion para calcular la distancia al cuadrado entre dos puntos
long long distance_squared(pair<int, int> a, pair<int, int> b) {
	long long dx = a.first - b.first;
	long long dy = a.second - b.second;
	return dx * dx + dy * dy;
}

long long min_time_for_pick_up_bags(vector<pair<int, int>>& bags, vector<long long>& simple_cost, vector<vector<long long>>& double_cost) {
	int n = bags.size();
	vector<long long> dp(1 << n, INF);
	dp[0] = 0;

	int i_fija = -1,
		simple_mask,
		double_mask; // Indice del punto fijo (origen)
	for (int mask = 1; mask < (1 << n); ++mask) {
		for (int i = 0; i < n; ++i) {
			if (mask & (1 << i)) { i_fija = i; break; }
		}

		// Opcion 1: Recoger una sola bolsa
		simple_mask = mask ^ (1 << i_fija);
		dp[mask] = dp[simple_mask] + simple_cost[i_fija];
		// Opcion 2: Recoger dos bolsas
		for (int j = i_fija + 1; j < n; ++j) {
			if (mask & (1 << j)) {
				double_mask = simple_mask ^ (1 << j);
				dp[mask] = min(dp[mask], dp[double_mask] + double_cost[i_fija][j]);
			}
		}
	}

	return dp[(1 << n) - 1];
}
		
int main() {
	int n;
	cin >> n;
	vector<pair<int, int>> bags(n);
	for (int i = 0; i < n; ++i) {
		cin >> bags[i].first >> bags[i].second;
	}
	vector<long long> simple_cost(n);
	vector<vector<long long>> double_cost(n, vector<long long>(n));
	long long ruta1, ruta2;
	for (int i = 0; i < n; ++i) {
		simple_cost[i] = 2 * distance_squared({0, 0}, bags[i]);
		for (int j = i + 1; j < n; ++j) {
			ruta1 = distance_squared({0, 0}, bags[i]) + distance_squared(bags[i], bags[j]) + distance_squared(bags[j], {0, 0});
			ruta2 = distance_squared({0, 0}, bags[j]) + distance_squared(bags[j], bags[i]) + distance_squared(bags[i], {0, 0});
			double_cost[i][j] = min(ruta1, ruta2);
			double_cost[j][i] = double_cost[i][j];
		}
	}
	cout << min_time_for_pick_up_bags(bags, simple_cost, double_cost) << endl;
	return 0;
}