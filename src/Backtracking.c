#include "../include/Backtracking.h"
#define MODO_ANALISE

//Definição das variaveis do modo analise.
#ifdef MODO_ANALISE
    int numero_chamadas_recursivas = 0;
    int nivel_atual = 0;
    int profundidade = 0;
#endif

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
    #ifdef MODO_ANALISE
        numero_chamadas_recursivas++;
        nivel_atual++;
        if (nivel_atual > profundidade) {
            profundidade = nivel_atual;
        }
    #endif

    // Imprime a posição atual
    printf("Linha: %d Coluna: %d\n", linha+1, coluna+1);
    (*movimentos)++;

    // Verifica se chegou ao final
    if (linha == 0) {
        (*coluna_final) = coluna;

        #ifdef MODO_ANALISE
            nivel_atual--;
        #endif

        return true;
    }

    // Marca a posição como visitada
    int temp = labirinto->matriz[linha][coluna];
    labirinto->matriz[linha][coluna] = -1;

    // Movimentos possíveis
    int movimentos_linha[] = {-1, 1, 0, 0};
    int movimentos_coluna[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int nova_linha = linha + movimentos_linha[i];
        int nova_coluna = coluna + movimentos_coluna[i];

        if (nova_linha >= 0 && nova_linha < labirinto->linhas && nova_coluna >= 0 && nova_coluna < labirinto->colunas) {
            if (labirinto->matriz[nova_linha][nova_coluna] == 1 || labirinto->matriz[nova_linha][nova_coluna] == 3|| 
                labirinto->matriz[nova_linha][nova_coluna] == 4) {
                bool chave_usada = false;
                bool chave_pega_chao = false;

                // Celula [3] = Porta.

                if (labirinto->matriz[nova_linha][nova_coluna] == 3) {
                    if (labirinto->chaves > 0) {
                        labirinto->chaves--; 
                        chave_usada = true;
                    } else {
                        continue;
                    }
                }

                //Celuna [4] = Chave no chão.

                if (labirinto->matriz[nova_linha][nova_coluna] == 4) {
                    labirinto->chaves++;
                    chave_pega_chao = true;
                }

                // Chamada recursiva
                if (movimenta_estudante(labirinto, nova_linha, nova_coluna, movimentos, coluna_final)) {
                    #ifdef MODO_ANALISE
                        nivel_atual--;
                    #endif
                    return true;
                }

                // Caso tenha ido para o caminho errado e esteja voltando, devolve as chaves:
                if (chave_pega_chao) {
                    labirinto->chaves--;
                }

                if (chave_usada) {
                    labirinto->chaves++;
                }
            }
        }
    }

    // Backtracking
    labirinto->matriz[linha][coluna] = temp;

    #ifdef MODO_ANALISE
        nivel_atual--;
    #endif

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
    #ifdef MODO_ANALISE
        numero_chamadas_recursivas = 0;
        nivel_atual = 0;
        profundidade = 0;
    #endif

    int linha_inicial = -1;
    int coluna_inicial = -1;
    int movimentos = 0;
    int coluna_final = 0;
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
    
    if (movimenta_estudante(labirinto, linha_inicial, coluna_inicial, &movimentos, &coluna_final)) {
        printf("O estudante se movimentou %d vezes e chegou na coluna %d da primeira linha.\n", movimentos, coluna_final + 1);
    } else {
        printf("O estudante se movimentou %d vezes e percebeu que o labirinto nao tem saida.\n", movimentos);
    }
    #ifdef MODO_ANALISE
        printf("\nANALISE:\nNIVEL MAXIMO DE RECURSIVIDADE: %d\nNUMERO TOTAL DE CHAMADAS RECURSIVAS: %d\n\n",profundidade,numero_chamadas_recursivas);
    #endif
}

