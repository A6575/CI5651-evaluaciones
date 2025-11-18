#include <iostream>
#include <string>
#include <vector>

using namespace std;
/**
 * Funcion para calcular el arreglo LPS (Longest Proper Prefix Suffix).
 */
 vector<int> compute_LPS(const string& s) {
    int n = s.length();
    if (n == 0) {
        return {};
    }
    vector<int> lps(n, 0);

	// 'len' almacena la longitud del lps anterior (lps[i-1]).
    int len = 0;
	// Se empieza desde i = 1, ya que lps[0] siempre es 0.
    int i = 1;

	while(i < n){
		// Si los caracteres coinciden, se aumenta la longitud del prefijo-sufijo.
		// y se asigna la longitud encontrada a lps[i].
		if (s[i] == s[len]){
			len++; lps[i] = len; i++;
		}else if (len != 0){
			// Si los caracteres no coinciden, se retrocede usando los valores
        	// de lps ya calculados
			len = lps[len-1];
		}else{
			// Si los caracteres no coinciden, y len = 0, se marca
			// como 0
			lps[i] = 0; i++;
		}
	}
    return lps;
}

/**
 * Funcion para buscar la sub-cadena T del string s
 */
string find_substring_T(const string& s) {
    // Calcular el arreglo LPS.
    vector<int> lps = compute_LPS(s);

    if (lps.empty()) {
        return "";
    }

    int L = lps.back(); // lps.back() es lo mismo que lps[n-1]

    // La respuesta es el prefijo de S de longitud L.
    return s.substr(0, L);
}

int main() {
    // 1. El carné de la pregunta anterior
    string s_carnet = "arepera";
    string t_carnet = find_substring_T(s_carnet);
    cout << "Cadena: \"" << s_carnet << "\"" << endl;
    cout << "Respuesta: \"" << t_carnet << "\"" << endl; // lps.back() = 1. Respuesta: "a"
    cout << "---" << endl;

    // 2. El ejemplo "trampa"
    string s_test1 = "abcxyzabcuvw";
    string t_test1 = find_substring_T(s_test1);
    cout << "Cadena: \"" << s_test1 << "\"" << endl;
    // El lps termina en [..., 3, 0, 0, 0]
    cout << "Respuesta: \"" << t_test1 << "\"" << endl; // lps.back() = 0. Respuesta: ""
    cout << "---" << endl;

    // 3. Un ejemplo con respuesta larga
    string s_test2 = "abracadabra";
    string t_test2 = find_substring_T(s_test2);
    cout << "Cadena: \"" << s_test2 << "\"" << endl;
    // El lps termina en [..., 3, 4]
    cout << "Respuesta: \"" << t_test2 << "\"" << endl; // lps.back() = 4. Respuesta: "abra"
    cout << "---" << endl;

    // 4. Un ejemplo sin respuesta
    string s_test3 = "abcdefg";
    string t_test3 = find_substring_T(s_test3);
    cout << "Cadena: \"" << s_test3 << "\"" << endl;
    cout << "Respuesta: \"" << t_test3 << "\"" << endl; // lps.back() = 0. Respuesta: ""
    cout << "---" << endl;
    
    // 5. Un ejemplo con superposición
    string s_test4 = "aaaaa";
    string t_test4 = find_substring_T(s_test4);
    cout << "Cadena: \"" << s_test4 << "\"" << endl;
    // El lps es [0, 1, 2, 3, 4]
    cout << "Respuesta: \"" << t_test4 << "\"" << endl; // lps.back() = 4. Respuesta: "aaaa"
    cout << "---" << endl;

    return 0;
}