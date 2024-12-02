#ifndef LABIRINTO_H
#define LABIRINTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int linhas;
    int colunas;
    int chaves;
    int** matriz;
} Labirinto;

Labirinto* carregar_labirinto(const char* nome_arquivo);
void liberar_labirinto(Labirinto* labirinto);

#endif //LABIRINTO_H