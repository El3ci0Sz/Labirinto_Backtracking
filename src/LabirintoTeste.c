#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/Labirinto.h"

// Função para gerar um labirinto aleatório equilibrado
Labirinto* gerar_labirinto_aleatorio(int linhas, int colunas, int num_portas, int num_chaves, int dificuldade) {
    Labirinto* labirinto = (Labirinto*)malloc(sizeof(Labirinto));
    labirinto->linhas = linhas;
    labirinto->colunas = colunas;
    labirinto->chaves = num_chaves;

    // Alocar matriz do labirinto
    labirinto->matriz = (int**)malloc(linhas * sizeof(int*));
    for (int i = 0; i < linhas; i++) {
        labirinto->matriz[i] = (int*)calloc(colunas, sizeof(int)); // Inicializa com 0 (espaços livres)
    }

    // Gerar células aleatórias
    srand(time(NULL));
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            int chance = rand() % 100;

            // Espaços livres (1) têm maior chance
            if (chance < 50) {
                labirinto->matriz[i][j] = 1;
            }
            // Portas (3) controladas pelo número de portas restante
            else if (chance < 70 && num_portas > 0) {
                labirinto->matriz[i][j] = 3;
                num_portas--;
            }
            // Paredes (2) reduzidas, mas ainda presentes com base na dificuldade
            else if (chance < 90) {
                labirinto->matriz[i][j] = 2;
            }
            // Espaços livres adicionais
            else {
                labirinto->matriz[i][j] = 1;
            }
        }
    }

    // Definir ponto inicial (0) na metade inferior da matriz
    // A linha inicial será aleatória entre a metade inferior da matriz
    int inicio_linha = rand() % (linhas / 2) + (linhas / 2); // Garante que esteja na metade inferior
    int inicio_coluna = rand() % colunas; // Pode ser qualquer coluna

    // Coloca o ponto inicial na posição calculada
    labirinto->matriz[inicio_linha][inicio_coluna] = 0;

    // Garantir que cada parede tenha pelo menos 3 caminhos ao redor
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (labirinto->matriz[i][j] == 2) {
                int caminhos = 0;
                int direcoes[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Cima, Baixo, Esquerda, Direita

                for (int k = 0; k < 4; k++) {
                    int ni = i + direcoes[k][0];
                    int nj = j + direcoes[k][1];
                    if (ni >= 0 && ni < linhas && nj >= 0 && nj < colunas &&
                        labirinto->matriz[ni][nj] != 2) {
                        caminhos++;
                    }
                }

                // Se houver menos de 3 caminhos, substitui a parede por espaço vazio
                if (caminhos < 3) {
                    labirinto->matriz[i][j] = 1;
                }
            }
        }
    }

    return labirinto;
}
