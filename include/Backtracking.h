#ifndef UNTITLED1_BACKTRACKING_H
#define UNTITLED1_BACKTRACKING_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Labirinto.h"

void backtracking_labirinto(Labirinto* labirinto);
bool movimenta_estudante(Labirinto *labirinto, int linha, int coluna, int *movimentos_totais, int * coluna_final);

#endif //UNTITLED1_BACKTRACKING_H
