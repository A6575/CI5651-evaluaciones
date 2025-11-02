#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
using namespace std;

class GameState{
    vector<string> board;
	int current_player;
	pair<int, int> illegal_move;
public:
	// constructor
	GameState(int player, vector<string> board, pair<int, int> illegal_move): board(board), current_player(player), illegal_move(illegal_move) {}
	
	bool is_winner(){
		for (int row = 0; row < 3; row++){
			if (this->board[row][0] == '+' && this->board[row][1] == '+' && this->board[row][2] == '+') return true;
		}

		for (int col = 0; col < 3; col++){
			if (this->board[0][col] == '+' && this->board[1][col] == '+' && this->board[2][col] == '+') return true;
		}

		if (this->board[0][0] == '+' && this->board[1][1] == '+' && this->board[2][2] == '+') return true;
		if (this->board[0][2] == '+' && this->board[1][1] == '+' && this->board[2][0] == '+') return true;

		return false;
	}
	bool is_legal_move(int row, int col){
		if (row == this->illegal_move.first && col == this->illegal_move.second){
			return false;
		}
		// 2. Ver si la casilla está vacía
		char contenido_casilla = this->board[row][col];
		if (contenido_casilla == '#') {
			return true;
		}

		// 3. Ver si la casilla tiene la "ficha" del oponente
		if (this->current_player == 1 && contenido_casilla == '|') { // Jugador 1 ('-') juega sobre '|'
			return true;
		}
		if (this->current_player == -1 && contenido_casilla == '-') { // Jugador 2 ('|') juega sobre '-'
			return true;
		}

		return false;
	}

	bool find_legal_moves(){
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				// Si encontramos UNA sola casilla legal...
				if (this->is_legal_move(i, j)) {
					return true;
				}
			}
		}
		// Si el bucle termina, es porque no encontró nada.
		return false; // ¡Es un empate!
	}

	int eval_state(){
		if (this->is_winner()) {
			return -this->current_player;
		}

		if (!this->find_legal_moves()){
			return 0;
		}

		return 2;
	}

	int minimax(){
		int state_val = this->eval_state();
		
		if (state_val != 2){
			return state_val;
		}

		int best_val;

		if(this->current_player == 1){
			best_val = INT16_MIN;
		}else{
			best_val = INT16_MAX;
		}

		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				if (this->is_legal_move(i, j)){
					GameState next_state = *this;
					char original_tile = next_state.board[i][j];

					if (original_tile == '#') {
						// Si está vacío, pone su ficha
						char player_piece = (this->current_player == 1) ? '-' : '|';
						next_state.board[i][j] = player_piece;
					} else {
						// Si no está vacío (es del oponente), se forma una '+'
						next_state.board[i][j] = '+';
					}
					
					// 1c. Modificación 2: Cambiar el jugador actual
					//     (Un truco simple: multiplicar por -1 cambia 1 a -1 y -1 a 1)
					next_state.current_player = -this->current_player;
					
					// 1d. Modificación 3: Marcar la casilla prohibida
					next_state.illegal_move = {i, j}; // {fila, columna}

					int new_best_val = next_state.minimax();

					if (this->current_player == 1){
						best_val = max(best_val, new_best_val);
					} else {
						best_val = min(best_val, new_best_val);
					}
				}
			}
		}

		return best_val;
	}
};

int main(){
	// --- PASO 1: Crear el "estado raíz" Jugador actual es 1 (MAX) ---
    GameState estado_raiz(1, {"+-|", "|-+", "|+|"}, {2, 2});
    // --- PASO 2: Llamar a minimax ---
    // ¡Aquí es donde ocurre toda la magia!
    // Esta sola llamada explorará todo el árbol del juego.
    cout << "Calculando el resultado del juego..." << endl;
    int resultado_final = estado_raiz.minimax();

    // --- PASO 3: Interpretar el resultado ---
    // La tarea pregunta: "¿Diga si hay una estrategia ganadora
    //                     para alguno de los jugadores?"

    if (resultado_final == 1) {
        cout << "El Jugador 1 (-) tiene una estrategia ganadora." << endl;
    } else if (resultado_final == -1) {
        cout << "El Jugador 2 (|) tiene una estrategia ganadora." << endl;
    } else { // resultado_final == 0
        cout << "Ningún jugador tiene una estrategia ganadora (el juego perfecto es un empate)." << endl;
    }
	return 0;
}