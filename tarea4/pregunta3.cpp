#include <iostream>
#include <vector>
#include <climits>
#include <string>
#include <sstream>

using namespace std;

// Clase para inicializacion virtual de arreglos
class VirtualInitializer {
	int size;			// Tamaño del arreglo
	int counter = 0;	// Contador de posiciones inicializadas en el arreglo
	vector<int> data;	// Arreglo de datos
	vector<int> a;		// Arreglo auxiliar para mapeo de posiciones (a[0] no se usa). Recuerda el orden de inicializacion
	vector<int> b;		// Arreglo auxiliar para mapeo de posiciones. Recuerda cuando se inicializo una posicion
	
	public:
		// Constructor
		VirtualInitializer(int size) : size(size) {
			data.resize(size); a.resize(size+1); b.resize(size);
		}

		// Metodo para asignar un valor en una posicion del arreglo
		void asignar(int pos, int val) {
			this->b[pos] = ++counter;	// Marca el tiempo de inicializacion
			this->a[counter] = pos;		// Guarda la posicion inicializada
			this->data[pos] = val;		// Asigna el valor en la posicion
		}

		// Metodo para consultar el valor en una posicion del arreglo
		int consultar(int pos) {
			// Si la posicion no ha sido inicializada, retorna INT_MIN como indicador
			if (this->b[pos] < 1 || this->b[pos] > this->counter || this->a[this->b[pos]] != pos) {
				return INT_MIN;
			}
			return this->data[pos];
		}
		// Metodo para limpiar todos los arreglos
		void limpiar() {
			// Recorre las posiciones inicializadas y las resetea
			while (this->counter > 0) {
				int pos = this->a[this->counter--];
				this->b[pos] = INT_MAX;
				this->data[pos] = INT_MAX;
			}
		}

};

// Funcion principal
int main(int argc, char* argv[]) {
	// Verifica que se haya proporcionado el tamaño del arreglo como argumento
	if (argc != 2) {
        cout << "Uso: ./pregunta3 <size>" << endl;
        return 1;
    }

	// Convierte el argumento a entero
    int size;
    try {
        size = stoi(argv[1]);
    } catch (const invalid_argument&) {
        cout << "Error: Tamaño inválido. Por favor ingrese un número entero." << endl;
        return 1;
    }

	// Verifica que el tamaño sea positivo
    if (size <= 0) {
        cout << "Error: El tamaño debe ser un entero positivo." << endl;
        return 1;
    }

    cout << "--- Inicializacion virtual de arreglos ---\n\n";
    cout << "- Opciones disponibles:\n";
    cout << "  ASIGNAR POS VAL -> Asigna el valor VAL a la posición POS del arreglo.\n";
    cout << "  CONSULTAR POS -> Consulta el valor en la posición POS del arreglo.\n";
    cout << "  LIMPIAR -> Limpia todos los arreglos.\n";
    cout << "  SALIR -> Termina la ejecución del programa.\n\n";

	// Crea una instancia de VirtualInitializer
    VirtualInitializer initializer(size);

	// Bucle principal para procesar comandos del usuario
    while (true) {
        cout << "Ingrese un comando: ";
        string command;
		getline(cin, command);
		stringstream ss(command);
		ss >> command;
		
        if (command == "SALIR") {
            cout << "Terminando la ejecución." << endl;
            break;
        } else if (command == "ASIGNAR") {
            try {
                int pos, val;
                ss >> pos >> val;

                if (pos < 0 || pos >= size) {
                    cout << "Error: La posición " << pos << " está fuera de los límites del arreglo." << endl;
                    continue;
                }

                initializer.asignar(pos, val);
                cout << "Asignando valor " << val << " en la posición " << pos << "." << endl;
            } catch (const exception &e) {
                cout << "Error al procesar ASIGNAR: " << e.what() << endl;
            }
        } else if (command == "CONSULTAR") {
            try {
                int pos;
                ss >> pos;

                if (pos < 0 || pos >= size) {
                    cout << "Error: La posición " << pos << " está fuera de los límites del arreglo." << endl;
                    continue;
                }

                int value = initializer.consultar(pos);
                if (value == INT_MIN) {
                    cout << "La posición " << pos << " no ha sido asignada previamente." << endl;
                } else {
                    cout << "Valor en la posición " << pos << ": " << value << endl;
                }
            } catch (const exception &e) {
                cout << "Error al procesar CONSULTAR: " << e.what() << endl;
            }
        } else if (command == "LIMPIAR") {
            initializer.limpiar();
            cout << "Limpiando todos los arreglos." << endl;
        } else {
            cout << "Comando no reconocido. Por favor intente de nuevo." << endl;
        }
    }

	return 0;
}