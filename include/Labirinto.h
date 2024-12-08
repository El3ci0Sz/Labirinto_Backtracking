#ifndef LABIRINTO_H
#define LABIRINTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



// Struct que representa o labirinto, e que contem algumas variaveis auxiliares.
typedef struct {
    int linhas;
    int colunas;
    int chaves;
    int** matriz;
    int movimentos;
} Labirinto;

// Funções de criação do Labirinto.
Labirinto* carregar_labirinto(const char* nome_arquivo);
void liberar_labirinto(Labirinto* labirinto);
void exibir_labirinto_visual(Labirinto* labirinto);


#endif // LABIRINTO_H
