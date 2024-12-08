#ifndef BACKTRACKING_H
#define BACKTRACKING_H
#include "Labirinto.h"

//Funções que promovem a busca por uma saida do labirinto.
void backtracking_labirinto(Labirinto* labirinto);
bool movimenta_estudante(Labirinto *labirinto, int linha, int coluna, int *movimentos_totais, int * coluna_final);

#endif //BACKTRACKING_H
