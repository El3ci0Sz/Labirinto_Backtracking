#include "../include/Labirinto.h"

// Função para carregar o labirinto de um arquivo
Labirinto* carregar_labirinto(const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    Labirinto* labirinto = (Labirinto*)malloc(sizeof(Labirinto));
    if (fscanf(arquivo, "%d %d %d", &labirinto->linhas, &labirinto->colunas, &labirinto->chaves) != 3) {
        fclose(arquivo);
        free(labirinto);
        return NULL;
    }

    labirinto->matriz = (int**)malloc(labirinto->linhas * sizeof(int*));
    for (int i = 0; i < labirinto->linhas; i++) {
        labirinto->matriz[i] = (int*)malloc(labirinto->colunas * sizeof(int));
    }

    for (int i = 0; i < labirinto->linhas; i++) {
        for (int j = 0; j < labirinto->colunas; j++) {
            char celula;
            if (fscanf(arquivo, " %c", &celula) != 1) {
                fclose(arquivo);
                liberar_labirinto(labirinto);
                return NULL;
            }
            labirinto->matriz[i][j] = celula - '0';
        }
    }

    fclose(arquivo);
    return labirinto;
}

// Função para liberar a memória do labirinto
void liberar_labirinto(Labirinto* labirinto) {
    if (labirinto == NULL) return;

    for (int i = 0; i < labirinto->linhas; i++) {
        free(labirinto->matriz[i]);
    }
    free(labirinto->matriz);
    free(labirinto);
}

void imprimir_labirinto(Labirinto* labirinto) {
    printf("%d %d %d\n", labirinto->linhas, labirinto->colunas, labirinto->chaves);
    for (int i = 0; i < labirinto->linhas; i++) {
        for (int j = 0; j < labirinto->colunas; j++) {
            printf("%d", labirinto->matriz[i][j]);
        }
        printf("\n");
    }
}

// Função para exibir o labirinto de forma visual
void exibir_labirinto_visual(Labirinto* labirinto) {
    for (int i = 0; i < labirinto->linhas; i++) {
        for (int j = 0; j < labirinto->colunas; j++) {
            switch (labirinto->matriz[i][j]) {
                case 0:
                    printf("\033[0;32mG "); // Ponto inicial em verde
                    break;
                case 1:
                    printf("\033[0;37m. "); // Espaço vazio em branco
                    break;
                case 2:
                    printf("\033[0;34m# "); // Parede em azul
                    break;
                case 3:
                    printf("\033[0;33m| "); // Porta em amarelo
                    break;
                default:
                    printf("\033[0m? "); // Caractere desconhecido sem cor
                    break;
            }
        }
        printf("\033[0m\n");
    }
}
