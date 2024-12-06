#include "../include/Backtracking.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Funções da pilha
Pilha* criar_pilha() {
    Pilha* pilha = (Pilha*)malloc(sizeof(Pilha));
    pilha->topo = NULL;
    return pilha;
}

void empilhar(Pilha* pilha, Posicao posicao) {
    Nodo* novo = (Nodo*)malloc(sizeof(Nodo));
    novo->posicao = posicao;
    novo->proximo = pilha->topo;
    pilha->topo = novo;
}

Posicao desempilhar(Pilha* pilha) {
    if (pilha_vazia(pilha)) {
        Posicao invalida = {-1, -1};
        return invalida;
    }

    Nodo* temp = pilha->topo;
    Posicao posicao = temp->posicao;
    pilha->topo = temp->proximo;
    free(temp);
    return posicao;
}

int pilha_vazia(Pilha* pilha) {
    return pilha->topo == NULL;
}

void liberar_pilha(Pilha* pilha) {
    while (!pilha_vazia(pilha)) {
        desempilhar(pilha);
    }
    free(pilha);
}

// Função de backtracking
void backtracking_labirinto(Labirinto* labirinto) {
    if (labirinto == NULL) {
        printf("Nenhum labirinto carregado.\n");
        return;
    }

    // Localiza a posição inicial (célula 0)
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

    // Configuração de movimentos: cima, direita, baixo, esquerda
    int movimentos_linha[] = {-1, 0, 1, 0};
    int movimentos_coluna[] = {0, 1, 0, -1};

    // Inicializa a pilha
    Pilha* pilha = criar_pilha();
    empilhar(pilha, inicial);

    int movimentos_totais = 0;
    bool encontrou_saida = false;

    printf("Trajetória:\n");

    while (!pilha_vazia(pilha)) {
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
        bool encontrou_caminho = false;
        for (int i = 0; i < 4; i++) {
            int nova_linha = linha + movimentos_linha[i];
            int nova_coluna = coluna + movimentos_coluna[i];

            // Verifica se o movimento é válido
            if (nova_linha >= 0 && nova_linha < labirinto->linhas &&
                nova_coluna >= 0 && nova_coluna < labirinto->colunas &&
                (labirinto->matriz[nova_linha][nova_coluna] == 1 || // Célula branca
                 labirinto->matriz[nova_linha][nova_coluna] == 3)) { // Célula vermelha
                if (labirinto->matriz[nova_linha][nova_coluna] == 3 && labirinto->chaves > 0) {
                    labirinto->chaves--; // Usa uma chave
                }

                empilhar(pilha, (Posicao){nova_linha, nova_coluna});
                encontrou_caminho = true;
                break;
            }
        }

        // Se não encontrou caminho, reverte (não faz nada, apenas desempilha na próxima iteração)
        if (!encontrou_caminho) {
            labirinto->matriz[linha][coluna] = 1; // Marca como não visitado novamente
        }
    }

    if (!encontrou_saida) {
        printf("O estudante se movimentou %d vezes e percebeu que o labirinto nao tem saida.\n",
               movimentos_totais);
    }

    liberar_pilha(pilha);
}
