#include <stdio.h>
#include <stdbool.h>

#define LINHAS 10
#define COLUNAS 10

// Estrutura para armazenar a posição no labirinto
typedef struct {
    int linha;
    int coluna;
} Posicao;

// Função recursiva de movimentação
bool movimenta_estudante(int labirinto[LINHAS][COLUNAS], int linha, int coluna, int *movimentos_totais) {
    // Imprime a posição atual
    printf("Linha: %d Coluna: %d\n", linha, coluna);
    (*movimentos_totais)++;

    // Verifica se chegou na primeira linha (linha 0)
    if (linha == 0) {
        return true;
    }

    // Marca a posição atual como visitada
    int temp = labirinto[linha][coluna];
    labirinto[linha][coluna] = -1;

    // Movimentos possíveis: cima, direita, baixo, esquerda
    int movimentos_linha[] = {-1, 0, 1, 0};
    int movimentos_coluna[] = {0, 1, 0, -1};

    // Tenta cada direção
    for (int i = 0; i < 4; i++) {
        int nova_linha = linha + movimentos_linha[i];
        int nova_coluna = coluna + movimentos_coluna[i];

        // Verifica se o movimento é válido
        if (nova_linha >= 0 && nova_linha < LINHAS && nova_coluna >= 0 && nova_coluna < COLUNAS) {
            if (labirinto[nova_linha][nova_coluna] == 1 || labirinto[nova_linha][nova_coluna] == 3) {
                // Se for célula vermelha (3), verifica chave
                if (labirinto[nova_linha][nova_coluna] == 3 && temp == 3) {
                    // Célula vermelha acessada sem chave, ignora
                    continue;
                }

                if (movimenta_estudante(labirinto, nova_linha, nova_coluna, movimentos_totais)) {
                    return true;
                }
            }
        }
    }

    // Volta para a posição anterior (backtracking)
    labirinto[linha][coluna] = temp;
    return false;
}

void backtracking_labirinto(int labirinto[LINHAS][COLUNAS]) {
    Posicao inicial = {-1, -1};

    // Localiza a posição inicial do estudante (célula 0)
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (labirinto[i][j] == 0) {
                inicial.linha = i;
                inicial.coluna = j;
                break;
            }
        }
        if (inicial.linha != -1) {
            break;
        }
    }

    if (inicial.linha == -1) {
        printf("Labirinto inválido: sem posição inicial.\n");
        return;
    }

    int movimentos_totais = 0;

    if (movimenta_estudante(labirinto, inicial.linha, inicial.coluna, &movimentos_totais)) {
        printf("O estudante se movimentou %d vezes e chegou na primeira linha.\n", movimentos_totais);
    } else {
        printf("O estudante se movimentou %d vezes e percebeu que o labirinto nao tem saida.\n", movimentos_totais);
    }
}

int main() {
    int labirinto[LINHAS][COLUNAS] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 1, 1},
        {1, 2, 1, 1, 1, 1, 1, 2, 1, 1},
        {1, 2, 1, 2, 2, 2, 1, 2, 1, 1},
        {1, 2, 1, 2, 1, 1, 1, 2, 1, 1},
        {1, 2, 1, 2, 1, 2, 2, 2, 1, 1},
        {1, 1, 1, 2, 1, 1, 1, 1, 1, 1},
        {1, 2, 2, 2, 1, 2, 2, 2, 2, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    backtracking_labirinto(labirinto);

    return 0;
}
