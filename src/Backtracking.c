#include "../include/Backtracking.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Criação da pilha
Pilha* criarPilha() {
    Pilha* pilha = (Pilha*)malloc(sizeof(Pilha));
    pilha->topo = NULL;
    return pilha;
}

// Empilhar uma posição
void empilhar(Pilha* pilha, Posicao posicao) {
    Nodo* novo_no = (Nodo*)malloc(sizeof(Nodo));
    novo_no->posicao = posicao;
    novo_no->proximo = pilha->topo;
    pilha->topo = novo_no;
}

// Desempilhar uma posição
Posicao desempilhar(Pilha* pilha) {
    if (pilhaVazia(pilha)) {
        Posicao invalida = {-1, -1};
        return invalida; // Retorna uma posição inválida se a pilha estiver vazia
    }

    Nodo* topo = pilha->topo;
    Posicao posicao = topo->posicao;
    pilha->topo = topo->proximo;
    free(topo);

    return posicao;
}

// Verificar se a pilha está vazia
int pilhaVazia(Pilha* pilha) {
    return pilha->topo == NULL;
}

// Liberar memória da pilha
void liberarPilha(Pilha* pilha) {
    while (!pilhaVazia(pilha)) {
        desempilhar(pilha);
    }
    free(pilha);
}

// Função de backtracking para resolver o labirinto
bool buscarCaminhoBT(Labirinto* labirinto, int linha, int coluna, int* movimentos_totais) {
    // Verifica se a posição atual é válida
    if (!posicaoValida(labirinto, linha, coluna)) {
        return false;
    }

    // Verifica se chegou ao objetivo
    if (ehObjetivo(labirinto, linha, coluna)) {
        labirinto->matriz[linha][coluna] = -1; // Marca o caminho
        return true;
    }

    // Marca a posição atual como parte do caminho
    labirinto->matriz[linha][coluna] = -1;
    (*movimentos_totais)++;

    // Prioridade: cima, direita, esquerda, baixo
    if (buscarCaminhoBT(labirinto, linha - 1, coluna, movimentos_totais)) return true;
    if (buscarCaminhoBT(labirinto, linha, coluna + 1, movimentos_totais)) return true;
    if (buscarCaminhoBT(labirinto, linha, coluna - 1, movimentos_totais)) return true;
    if (buscarCaminhoBT(labirinto, linha + 1, coluna, movimentos_totais)) return true;

    // Backtracking: desmarca a posição
    labirinto->matriz[linha][coluna] = 1;
    (*movimentos_totais)--;
    return false;
}

void resolverLabirinto(Labirinto* labirinto) {
    if (labirinto == NULL) {
        printf("Nenhum labirinto carregado.\n");
        return;
    }

    Posicao inicial = {-1, -1};
    for (int i = 0; i < labirinto->linhas; i++) {
        for (int j = 0; j < labirinto->colunas; j++) {
            if (labirinto->matriz[i][j] == 0) {
                inicial.linha = i;
                inicial.coluna = j;
                break;
            }
        }
        if (inicial.linha != -1) break;
    }

    if (inicial.linha == -1) {
        printf("Labirinto inválido: sem posição inicial.\n");
        return;
    }

    // Inicializa a pilha
    Pilha* pilha = criarPilha();
    empilhar(pilha, inicial);

    int movimentos_totais = 0;
    bool encontrou_saida = false;

    printf("Trajetória:\n");

    // Movimentos: cima, direita, baixo, esquerda
    int movimentos_linha[] = {-1, 0, 1, 0};
    int movimentos_coluna[] = {0, 1, 0, -1};

    while (!pilhaVazia(pilha)) {
        Posicao atual = desempilhar(pilha);
        int linha = atual.linha;
        int coluna = atual.coluna;

        // Registra a posição na saída
        printf("Linha: %d Coluna: %d\n", linha + 1, coluna + 1);
        movimentos_totais++;

        // Marca a posição como visitada
        labirinto->matriz[linha][coluna] = -1;

        // Verifica se chegou à saída
        if (linha == 0) {
            encontrou_saida = true;
            printf("O estudante se movimentou %d vezes e chegou na coluna %d da primeira linha.\n",
                   movimentos_totais, coluna + 1);
            break;
        }

        // Tenta todos os movimentos possíveis
        for (int i = 0; i < 4; i++) {
            int nova_linha = linha + movimentos_linha[i];
            int nova_coluna = coluna + movimentos_coluna[i];

            // Verifica se o movimento é válido
            if (nova_linha >= 0 && nova_linha < labirinto->linhas &&
                nova_coluna >= 0 && nova_coluna < labirinto->colunas &&
                (labirinto->matriz[nova_linha][nova_coluna] == 1 || // Célula branca
                 (labirinto->matriz[nova_linha][nova_coluna] == 3 && labirinto->chaves > 0))) { // Célula vermelha
                if (labirinto->matriz[nova_linha][nova_coluna] == 3) {
                    labirinto->chaves--; // Usa uma chave
                }

                empilhar(pilha, (Posicao){nova_linha, nova_coluna});
            }
        }
    }

    if (!encontrou_saida) {
        printf("O estudante se movimentou %d vezes e percebeu que o labirinto nao tem saida.\n",
               movimentos_totais);
    }

    liberarPilha(pilha);
}
