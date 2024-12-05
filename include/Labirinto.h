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
    int movimentos;
    int posicao_inicial[2];
} Labirinto;

Labirinto* carregar_labirinto(const char* nome_arquivo);
void liberar_labirinto(Labirinto* labirinto);
void imprimir_labirinto(Labirinto* labirinto);
void exibir_labirinto_visual(Labirinto* labirinto);
Labirinto* cria_labirinto_vazio(int linhas, int colunas);

#endif //LABIRINTO_H
