#include "../include/Backtracking.h"
#include "../include/Labirinto.h"


bool movimenta_estudante(Labirinto *labirinto, int linha, int coluna, int *movimentos_totais, int *coluna_final) {
    // Imprime a posição atual
    printf("Linha: %d Coluna: %d\n", linha, coluna);
    (*movimentos_totais)++;

    // Verifica se chegou na primeira linha (linha 0)
    if (linha == 0) {
        (*coluna_final) = coluna;
        return true;
    }

    // Marca a posição atual como visitada
    int temp = labirinto->matriz[linha][coluna];
    labirinto->matriz[linha][coluna] = -1;

    // Movimentos possíveis: cima, direita, baixo, esquerda
    int movimentos_linha[] = {-1, 0, 1, 0};
    int movimentos_coluna[] = {0, 1, 0, -1};

    // Tenta cada direção
    for (int i = 0; i < 4; i++) {
        int nova_linha = linha + movimentos_linha[i];
        int nova_coluna = coluna + movimentos_coluna[i];

        // Verifica se o movimento é válido
        if (nova_linha >= 0 && nova_linha < labirinto->linhas && nova_coluna >= 0 && nova_coluna < labirinto->colunas) {
            // Se a célula é acessível (1 ou 3)
            if (labirinto->matriz[nova_linha][nova_coluna] == 1 || labirinto->matriz[nova_linha][nova_coluna] == 3) {
                bool usou_chave = false;

                // Se for célula vermelha (3), verifica chave
                if (labirinto->matriz[nova_linha][nova_coluna] == 3) {
                    if (labirinto->chaves > 0) {
                        labirinto->chaves--; // Usa uma chave
                        usou_chave = true;
                    } else {
                        continue; // Sem chave, ignora
                    }
                }

                // Movimenta recursivamente
                if (movimenta_estudante(labirinto, nova_linha, nova_coluna, movimentos_totais, coluna_final)) {
                    return true;
                }

                // Se o movimento falhou, devolve a chave usada
                if (usou_chave) {
                    labirinto->chaves++;
                }
            }
        }
    }

    // Volta para a posição anterior (backtracking)
    labirinto->matriz[linha][coluna] = temp;
    return false;
}

void backtracking_labirinto(Labirinto *labirinto) {
    Posicao inicial = {-1, -1};

    // Localiza a posição inicial do estudante (célula 0)
    for (int i = 0; i < labirinto->linhas; i++) {
        for (int j = 0; j < labirinto->colunas; j++) {
            if (labirinto->matriz[i][j] == 0) {
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
    int coluna_final = 0;

    if (movimenta_estudante(labirinto, inicial.linha, inicial.coluna, &movimentos_totais, &coluna_final)) {
        printf("O estudante se movimentou %d vezes e chegou na coluna %d da primeira linha.\n", movimentos_totais, coluna_final);
    } else {
        printf("O estudante se movimentou %d vezes e percebeu que o labirinto nao tem saida.\n", movimentos_totais);
    }
}

