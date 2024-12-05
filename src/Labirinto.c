#include "../include/Labirinto.h"

Labirinto* cria_labirinto_vazio(int linhas, int colunas) {
    // Aloca memória para a estrutura Labirinto
    Labirinto* labirinto = (Labirinto*)malloc(sizeof(Labirinto));
    if (labirinto == NULL) {
        printf("Erro: Falha ao alocar memória para o labirinto.\n");
        return NULL;
    }

    labirinto->linhas = linhas;
    labirinto->colunas = colunas;

    // Aloca memória para a matriz do labirinto
    labirinto->matriz = (int**)malloc(linhas * sizeof(int*));
    if (labirinto->matriz == NULL) {
        printf("Erro: Falha ao alocar memória para as linhas do labirinto.\n");
        free(labirinto);
        return NULL;
    }

    for (int i = 0; i < linhas; i++) {
        labirinto->matriz[i] = (int*)malloc(colunas * sizeof(int));
        if (labirinto->matriz[i] == NULL) {
            printf("Erro: Falha ao alocar memória para as colunas do labirinto.\n");
            for (int j = 0; j < i; j++) {
                free(labirinto->matriz[j]);
            }
            free(labirinto->matriz);
            free(labirinto);
            return NULL;
        }

        // Inicializa todas as posições como 0
        for (int j = 0; j < colunas; j++) {
            labirinto->matriz[i][j] = 0;
        }
    }

    return labirinto;
}

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
            if(celula == '3'){
                labirinto->posicao_inicial[0] = i;
                labirinto->posicao_inicial[1] = j;
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
                    printf("\033[0;31m| "); // Porta em vermelho
                    break;
                case 4:
                    printf("\033[0;33m| "); // Chave no chão em amarelo
                    break;
                default:
                    printf("\033[0m? "); // Caractere desconhecido sem cor
                    break;
            }
        }
        printf("\033[0m\n");
    }
}
