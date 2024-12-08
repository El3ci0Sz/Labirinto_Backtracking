#include "../include/LabirintoTeste.h"
#include <time.h>

/*
    Função:
        Apartir da funcao rand(), essa função cria um labirinto e preenche cada célula
        adequadamente, de acordo com a difuculdade ja setada antes de executar o codigo.
    input:
        Labirinto(Labirinto): int linhas, int colunas, int chaves, int portas, int dificuldade
    output:
        labirinto (Labirinto): Retorna uma Struct do tipo Labirinto.
*/
Labirinto* gerar_labirinto_aleatorio(int linhas, int colunas, int chaves, int portas, int dificuldade) {
    if (linhas <= 0 || colunas <= 0 || dificuldade < 0 || dificuldade > 100) {
        printf("Parâmetros inválidos para geração do labirinto.\n");
        return NULL;
    }

    srand(time(NULL));

    Labirinto* labirinto = malloc(sizeof(Labirinto));
    labirinto->linhas = linhas;
    labirinto->colunas = colunas;
    labirinto->chaves = chaves;
    labirinto->movimentos = 0;

    labirinto->matriz = malloc(linhas * sizeof(int*));
    for (int i = 0; i < linhas; i++) {
        labirinto->matriz[i] = malloc(colunas * sizeof(int));
    }

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            int chance = rand() % 100;

            // Fórmula para diminuir a probabilidade de paredes mesmo em dificuldades altas
            int probabilidade_parede = dificuldade - (dificuldade / 6); 
            if (chance < probabilidade_parede) {
                labirinto->matriz[i][j] = 2; // Parede
            } else {
                labirinto->matriz[i][j] = 1; // Espaço vazio
            }
        }
    }
    
    int ponto_inicial_coluna = rand() % colunas;
    int ponto_inicial_linha = linhas / 2 + rand() % (linhas / 2);
    labirinto->matriz[ponto_inicial_linha][ponto_inicial_coluna] = 0;

    // Adiciona portas 
    for (int i = 0; i < portas; i++) {
        int porta_linha, porta_coluna;
        do {
            porta_linha = rand() % linhas;
            porta_coluna = rand() % colunas;
        } while (labirinto->matriz[porta_linha][porta_coluna] != 1);
        labirinto->matriz[porta_linha][porta_coluna] = 3;
    }

    // Adiciona chaves 
    for (int i = 0; i < chaves; i++) {
        int chave_linha, chave_coluna;
        do {
            chave_linha = rand() % linhas;
            chave_coluna = rand() % colunas;
        } while (labirinto->matriz[chave_linha][chave_coluna] != 1);
        labirinto->matriz[chave_linha][chave_coluna] = 4;
    }

    return labirinto;
}
