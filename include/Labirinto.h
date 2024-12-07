#ifndef LABIRINTO_H
#define LABIRINTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int linha;
    int coluna;
} Posicao;


// Representação do labirinto completo
typedef struct {
    int linhas;
    int colunas;
    int chaves;
    int** matriz;
    int movimentos;
} Labirinto;

// Funções do labirinto
Labirinto* carregar_labirinto(const char* nome_arquivo);
void liberar_labirinto(Labirinto* labirinto);


#endif // LABIRINTO_H
