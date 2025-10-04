/* 
    Implementación de pseudo-código propuesto.

 * Detalles de implementación:
      - En lugar de tener una estructura especial "Canciones", se decidió trabajar con 3 vectores:
            + init: vector para almacenar el tiempo en que inician cada canción
            + duration: vector para almacenar la duración de cada canción
            + finish: vector de pares para almacenar el tiempo de finalización y el id de cada canción.
        En estos vectores, el id de las canciones serán representadas por los índices del arreglo, por
        lo que la canción i será equivalente al índice i.

      - Se ordena el vector de pares por tiempo de finalización.

      - Se selecciona la primera canción y se compara el tiempo de inicio de las siguientes
      canciones con el tiempo de finalización de la última canción seleccionada.

      - Si el tiempo de inicio de la canción actual es mayor o igual al tiempo de
        finalización de la última canción seleccionada, se agrega a la lista de canciones seleccionadas.

      - Se devuelve el vector de índices de las canciones seleccionadas.

 * Ejemplo de uso:
      - Se define un vector de tiempos de inicio y otro de duraciones de canciones. En el índice 0 de cada
        vector se coloca -1 como valor dummie para asegurar un correcto comportamiento del algoritmo.

      - Se llama a la función `select_songs` con estos vectores.

      - Se imprime el resultado de las canciones seleccionadas.

      - El resultado es un vector de índices de las canciones seleccionadas.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> select_songs(vector<int> init, vector<int> duration){
    vector<pair<int, int>> finish_time(init.size(), make_pair(-1,-1));
    vector<int> selected;

    for (size_t song = 1; song < init.size(); song++) {
        finish_time[song] = make_pair(init[song] + duration[song], song);
    }

    sort(finish_time.begin(), finish_time.end(), [](pair<int, int> a, pair<int, int> b) {
        return a.first < b.first;
    });

    selected.push_back(finish_time[1].second);
    int last_finish = finish_time[1].first;  
    for (size_t i = 2; i < finish_time.size(); i++) {
        if (init[finish_time[i].second] >= last_finish) {
            selected.push_back(finish_time[i].second);
            last_finish = finish_time[i].first;
        }
    }
    return selected;
}

int main() {
    //Canciones                 1  2  3
    vector<int> init     = {-1, 1, 2, 3};
    vector<int> duration = {-1, 4, 1, 3};
    vector<int> selected = select_songs(init, duration);
    cout << "Selected songs: { ";
    for (int i : selected) {
        cout << i << " ";
    }
    cout << "}" << endl;
    return 0;
}