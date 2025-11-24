#include<iostream>
#include<vector>
#include<complex>
#include<cmath>
#include<climits>

using namespace std;
// Definicion de tipo para complex<double>
typedef complex<double> Complex;
// Definicion de Pi
const double PI = acos(-1);

// Funcion que calcula la Transformada Rapida de Fourier (FFT)
// a: vector de complejos
// invert: indica si se calcular FFT o IFFT (Transformada Rapida Inversa de Fourier)
void fft(vector<Complex>& a, bool invert){
	int n = a.size();
	
	if (n == 1) return;

	vector<Complex> a0(n / 2), a1(n / 2);

	// Dividir el vector a en pares (a0) e impares (a1)
	for(int i = 0; i < n/2; i++){
		a0[i] = a[2*i];
		a1[i] = a[2*i + 1];
	}

	fft(a0, invert);
	fft(a1, invert);

	// Angulo
	double angle = (2*PI)/n;
	// Si IFFT, cambiar signo del angulo
	if (invert) angle *= -1;
	
	// Inicializar w en 1 + 0i
	Complex w = {1, 0};
	// w_n = cos(angle) + i*sin(angle)
	Complex w_n = {cos(angle), sin(angle)};

	// Combinar resultados de las llamadas recursivas
	for (int i = 0; i < n/2; i++){
		a[i] = a0[i] + w*a1[i];
		a[i+n/2] = a0[i] - w*a1[i];
		w *= w_n;
	}
}

int main(){
	int n;
	cout << "Ingrese un numero: ";
	cin >> n;

	// Vector de la cantidad de divisores para el indice i
	vector<int> d(2*n, 0);
	
	for (int i = 1; i < n+1; i++){
		for(int p = i; p < n+1; p+=i){
			d[p]++;
		}
	}

	// Calcular el tamaño de fa (potencia de 2 mas cercana)
    int size = 1;
    while (size <= 2 * n) size *= 2;

	// Inicializar vector fa (vector de complejos) con tamaño size
    vector<Complex> fa(size);

    for (int i = 0; i <= n; i++) {
        fa[i] = d[i]; 
        // La parte imaginaria se queda en 0 por defecto
    }

	// Calcular FFT
	fft(fa, false);

	// Elevar al cuadrado cada elemento del vector fa
	for (int i = 0; i < size; i++){
		fa[i]*=fa[i];
	}

	// Calcular IFFT
	fft(fa, true);

	// Normalizar, redondear los elementos de fa y calcular el maximo valor
	int idx = -1;
	long long max_descomp = INT_MIN;
	for (int i = 0; i<size; i++){
		if (round(fa[i].real() / size) > max_descomp && i <= n) {
			max_descomp = round(fa[i].real() / size);
			idx = i;
		}
	}
	cout << "X = " << idx << "\nMaximo valor de decomp(" << idx << ") = " << max_descomp << endl;
}