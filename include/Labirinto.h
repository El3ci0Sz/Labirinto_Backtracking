#ifndef LABIRINTO_H
#define LABIRINTO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Representação de uma posição no labirinto
typedef struct {
    int linha;
    int coluna;
} Posicao;

// Representação do labirinto completo
typedef struct {
    int linhas;   // Número de linhas
    int colunas;  // Número de colunas
    int chaves;   // Número de chaves disponíveis
    int** matriz; // Matriz representando o labirinto
} Labirinto;

// Funções do labirinto
Labirinto* carregar_labirinto(const char* nome_arquivo);
void liberar_labirinto(Labirinto* labirinto);

// Verificação e manipulação
bool posicaoValida(Labirinto* labirinto, int linha, int coluna);
bool ehObjetivo(Labirinto* labirinto, int linha, int coluna);

#endif // LABIRINTO_H
