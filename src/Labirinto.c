#include "../include/Labirinto.h"
#include "../include/Backtracking.h"

Labirinto* carregar_labirinto(const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    Labirinto* labirinto = (Labirinto*)malloc(sizeof(Labirinto));
    if (!labirinto) {
        printf("Erro de memória.\n");
        fclose(arquivo);
        return NULL;
    }

    if (fscanf(arquivo, "%d %d %d\n", &labirinto->linhas, &labirinto->colunas, &labirinto->chaves) != 3) {
        printf("Erro ao ler as dimensões ou chaves do labirinto.\n");
        free(labirinto);
        fclose(arquivo);
        return NULL;
    }

    labirinto->matriz = (int**)malloc(labirinto->linhas * sizeof(int*));
    for (int i = 0; i < labirinto->linhas; i++) {
        labirinto->matriz[i] = (int*)malloc(labirinto->colunas * sizeof(int));
    }

    for (int i = 0; i < labirinto->linhas; i++) {
        for (int j = 0; j < labirinto->colunas; j++) {
            char c;
            fscanf(arquivo, "%c", &c);
            labirinto->matriz[i][j] = c - '0';
        }
        fgetc(arquivo);
    }

    fclose(arquivo);
    return labirinto;
}

void liberar_labirinto(Labirinto* labirinto) {
    if (!labirinto) return;
    for (int i = 0; i < labirinto->linhas; i++) {
        free(labirinto->matriz[i]);
    }
    free(labirinto->matriz);
    free(labirinto);
}



