#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Multiplicacion de matrices 3x3
vector<vector<long long int>> multiply(const vector<vector<long long int>>& A, const vector<vector<long long int>>& B) {
	vector<vector<long long int>> C(3, vector<long long int>(3, 0));

	C[0][0] = A[0][0]*B[0][0] + A[0][1]*B[1][0] + A[0][2]*B[2][0];
	C[0][1] = A[0][0]*B[0][1] + A[0][1]*B[1][1] + A[0][2]*B[2][1];
	C[0][2] = A[0][0]*B[0][2] + A[0][1]*B[1][2] + A[0][2]*B[2][2];
	C[1][0] = A[1][0]*B[0][0] + A[1][1]*B[1][0] + A[1][2]*B[2][0];
	C[1][1] = A[1][0]*B[0][1] + A[1][1]*B[1][1] + A[1][2]*B[2][1];
	C[1][2] = A[1][0]*B[0][2] + A[1][1]*B[1][2] + A[1][2]*B[2][2];
	C[2][0] = A[2][0]*B[0][0] + A[2][1]*B[1][0] + A[2][2]*B[2][0];
	C[2][1] = A[2][0]*B[0][1] + A[2][1]*B[1][1] + A[2][2]*B[2][1];
	C[2][2] = A[2][0]*B[0][2] + A[2][1]*B[1][2] + A[2][2]*B[2][2];
	
	return C;
}

// Exponenciacion rapida para matrices 3x3
vector<vector<long long int>> exp_matriz(const vector<vector<long long int>>& A, int n){
	if (n == 0) {
		return {{1,0,0},{0,1,0},{0,0,1}};
	}

	auto half = exp_matriz(A, n/2);

	if (n % 2 == 0) {
		return multiply(half, half);
	} else {
		return multiply(multiply(half, half), A);
	}
}

// Funcion para calcular el n-esimo numero de la secuencia de Perrin
long long int perrin(int n){
	if (n == 0) return 3;
	if (n == 1) return 0;
	if (n == 2) return 2;

	vector<vector<long long int>> A = {{0,1,1},{1,0,0},{0,1,0}};
	
	auto result = exp_matriz(A, n-2);
	
	return result[0][0]*2 + result[0][2]*3; // se omite result[0][1]*0 porque es 0
}

int main() {
	int n;
	cout << "Ingrese un numero n para calcular el n-esimo numero de la secuencia de Perrin: ";
	cin >> n;
	
	long long int resultado = perrin(n);
	cout << "El " << n << "-esimo numero de la secuencia de Perrin es: " << resultado << endl;
	
    return 0;
}