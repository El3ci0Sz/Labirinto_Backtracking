#include "../include/Backtracking.h"
/*
 Função:
    Função recursiva que tem como objetivo encontrar uma saida valida em um labirinto, utilizando Backtracking.

 inputs:
    labirinto (Labirinto):Struct que contem os dados da tabela e variaveis auxiliares.
    linha (int) & coluna (int): São os indices, da posição inicial.
    movimentos (*int): Armazena a quantidade de movimentos.
    coluna_final: Armazena o indice da coluna em que que se chegou ao final.

 output:
    true se o labirinto tem uma saida.
    false se o labirinto nao tem uma saida.
*/

bool movimenta_estudante(Labirinto *labirinto, int linha, int coluna, int *movimentos, int *coluna_final) {
    // Imprime a posição atual em cada iteração.
    printf("Linha: %d Coluna: %d\n", linha, coluna);
    (*movimentos)++;

    // Verifica se chegou ao final do Labirinto.
    if (linha == 0) {
        (*coluna_final) = coluna;
        return true;
    }

    // Marca a posição atual como visitada.
    int temp = labirinto->matriz[linha][coluna];
    labirinto->matriz[linha][coluna] = -1;

    // Tenta cada um dos 4 possíveis: cima, baixo, direita, esquerda.
    int movimentos_linha[] = {-1, 1, 0, 0};
    int movimentos_coluna[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int nova_linha = linha + movimentos_linha[i];
        int nova_coluna = coluna + movimentos_coluna[i];

        // Verifica se o movimento pode ser feito, e o que deve ser feito, dependendo do conteudo de cada célula.
        if (nova_linha >= 0 && nova_linha < labirinto->linhas && nova_coluna >= 0 && nova_coluna < labirinto->colunas) {
            if (labirinto->matriz[nova_linha][nova_coluna] == 1 || labirinto->matriz[nova_linha][nova_coluna] == 3) {
                bool chave_usada = false;

                //Célula [3], Porta.
                if (labirinto->matriz[nova_linha][nova_coluna] == 3) {
                    if (labirinto->chaves > 0) {
                        labirinto->chaves--; 
                        chave_usada = true;
                    } else {
                        continue; 
                    }
                }

                //Recursividade:
                if (movimenta_estudante(labirinto, nova_linha, nova_coluna, movimentos, coluna_final)) {
                    return true;
                }

                if (chave_usada) {
                    labirinto->chaves++;
                }
            }
        }
    }

    //Caso nenhum dos movimentos funcione, Backtracking:
    labirinto->matriz[linha][coluna] = temp;
    return false;
}

/*
Função:
    Chama a função recursiva movimenta_estudante para inciar a busca por uma saida, e imprime a saida
    achada ou se não a saida, ao final.

input:
    labirinto (Labirinto): Struct que contem os dados da tabela e variaveis auxiliares.
*/

void backtracking_labirinto(Labirinto *labirinto) {
    int linha_inicial = -1;
    int coluna_inicial = -1;

    // Localiza a posição inicial do estudante.
    for (int i = 0; i < labirinto->linhas; i++) {
        for (int j = 0; j < labirinto->colunas; j++) {
            if (labirinto->matriz[i][j] == 0) {
                linha_inicial = i;
                coluna_inicial = j;
                break;
            }
        }
        if (linha_inicial != -1) {
            break;
        }
    }

    if (linha_inicial == -1 || coluna_inicial == -1) {
        printf("Labirinto inválido: sem posição inicial.\n");
        return;
    }

    int movimentos = 0;
    int coluna_final = 0;

    if (movimenta_estudante(labirinto, linha_inicial, coluna_inicial, &movimentos, &coluna_final)) {
        printf("O estudante se movimentou %d vezes e chegou na coluna %d da primeira linha.\n", movimentos, coluna_final);
    } else {
        printf("O estudante se movimentou %d vezes e percebeu que o labirinto nao tem saida.\n", movimentos);
    }
}

